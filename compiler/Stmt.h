#pragma once
#include "Node.h"
#include "Expr.h"
#include "Op.h"

using namespace std;

class Stmt: public Node {//���ڵ�
public:
	int after;
	static Stmt* StmtNULL;//�����
	static Stmt* Enclosing;//����break���

	Stmt(void);//�����﷨���Ĺ���
	bool operator==(const Stmt& rhs);
};


class If: public Stmt {//���if(E)S�Ĺ���
public:
	If(Expr* e, Stmt* s);
private:
	Expr* test;//E��Ӧ�Ľڵ�
	Stmt* stmt;//S��Ӧ�Ľڵ�
};

class Else: public Stmt {//else��䴦��
public:
	Else(Expr* e, Stmt* s1, Stmt* s2);
private:
	Expr* test;
	Stmt* stmt1;
	Stmt* stmt2;
};

class While: public Stmt {//while��䴦��
public:
	While();//����һ���ӽڵ�Ϊ�յĽڵ�
	void init(Expr* e, Stmt* s);//���ӽڵ�expr��ʼ��Ϊe��stmt��ʼ��Ϊs
private:
	Expr* test;
	Stmt* stmt;
};

class Do: public Stmt {//do���
public:
	Do();
	void init(Expr* e, Stmt* s);
private:
	Expr* test;
	Stmt* stmt;
};

class Set: public Stmt {//��ֵ��䴦��
public:
	Set(Id* i, Expr* e);
private:
	Id* id;
	Expr* exp;
};

class SetElem: public Stmt {//����Ԫ�ظ�ֵ����
public:
	SetElem(Access* x, Expr* e);
private:
	Id* array;
	Expr* index;
	Expr* exp;
};

class Break: public Stmt {//break��䴦��
public:
	Break();
private:
	Stmt* stmt;
};

class Seq: public Stmt {//ʵ��һ���������
public:
	Seq(Stmt* s1, Stmt* s2);//s1->stmt1 s2->stmt2
private:
	Stmt* stmt1;
	Stmt* stmt2;
};
