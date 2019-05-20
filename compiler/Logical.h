#pragma once
#include "Expr.h"
#include "DataType.h"

using namespace std;

class Logical: public Expr {//处理逻辑运算
public:
	Expr* exp1;
	Expr* exp2;//逻辑运算的两个运算分量

	Logical(Token* tok, Expr* e1, Expr* e2);//构造一个语法树节点，运算符tok，运算分量e1，e2
	virtual string toString() const;
};

class Or: public Logical {//处理或运算
public:
	Or(Token* tok, Expr* e1, Expr* e2);
};

class And: public Logical {//处理与运算
public:
	And(Token* tok, Expr* e1, Expr* e2);
};

class Not: public Logical {//处理非运算，单目
public:
	Not(Token* tok, Expr* e);//e被使用两次
	virtual string toString() const;
};

class Rel: public Logical {//实现<,<=,>,>=,==,!=
public:
	Rel(Token* tok, Expr* e1, Expr* e2);
};