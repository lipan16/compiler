#include "Parser.h"

Parser::Parser(Lexer* l): p_lex(l), look(NULL), top(NULL), used(0) {//以当前词法构造一个语法分析器
	move();
}

void Parser::move() {//读下一个词法单元
	look = p_lex->scan();
}

void Parser::error(string msg) {//错误输出
	cerr << "Near Line " << p_lex->line << ": " << msg << endl;
}

void Parser::match(int t) {//匹配
	if ((int) look->t_tag == t) {
		move();
	} else {
		error("Syntax Error");
	}
}

void Parser::program() {//语法分析的开始，最大的语法单元program，program -> block
	syntax_node* root = makenode("program");
	syntax_node* s = block();
	root->son = s;
	showtree(root, 0);
}

syntax_node* Parser::block() {
	syntax_node* node = makenode("block");

	match('{');
	syntax_node *tmp = makenode("temp");
	node->son = tmp;
	tmp->son = makenode("{");
	Env* savedEnv = top;//指向前面的符号表的连接
	top = new Env(top);
	tmp->bro = decls();
	syntax_node *tmp1 = makenode("temp");
	node->bro = tmp1;
	tmp1->son = stmts();
	match('}');
	tmp1->bro = makenode("}");
	//cout << *top;
	//io << *top;
	top = savedEnv;//存放最顶层的符号表
	return node;
}

syntax_node* Parser::decls() {
	syntax_node *node = makenode("decls");
	syntax_node *tmp0 = node;

	while (look->t_tag == BASIC) {//当声明语句是基本类型int，float，char，bool
		DataType* p = type();
		Word* tokWord = (Word *) look;

		syntax_node *tmp = makenode("decl");
		tmp0->son = tmp;
		tmp->son = makenode(p->toString());
		syntax_node *tmp1 = makenode(tokWord->w_lexme);
		tmp->bro = tmp1;
		match(ID);//是否是标识符
		match(';');
		tmp1->son = makenode(";");
		tmp0->bro = makenode("temp");
		tmp0 = tmp0->bro;

		Id id(tokWord, p, used);//以该数值构造一个叶子节点
		top->put(*tokWord, id);//加入到字典中
		used = used + p->d_width;//位置后移
	}
	return node;
}

DataType* Parser::type() {
	Word *lookAsWord = (Word*) look;
	int width = 0;
	if (lookAsWord->w_lexme.compare("char") == 0) {//char类型占一个字节
		width = 1;
	} else if (lookAsWord->w_lexme.compare("bool") == 0) {
		width = 1;
	} else {
		width = 4;//float int型4字节
	}
	DataType* p = new DataType(lookAsWord->w_lexme, lookAsWord->t_tag, width);//数据对象
	match(BASIC);
	return p;
}

syntax_node* Parser::stmts() {
	if (look->t_tag == '}') {
		return NULL;
	} else {
		syntax_node *node = makenode("stmts");
		node->son = stmt();//一条语句
		node->bro = stmts();//语句序列，递归，再次调用stmts
		return node;
	}
}

syntax_node* Parser::stmt() {//一条语句的处理
	if (look->t_tag == ';') {//空语句
		move();
		return makenode(";");
	} else if (look->t_tag == IF) {//if语句
		match(IF);
		match('(');

		syntax_node *tmp = makenode("if");
		tmp->son = makenode("(");
		syntax_node *tmp1 = makenode("temp");
		tmp->bro = tmp1;
		syntax_node* x = boolExpr();//bool表达式
		tmp1->son = x;//bool表达式
		match(')');
		syntax_node*tmp2 = makenode("temp");
		tmp2->son = makenode(")");
		syntax_node* s1 = stmt();//为true时的语句
		syntax_node*tmp3 = makenode("temp");
		tmp2->bro = tmp3;
		tmp3->son = s1;
		tmp3->bro = NULL;
		if (look->t_tag != ELSE) {//if后没有else
			return tmp;
		}
		match(ELSE);
		syntax_node*tmp4 = makenode("else");
		tmp3->bro = tmp4;
		syntax_node* s2 = stmt();//false时 语句
		tmp4->son = s2;
		return tmp;
	} else if (look->t_tag == WHILE) {//while语句
		match(WHILE);
		match('(');
		syntax_node *tmp = makenode("while");
		tmp->son = makenode("(");

		syntax_node* x = boolExpr();
		syntax_node *tmp1 = makenode("temp");
		tmp->bro = tmp1;
		tmp1->son = x;//x
		syntax_node *tmp2 = makenode("temp");
		tmp1->bro = tmp2;
		match(')');
		tmp2->son = makenode(")");
		syntax_node* s = stmt();
		tmp2->bro = s;
		return tmp;
	} else if (look->t_tag == DO) {//do语句
		match(DO);
		syntax_node *tmp = makenode("do");
		syntax_node* s = stmt();
		tmp->son = s;
		match(WHILE);
		syntax_node *tmp1 = makenode("while");
		tmp->bro = tmp1;
		match('(');
		syntax_node *tmp2 = makenode("temp");
		tmp1->son = tmp2;
		tmp2->son = makenode("(");
		syntax_node* x = boolExpr();
		tmp2->bro = x;//x
		match(')');
		match(';');
		syntax_node * tmp3 = makenode("temp");
		tmp1->bro = tmp3;
		tmp3->son = makenode(")");
		tmp3->bro = makenode(";");
		return tmp;
	} else if (look->t_tag == BREAK) {//break语句
		match(BREAK);
		match(';');
		syntax_node *tmp = makenode("break");
		tmp->son = makenode(";");
		return tmp;
	} else if (look->t_tag == '{') {//块语句
		syntax_node *tmp = block();//再次调用bolck()函数
		return tmp;
	} else {
		return assign();//赋值语句
	}
}

syntax_node* Parser::assign() {//赋值语句
	syntax_node* s = makenode("assign");
	Word* w = (Word*) look;//标识符
	Id* id = new Id(top->get(w));
	if (*id == *Id::IdNULL) {//在字典中未找到当前标识符
		error(((Word *) look)->toString() + " Undeclared");
	}
	match(ID);
	syntax_node *tmp1 = makenode("temp");
	syntax_node* tmp2 = makenode("temp");
	s->son = tmp1;
	tmp1->son = makenode(w->w_lexme);
	if (look->t_tag == '=') {
		tmp1->bro = makenode("=");
		move();
		//Id *lhs = new Id(*id);//赋值表达式左边
		syntax_node *rhs = boolExpr();//右边
		s->bro = tmp2;
		tmp2->son = rhs;
	}
	match(';');
	tmp2->bro = makenode(";");
	return s;
}

syntax_node* Parser::boolExpr() {//bool表达式，所有的表达式
	syntax_node *node = makenode("boolexpr");
	syntax_node *tmp = makenode("temp");
	syntax_node* x = join();
	node->son = x;//x
	node->bro = tmp;
	while (look->t_tag == OR) {//或表达式
		Token* tok = look;
		move();
		syntax_node *tmp1 = makenode("||");
		syntax_node *tmp2 = makenode("temp");
		tmp->son = tmp1;
		tmp->bro = tmp2;
		syntax_node *rhs = join();
		tmp2->son = rhs;//rhs
		syntax_node *tmp3 = makenode("temp");
		tmp2->bro = tmp3;
		tmp = tmp3;
	}
	return node;
}

syntax_node* Parser::join() {
	syntax_node *node = makenode("join");
	syntax_node *tmp = makenode("temp");
	syntax_node* x = equality();
	node->son = x;
	node->bro = tmp;
	while (look->t_tag == AND) {//and
		Token* tok = look;
		move();
		syntax_node *tmp1 = makenode("&&");
		syntax_node *tmp2 = makenode("temp");
		tmp->son = tmp1;
		tmp->bro = tmp2;
		syntax_node *rhs = equality();
		tmp2->son = rhs;
		syntax_node *tmp3 = makenode("temp");
		tmp2->bro = tmp3;
		tmp = tmp3;
	}
	return node;
}

syntax_node* Parser::equality() {
	syntax_node *node = makenode("equality");
	syntax_node *tmp = makenode("temp");
	syntax_node* x = rel();
	node->son = x;
	node->bro = tmp;
	while (look->t_tag == EQ || look->t_tag == NE) {//== !=
		string str = look->toString();
		Token* tok = look;
		move();
		syntax_node *tmp1 = makenode(str);
		syntax_node *tmp2 = makenode("temp");
		tmp->son = tmp1;
		tmp->bro = tmp2;
		syntax_node *rhsExpr = rel();
		tmp2->son = rhsExpr;
		syntax_node *tmp3 = makenode("temp");
		tmp2->bro = tmp3;
		tmp = tmp3;
	}
	return node;
}

syntax_node* Parser::rel() {
	syntax_node *node = makenode("rel");
	syntax_node* x = expr();
	node->son = x;
	if (look->t_tag == '<' || look->t_tag == '>'||look->t_tag==GE ||look->t_tag==LE) {//比较
		string str=look->toString();
		Token* tok = look;
		move();
		syntax_node *tmp = makenode("temp");
		node->bro = tmp;
		tmp->son = makenode(str);
		syntax_node *rhsExpr = expr();
		tmp->bro = rhsExpr;
	}
	return node;
}

syntax_node* Parser::expr() {
	syntax_node *node = makenode("expr");
	syntax_node *tmp = makenode("temp");
	syntax_node* x = term();
	node->son = x;
	node->bro = tmp;
	while (look->t_tag == '+' || look->t_tag == '-') {
		Token* tok = look;
		move();
		string str;
		if (look->t_tag == '+') {
			str = "+";
		} else {
			str = "-";
		}
		syntax_node *tmp1 = makenode(str);
		syntax_node *tmp2 = makenode("temp");
		tmp->son = tmp1;
		tmp->bro = tmp2;
		syntax_node *rhs = expr();
		tmp2->son = rhs;
		syntax_node *tmp3 = makenode("temp");
		tmp2->bro=tmp3;
		tmp = tmp3;
	}
	return node;
}

syntax_node* Parser::term() {
	syntax_node *node = makenode("expr");
	syntax_node *tmp = makenode("temp");
	syntax_node* x = unary();
	node->son = x;
	node->bro = tmp;
	while (look->t_tag == '*' || look->t_tag == '/') {
		string str = look->toString();
		Token* tok = look;
		move();
		syntax_node *tmp1 = makenode(str);
		syntax_node *tmp2 = makenode("temp");
		tmp->son = tmp1;
		tmp->bro = tmp2;
		syntax_node *rhs = unary();
		tmp2->son = rhs;
		syntax_node *tmp3 = makenode("temp");
		tmp2->bro = tmp3;
		tmp = tmp3;
	}
	return node;
}

syntax_node* Parser::unary() {
	syntax_node *node = makenode("unary");
	if (look->t_tag == '-') {
		move();
		node->son = makenode("-");
		syntax_node *rhs = unary();
		node->bro = rhs;
		return node;
	} else if (look->t_tag == '!') {
		Token* tok = look;
		move();
		node->son = makenode("!");
		syntax_node *rhs = unary();
		node->bro = rhs;
		return node;
	} else {
		return factor();
	}
}

syntax_node* Parser::factor() {
	syntax_node *node = makenode("factor");
	syntax_node *x = makenode("temp");
	if (look->t_tag == '(') {
		move();
		node->son=makenode("(");
		node->bro = x;
		x->son=boolExpr();
		match(')');
		x->bro = makenode(")");
		return x;
	} else if (look->t_tag == NUM) {
		x = makenode(look->toString());
		move();
		return x;
	} else if (look->t_tag == REAL) {
		x = makenode(look->toString());
		move();
		return x;
	} else if (look->t_tag == TRUE) {
		move();
		return makenode("true");
	} else if (look->t_tag == FALSE) {
		move();
		return makenode("false");
	} else if (look->t_tag == ID) {
		string s = look->toString();
		Word *w = (Word*) look;
		Id* id = new Id(top->get(w));
		if (id == Id::IdNULL) {
			error(look->toString() + "Undeclared");
		}
		move();
		x = makenode(s);
		return x;
	} else {
		error("Syntax Error");
		return NULL;
	}
}

syntax_node* Parser::makenode(string s) {
	syntax_node* node = new syntax_node;
	node->str = s;
	node->lexerLine = p_lex->line;
	node->bro = NULL;
	node->son = NULL;
	return node;
}

static void PrintWhiteSpaces(int num) {
	for (int i = 0; i < num; i++)
		cout << "__";
}

void Parser::showtree(syntax_node* root, int num) {
	syntax_node * head = root;
	if (head == NULL)
		return;
	PrintWhiteSpaces(num);
	cout << head->str << endl;
	showtree(head->son, num + 1);
	showtree(head->bro, num + 1);
}
