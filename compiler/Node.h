#pragma once
#include <string>
#include <iostream>

using namespace std;

extern std::ofstream io;

class Node {//语法树中的节点类
public:
	int lexerLine;
	static int label;
	Node(void);

	int newLabel();
	void error(string str);
	void emitLabel(int i);
	void emit(string str);
};

