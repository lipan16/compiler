#pragma once
#include "Expr.h"
#include "DataType.h"

using namespace std;

class Logical: public Expr {//�����߼�����
public:
	Expr* exp1;
	Expr* exp2;//�߼�����������������

	Logical(Token* tok, Expr* e1, Expr* e2);//����һ���﷨���ڵ㣬�����tok���������e1��e2
	virtual string toString() const;
};

class Or: public Logical {//���������
public:
	Or(Token* tok, Expr* e1, Expr* e2);
};

class And: public Logical {//����������
public:
	And(Token* tok, Expr* e1, Expr* e2);
};

class Not: public Logical {//��������㣬��Ŀ
public:
	Not(Token* tok, Expr* e);//e��ʹ������
	virtual string toString() const;
};

class Rel: public Logical {//ʵ��<,<=,>,>=,==,!=
public:
	Rel(Token* tok, Expr* e1, Expr* e2);
};