#include "Lexer.h"

int Lexer::line = 1;//行号

Lexer::Lexer(string sourceFileName) {
	reserve(Word("if", IF));//存储定义的关键字,（关键字，关键字在Tag对应的类型）
	reserve(Word("else", ELSE));
	reserve(Word("while", WHILE));
	reserve(Word("do", DO));
	reserve(Word("break", BREAK));

	reserve(*Word::WordTRUE);
	reserve(*Word::WordFALSE);

	reserve(*DataType::TypeBOOL);
	reserve(*DataType::TypeCHAR);
	reserve(*DataType::TypeFLOAT);
	reserve(*DataType::TypeINT);

	source.open(sourceFileName.c_str(), ios::in);//打开文件
	source.unsetf(ios::skipws);//取消跳过空白
	if (!source.is_open()) {
		cout << "Fail to Open File " << sourceFileName << endl;
		exit(1);
	}
}

Token* Lexer::scan() {
	for (; ; readChar()) {
		if (peekChar == EOF) {//文档结束
			return NULL;
		}
		if (peekChar == ' ' || peekChar == '\t') {//空格和tab
			continue;
		} else if (peekChar == '\n') {//新行
			line++;
		} else if (peekChar > 0) {//读到一个字符
			break;
		}
	}

	switch (peekChar) {//是否双目运算符
	case '+':
		if (readChar('+')) {
			cout << "line:" << line << "\t" << (*Word::WordPLUS);
			io << "line:" << line << "\t" << (*Word::WordPLUS);
			return Word::WordPLUS;
		} else if (peekChar == '=') {
			cout << "line:" << line << "\t" << (*Word::WordAE);
			io << "line:" << line << "\t" << (*Word::WordAE);
			return Word::WordAE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('+');
			io << "line:" << line << "\tOperater：" << Token('+');
			return new Token('+');
		}
		break;
	case '-':
		if (readChar('-')) {
			cout << "line:" << line << "\t" << (*Word::WordSUBS);
			io << "line:" << line << "\t" << (*Word::WordSUBS);
			return Word::WordSUBS;
		} else if (peekChar == '=') {
			cout << "line:" << line << "\t" << (*Word::WordSE);
			io << "line:" << line << "\t" << (*Word::WordSE);
			return Word::WordSE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('-');
			io << "line:" << line << "\tOperater：" << Token('-');
			return new Token('-');
		}
		break;
	case '*':
		if (readChar('=')) {
			cout << "line:" << line << "\t" << (*Word::WordME);
			io << "line:" << line << "\t" << (*Word::WordME);
			return Word::WordME;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('*');
			io << "line:" << line << "\tOperater：" << Token('*');
			return new Token('*');
		}
		break;
	case '/':
		if (readChar('=')) {
			cout << "line:" << line << "\t" << (*Word::WordDE);
			io << "line:" << line << "\t" << (*Word::WordDE);
			return Word::WordDE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('/');
			io << "line:" << line << "\tOperater：" << Token('/');
			return new Token('*');
		}
		break;
	case '&':
		if (readChar('&')) {//&&
			cout << "line:" << line << "\t" << (*Word::WordAND);
			io << "line:" << line << "\t" << (*Word::WordAND);
			return Word::WordAND;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('&');
			io << "line:" << line << "\tOperater：" << Token('&');
			return new Token('&');
		}
		break;
	case '|':
		if (readChar('|')) {//||
			cout << "line:" << line << "\t" << (*Word::WordOR);
			io << "line:" << line << "\t" << (*Word::WordOR);
			return Word::WordOR;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('|');
			io << "line:" << line << "\tOperater：" << Token('|');
			return new Token('|');
		}
		break;
	case '=':
		if (readChar('=')) {//==
			cout << "line:" << line << "\t" << (*Word::WordEQ);
			io << "line:" << line << "\t" << (*Word::WordEQ);
			return Word::WordEQ;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('=');
			io << "line:" << line << "\tOperater：" << Token('=');
			return new Token('=');
		}
		break;
	case '<':
		if (readChar('=')) {//<=
			cout << "line:" << line << "\t" << (*Word::WordLE);
			io << "line:" << line << "\t" << (*Word::WordLE);
			return Word::WordLE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('<');
			io << "line:" << line << "\tOperater：" << Token('<');
			return new Token('<');
		}
		break;
	case '>':
		if (readChar('=')) {//>=
			cout << "line:" << line << "\t" << (*Word::WordGE);
			io << "line:" << line << "\t" << (*Word::WordGE);
			return Word::WordGE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('>');
			io << "line:" << line << "\tOperater：" << Token('>');
			return new Token('>');
		}
		break;
	case '!':
		if (readChar('=')) {//!=
			cout << "line:" << line << "\t" << (*Word::WordNE);
			io << "line:" << line << "\t" << (*Word::WordNE);
			return Word::WordNE;
		} else {
			cout << "line:" << line << "\tOperater：" << Token('!');
			io << "line:" << line << "\tOperater：" << Token('!');
			return new Token('!');
		}
		break;
	default:
		break;
	}

	if (isdigit(peekChar)) {//数字
		int v = 0;
		do {
			v = v * 10 + (peekChar - '0');//ASCII变数值
			readChar();
		} while (isdigit(peekChar));//是数字时一直读
		if (peekChar != '.') {//非小数
			cout << "line:" << line << "\tInt Value：" << v << endl;
			io << "line:" << line << "\tInt Value：" << v << endl;
			return new Num(v);//返回数字
		}
		float f = (float) v;
		float d = 10;
		while (isdigit(peekChar)) {
			f = f + (float) (peekChar - '0') / d;
			d = d * 10;
		}
		cout << "line:" << line << "\tReal Value：" << v << endl;
		io << "line:" << line << "\tReal Value：" << v << endl;
		return new Real(f);//返回实数
	}

	if (isalpha(peekChar)) {//字母
		stringstream idSS;//字符串流
		do {
			idSS << peekChar;//向流中传值
			readChar();
		} while (isalpha(peekChar));
		string id = idSS.str();//得到当前流中的值
		Word* w = findByString(id);
		if (w == Word::WordNULL) {
			Word* idWord = new Word(id, ID);
			reserve(*idWord);//在顺序表末端插入

			cout << "line:" << line << "\t" << (*idWord);//输出 Word中重载的<<
			io << "line:" << line << "\t" << (*idWord);

			return idWord;
		}
		cout << "line:" << line << "\t" << (*w);//输出 Word中重载的<<
		io << "line:" << line << "\t" << (*w);
		return w;
	}

	Token* tok = new Token(peekChar);
	peekChar = ' ';
	cout << "line:" << line << "\t\t" << (*tok);//输出 Token中重载的<<
	io << "line:" << line << "\t\t" << (*tok);
	return tok;
}

void Lexer::reserve(Word w) {//存数据
	words.push_back(w);//在顺序表末端插入数据
}

Word* Lexer::findByString(string& str) {//查找str是否在顺序表中，是的话返回该单词，不是就返回null
	for (vector<Word>::iterator iter = words.begin(); iter != words.end(); iter++) {
		if (iter->w_lexme.compare(str) == 0) {
			return &(*iter);
		}
	}
	return Word::WordNULL;
}

void Lexer::readChar() {//从文件中读一个字符
	if (source.eof()) {
		peekChar = EOF;
	} else if (source.good()) {//状态良好
		source >> peekChar;
	}
}

bool Lexer::readChar(char c) {//比较下一个字符是否是c
	readChar();
	if (peekChar != c || peekChar == EOF) {
		return false;
	}
	peekChar = ' ';
	return true;
}