#pragma once
#include <string>
#include <iostream>


using namespace std;

extern std::ofstream io;

struct syntax_node { //语法树的结点
	int lexerLine;//行号
	string str;
	struct syntax_node* bro;//语法单元兄弟结点
	struct syntax_node* son;//语法单元儿子结点
};

class syntaxtree{//节点类
public:
	syntax_node* head;

	syntaxtree();
	syntax_node* makenode(string s);
	string tostring();
};