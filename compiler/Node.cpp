#include "Node.h"
#include "Lexer.h"

Node::Node() {//Դ�����ж�Ӧ���к�
	lexerLine = Lexer::line;
}

void Node::error(string str) {
	cerr << "Near Line " << lexerLine << ": " << str << endl;
	io << "Near Line " << lexerLine << ": " << str << endl;
}
