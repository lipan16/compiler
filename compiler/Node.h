#pragma once
#include <string>
#include <iostream>


using namespace std;

extern std::ofstream io;


class Node{//�ڵ���
public:
	int lexerLine;

	Node();
	void error(string str);
};