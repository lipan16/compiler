#pragma once
#include "Node.h"
#include "Token.h"
#include "Word.h"
#include "DataType.h"

#include <sstream>
#include <iostream>

using namespace std;

class Expr: public Node {//���ʽ�ڵ㹹���࣬���������ʽ����ת����
public:
	Token* op;//�ýڵ��ϵ������
	DataType* type;//�ýڵ�����
	static Expr* ExprNULL;

	Expr();
	Expr(Token* tok, DataType* p);//������������͹���һ���ڵ����
	bool operator==(const Expr& rhs);
	virtual Expr* gen();//����һ�������������Գ�Ϊһ������ַָ����Ҳ��������һ�����ʽE=E1+E2,����gen����һ����x1+x2������x1��x2���E1��E2ֵ�ĵ�ַ��������������һ����ַ�ͷ���thisֵ
	virtual Expr* reduce();//��Լ����һ�����ʽ�����Ϊһ����һ�ĵ�ַ����һ����������ʶ����������ʱ����
	virtual void jumping(int t, int f);
	virtual void emitJumps(string test, int t, int f);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Expr& expr);
};

class Id: public Expr {//Ҷ�ӽڵ���
public:
	static Id* IdNULL;

	Id();
	Id(Token* id, DataType* p, int b);
	bool operator==(const Id& rhs);
	friend ostream& operator<<(ostream& os, const Id& id);
private:
	int offset;//�ñ�ʶ������Ե�ַ
};

class Temp: public Expr {
public:
	static int count;

	Temp(DataType* p);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Temp& temp);
private:
	int number;
};


class Constant: public Expr {
public:
	static Constant* ConstantTRUE;
	static Constant* ConstantFALSE;

	Constant(Token* tok, DataType* p);//����һ�����Ϊtok������Ϊp��Ҷ�ӽڵ�
	Constant(int i);//���أ�����i����һ����������
	friend ostream& operator<<(ostream& os, const Constant& constant);//�������<<�����
	virtual void jumping(int t, int f);//�������ʽ����ת
};