#pragma once
#include <string>
#include <iostream>

using namespace std;

extern std::ofstream io;

class Node {//�﷨���еĽڵ���
public:
	int lexerLine;
	static int label;
	Node(void);

	int newLabel();
	void error(string str);
	void emitLabel(int i);
	void emit(string str);
};

