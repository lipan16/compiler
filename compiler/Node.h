#pragma once
#include <string>
#include <iostream>

using namespace std;

extern std::ofstream io;

class Node {
public:
	Node(void);
	virtual ~Node(void);
	void error(string str);
	int newLabel();
	void emitLabel(int i);
	void emit(string str);

	int lexerLine;
	static int label;
};

