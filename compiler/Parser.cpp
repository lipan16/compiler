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
	Stmt* s = block();

	int begin = s->newLabel();
	int after = s->newLabel();
	s->emitLabel(begin);//输出标签 L1:
	s->gen(begin, after);

	//s->emitLabel(after);
}

Stmt* Parser::block() {
	match('{');
	Env* savedEnv = top;//指向前面的符号表的连接
	top = new Env(top);
	decls();
	Stmt* s = stmts();
	match('}');

	cout << *top;
	io << *top;

	top = savedEnv;//存放最顶层的符号表
	return s;
}

void Parser::decls() {
	while (look->t_tag == BASIC) {//当声明语句是基本类型int，float，char，bool
		DataType* p = type();
		Word* tokWord = (Word *) look;
		match(ID);//是否是标识符
		match(';');
		Id id(tokWord, p, used);//以该数值构造一个叶子节点
		top->put(*tokWord, id);//加入到字典中
		used = used + p->d_width;//位置后移
	}
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
	if (look->t_tag != '[') {
		return p;
	} else {
		return dims(p);//返回数组类型
	}
}

DataType* Parser::dims(DataType* p) {
	match('[');
	Num *tok = (Num *) look;
	match(NUM);
	match(']');
	if (look->t_tag == '[') {//多维数组
		p = dims(p);
	}
	return new Array(tok->n_value, p);//构造数组
}

Stmt* Parser::stmts() {
	if (look->t_tag == '}') {
		return Stmt::StmtNULL;
	} else {
		Stmt *s = stmt();//一条语句
		return new Seq(s, stmts());//语句序列，递归，再次调用stmts
	}
}

Stmt* Parser::stmt() {//一条语句的处理
	if (look->t_tag == ';') {//空语句
		move();
		return Stmt::StmtNULL;
	} else if (look->t_tag == IF) {//if语句
		match(IF);
		match('(');
		Expr* x = boolExpr();//bool表达式
		match(')');
		Stmt* s1 = stmt();//为true时的语句
		if (look->t_tag != ELSE) {//if后没有else
			return new If(x, s1);
		}
		match(ELSE);
		Stmt* s2 = stmt();//false时 语句
		return new Else(x, s1, s2);//if后有else语句
	} else if (look->t_tag == WHILE) {//while语句
		While* whileNode = new While();;
		Stmt* savedStmt = Stmt::Enclosing;
		Stmt::Enclosing = whileNode;
		match(WHILE);
		match('(');
		Expr* x = boolExpr();
		match(')');
		Stmt* s = stmt();
		whileNode->init(x, s);
		Stmt::Enclosing = savedStmt;
		return whileNode;
	} else if (look->t_tag == DO) {//do语句
		Do* doNode = new Do();
		Stmt* savedStmt = Stmt::Enclosing;
		Stmt::Enclosing = doNode;
		match(DO);
		Stmt* s = stmt();
		match(WHILE);
		match('(');
		Expr* x = boolExpr();
		match(')');
		match(';');
		doNode->init(x, s);
		Stmt::Enclosing = savedStmt;
		return doNode;
	} else if (look->t_tag == BREAK) {//break语句
		match(BREAK);
		match(';');
		return new Break();
	} else if (look->t_tag == '{') {//块语句
		return block();//再次调用bolck()函数
	} else {
		return assign();//赋值语句
	}
}

Stmt* Parser::assign() {//赋值语句
	Stmt* s = NULL;
	Word* w = (Word*) look;//标识符
	Id* id = new Id(top->get(w));

	if (*id == *Id::IdNULL) {//在字典中未找到当前标识符
		error(((Word *) look)->toString() + " Undeclared");
	}
	match(ID);
	if (look->t_tag == '=') {
		move();
		Id *lhs = new Id(*id);//赋值表达式左边
		Expr *rhs = boolExpr();//右边
		s = new Set(lhs, rhs);//设置为赋值运算，lhs=rhs
	} else {//针对数组赋值
		Access* x = offset(id);
		match('=');
		Expr *rhs = boolExpr();
		s = new SetElem(x, rhs);
	}
	match(';');
	return s;
}

Expr* Parser::boolExpr() {//bool表达式，所有的表达式
	Expr* x = join();
	while (look->t_tag == OR) {//或表达式
		Token* tok = look;
		move();
		Expr *rhs = join();
		Or* orExpr = new Or(tok, x, rhs);
		x = orExpr;
	}
	return x;
}

Expr* Parser::join() {
	Expr* x = equality();
	while (look->t_tag == AND) {//and
		Token* tok = look;
		move();
		Expr *rhs = equality();
		And *andExpr = new And(tok, x, rhs);
		x = andExpr;
	}
	return x;
}

Expr* Parser::equality() {
	Expr* x = rel();
	while (look->t_tag == EQ || look->t_tag == NE) {//== !=
		Token* tok = look;
		move();
		Expr *rhsExpr = rel();
		Rel *rel = new Rel(tok, x, rhsExpr);
		x = rel;
	}
	return x;
}

Expr* Parser::rel() {
	Expr* x = expr();
	if (look->t_tag == '<' || look->t_tag == '>' || look->t_tag == LE || look->t_tag == GE) {//比较
		Token* tok = look;
		move();
		Expr *rhsExpr = expr();
		Rel *rel = new Rel(tok, x, rhsExpr);
		return rel;
	}
	return x;
}

Expr* Parser::expr() {
	Expr* x = term();
	while (look->t_tag == '+' || look->t_tag == '-' || look->t_tag == AE || look->t_tag == SE) {
		Token* tok = look;
		move();
		Expr *rhs = expr();
		Arith* temp = new Arith(tok, x, rhs);
		x = temp;
	}
	return x;
}

Expr* Parser::term() {
	Expr* x = unary();
	while (look->t_tag == '*' || look->t_tag == '/') {
		Token* tok = look;
		move();
		Expr *rhs = unary();
		x = new Arith(tok, x, rhs);
	}
	return x;
}

Expr* Parser::unary() {
	if (look->t_tag == '-') {
		move();
		Expr *rhs = unary();
		return new Unary(Word::WordMINUS, rhs);
	} else if (look->t_tag == '!') {
		Token* tok = look;
		move();
		Expr *rhs = unary();
		return new Not(tok, rhs);
	} else {
		return factor();
	}
}

Expr* Parser::factor() {
	Expr *x = NULL;
	if (look->t_tag == '(') {
		move();
		x = boolExpr();
		match(')');
		return x;
	} else if (look->t_tag == NUM) {
		x = new Constant(look, DataType::TypeINT);
		move();
		return x;
	} else if (look->t_tag == REAL) {
		x = new Constant(look, DataType::TypeFLOAT);
		move();
		return x;
	} else if (look->t_tag == TRUE) {
		move();
		return new Constant(*Constant::ConstantTRUE);
	} else if (look->t_tag == FALSE) {
		move();
		return new Constant(*Constant::ConstantFALSE);
	} else if (look->t_tag == ID) {
		string s = look->toString();
		Word *w = (Word*) look;
		Id* id = new Id(top->get(w));
		if (id == Id::IdNULL) {
			error(look->toString() + "Undeclared");
		}
		move();
		if (look->t_tag != '[') {
			return new Id(*id);
		} else {
			return offset(id);
		}
	} else {
		error("Syntax Error");
		return new Expr(*Expr::ExprNULL);
	}
}

Access* Parser::offset(Id* a) {
	Array* type = (Array *) a->type;
	match('[');
	Expr* index = boolExpr();
	DataType* ofType = type->a_of;
	Expr* w = new Constant(ofType->d_width);
	Expr* t1 = new Arith(new Token('*'), index, w);
	Expr* loc = t1;
	Expr* t2 = NULL;

	match(']');

	while (look->t_tag == '[') {
		match('[');
		index = boolExpr();
		w = new Constant(ofType->d_width);
		t1 = new Arith(new Token('*'), index, w);
		t2 = new Arith(new Token('+'), loc, t1);
		loc = t2;
	}
	Id *array = new Id(*a);
	return new Access(array, loc, ofType);
}
