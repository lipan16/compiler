#pragma once
#include <string>
#include <sstream>
#include <iostream>

#include "Token.h"
#include "Word.h"
#include "DataType.h"

using namespace std;

extern std::ofstream io;

class Id{//Ҷ�ӽڵ���
public:
	int lexerLine;//�к�
	Token* op;//�ýڵ��ϵ������
	DataType* type;//�ýڵ�����

	static Id* IdNULL;

	Id();
	Id(Token* id, DataType* p, int b);
	bool operator==(const Id& rhs);
	void error(string);
	friend ostream& operator<<(ostream& os, const Id& id);
private:
	int offset;//�ñ�ʶ������Ե�ַ
};