#pragma once
#include "Expr.h"
#include "Token.h"
#include "DataType.h"

using namespace std;

class Op: public Expr {
public:
	Op(Token* tok, DataType* p);

	virtual Expr* reduce();
};

class Arith: public Op {//����˫Ŀ����
public:
	Arith(Token* tok, Expr* e1, Expr* e2);

	virtual Expr* gen();
	virtual string toString() const;
private:
	Expr* exp1;
	Expr* exp2;
};

class Unary: public Op {//����Ŀ����
public:
	Unary(Token* tok, Expr* e);//����Ŀ����
	virtual Expr* gen();
	virtual string toString() const;
private:
	Expr* exp;
};

class Access: public Op {
public:
	Id* array;
	Expr* index;

	Access(Id* a, Expr* i, DataType* p);

	virtual Expr* gen();
	virtual void jumping(int t, int f);
	virtual string toString() const;
};