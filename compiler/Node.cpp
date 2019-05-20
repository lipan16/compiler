#include "Node.h"
#include "Lexer.h"

Node::Node() {//源程序中对应的行号
	lexerLine = Lexer::line;
}

void Node::error(string str) {
	cerr << "Near Line " << lexerLine << ": " << str << endl;
	io << "Near Line " << lexerLine << ": " << str << endl;
}
