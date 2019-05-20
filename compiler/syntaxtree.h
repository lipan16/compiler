#pragma once
#include <string>
#include <iostream>


using namespace std;

extern std::ofstream io;

struct syntax_node { //�﷨���Ľ��
	int lexerLine;//�к�
	string str;
	struct syntax_node* bro;//�﷨��Ԫ�ֵܽ��
	struct syntax_node* son;//�﷨��Ԫ���ӽ��
};

class syntaxtree{//�ڵ���
public:
	syntax_node* head;

	syntaxtree();
	syntax_node* makenode(string s);
	string tostring();
};