#pragma once
#include <string>
#include <sstream>
#include <iostream>

#include "Token.h"
#include "Word.h"
#include "DataType.h"

using namespace std;

extern std::ofstream io;

class Id{//叶子节点类
public:
	int lexerLine;//行号
	Token* op;//该节点上的运算符
	DataType* type;//该节点类型

	static Id* IdNULL;

	Id();
	Id(Token* id, DataType* p, int b);
	bool operator==(const Id& rhs);
	void error(string);
	friend ostream& operator<<(ostream& os, const Id& id);
private:
	int offset;//该标识符的相对地址
};