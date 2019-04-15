#include "Lexer.h"

int Lexer::line = 1;//�к�

Lexer::Lexer(string sourceFileName) {
	reserve(Word("if", IF));//�洢����Ĺؼ���,���ؼ��֣��ؼ�����Tag��Ӧ�����ͣ�
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

	source.open(sourceFileName.c_str(), ios::in);//���ļ�
	source.unsetf(ios::skipws);//ȡ�������հ�
	if (!source.is_open()) {
		cout << "Fail to Open File " << sourceFileName << endl;
		exit(1);
	}
}

Token* Lexer::scan() {
	for (; ; readChar()) {
		if (peekChar == EOF) {//�ĵ�����
			return NULL;
		}
		if (peekChar == ' ' || peekChar == '\t') {//�ո��tab
			continue;
		} else if (peekChar == '\n') {//����
			line++;
		} else if (peekChar > 0) {//����һ���ַ�
			break;
		}
	}

	switch (peekChar) {//�Ƿ�˫Ŀ�����
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
			cout << "line:" << line << "\tOperater��" << Token('+');
			io << "line:" << line << "\tOperater��" << Token('+');
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
			cout << "line:" << line << "\tOperater��" << Token('-');
			io << "line:" << line << "\tOperater��" << Token('-');
			return new Token('-');
		}
		break;
	case '*':
		if (readChar('=')) {
			cout << "line:" << line << "\t" << (*Word::WordME);
			io << "line:" << line << "\t" << (*Word::WordME);
			return Word::WordME;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('*');
			io << "line:" << line << "\tOperater��" << Token('*');
			return new Token('*');
		}
		break;
	case '/':
		if (readChar('=')) {
			cout << "line:" << line << "\t" << (*Word::WordDE);
			io << "line:" << line << "\t" << (*Word::WordDE);
			return Word::WordDE;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('/');
			io << "line:" << line << "\tOperater��" << Token('/');
			return new Token('*');
		}
		break;
	case '&':
		if (readChar('&')) {//&&
			cout << "line:" << line << "\t" << (*Word::WordAND);
			io << "line:" << line << "\t" << (*Word::WordAND);
			return Word::WordAND;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('&');
			io << "line:" << line << "\tOperater��" << Token('&');
			return new Token('&');
		}
		break;
	case '|':
		if (readChar('|')) {//||
			cout << "line:" << line << "\t" << (*Word::WordOR);
			io << "line:" << line << "\t" << (*Word::WordOR);
			return Word::WordOR;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('|');
			io << "line:" << line << "\tOperater��" << Token('|');
			return new Token('|');
		}
		break;
	case '=':
		if (readChar('=')) {//==
			cout << "line:" << line << "\t" << (*Word::WordEQ);
			io << "line:" << line << "\t" << (*Word::WordEQ);
			return Word::WordEQ;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('=');
			io << "line:" << line << "\tOperater��" << Token('=');
			return new Token('=');
		}
		break;
	case '<':
		if (readChar('=')) {//<=
			cout << "line:" << line << "\t" << (*Word::WordLE);
			io << "line:" << line << "\t" << (*Word::WordLE);
			return Word::WordLE;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('<');
			io << "line:" << line << "\tOperater��" << Token('<');
			return new Token('<');
		}
		break;
	case '>':
		if (readChar('=')) {//>=
			cout << "line:" << line << "\t" << (*Word::WordGE);
			io << "line:" << line << "\t" << (*Word::WordGE);
			return Word::WordGE;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('>');
			io << "line:" << line << "\tOperater��" << Token('>');
			return new Token('>');
		}
		break;
	case '!':
		if (readChar('=')) {//!=
			cout << "line:" << line << "\t" << (*Word::WordNE);
			io << "line:" << line << "\t" << (*Word::WordNE);
			return Word::WordNE;
		} else {
			cout << "line:" << line << "\tOperater��" << Token('!');
			io << "line:" << line << "\tOperater��" << Token('!');
			return new Token('!');
		}
		break;
	default:
		break;
	}

	if (isdigit(peekChar)) {//����
		int v = 0;
		do {
			v = v * 10 + (peekChar - '0');//ASCII����ֵ
			readChar();
		} while (isdigit(peekChar));//������ʱһֱ��
		if (peekChar != '.') {//��С��
			cout << "line:" << line << "\tInt Value��" << v << endl;
			io << "line:" << line << "\tInt Value��" << v << endl;
			return new Num(v);//��������
		}
		float f = (float) v;
		float d = 10;
		while (isdigit(peekChar)) {
			f = f + (float) (peekChar - '0') / d;
			d = d * 10;
		}
		cout << "line:" << line << "\tReal Value��" << v << endl;
		io << "line:" << line << "\tReal Value��" << v << endl;
		return new Real(f);//����ʵ��
	}

	if (isalpha(peekChar)) {//��ĸ
		stringstream idSS;//�ַ�����
		do {
			idSS << peekChar;//�����д�ֵ
			readChar();
		} while (isalpha(peekChar));
		string id = idSS.str();//�õ���ǰ���е�ֵ
		Word* w = findByString(id);
		if (w == Word::WordNULL) {
			Word* idWord = new Word(id, ID);
			reserve(*idWord);//��˳���ĩ�˲���

			cout << "line:" << line << "\t" << (*idWord);//��� Word�����ص�<<
			io << "line:" << line << "\t" << (*idWord);

			return idWord;
		}
		cout << "line:" << line << "\t" << (*w);//��� Word�����ص�<<
		io << "line:" << line << "\t" << (*w);
		return w;
	}

	Token* tok = new Token(peekChar);
	peekChar = ' ';
	cout << "line:" << line << "\t\t" << (*tok);//��� Token�����ص�<<
	io << "line:" << line << "\t\t" << (*tok);
	return tok;
}

void Lexer::reserve(Word w) {//������
	words.push_back(w);//��˳���ĩ�˲�������
}

Word* Lexer::findByString(string& str) {//����str�Ƿ���˳����У��ǵĻ����ظõ��ʣ����Ǿͷ���null
	for (vector<Word>::iterator iter = words.begin(); iter != words.end(); iter++) {
		if (iter->w_lexme.compare(str) == 0) {
			return &(*iter);
		}
	}
	return Word::WordNULL;
}

void Lexer::readChar() {//���ļ��ж�һ���ַ�
	if (source.eof()) {
		peekChar = EOF;
	} else if (source.good()) {//״̬����
		source >> peekChar;
	}
}

bool Lexer::readChar(char c) {//�Ƚ���һ���ַ��Ƿ���c
	readChar();
	if (peekChar != c || peekChar == EOF) {
		return false;
	}
	peekChar = ' ';
	return true;
}