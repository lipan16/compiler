#include "Node.h"
#include "Lexer.h"

int Node::label = 0;

Node::Node(void) {//Դ�����ж�Ӧ���к�
	lexerLine = Lexer::line;
}

void Node::error(string str) {
	cerr << "Near Line " << lexerLine << ": " << str << endl;
	io << "Near Line " << lexerLine << ": " << str << endl;
}

int Node::newLabel() {
	return ++label;
}

void Node::emitLabel(int i) {
	cout << "L" << i << ":";
	io << "L" << i << ":";
}

void Node::emit(string str) {
	cout << "\t" << str << endl;
	io << "\t" << str << endl;
}