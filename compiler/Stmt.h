#pragma once
#include "Node.h"
#include "Expr.h"
#include "Op.h"

using namespace std;

class Stmt: public Node {//语句节点
public:
	int after;
	static Stmt* StmtNULL;//空语句
	static Stmt* Enclosing;//用于break语句

	Stmt(void);//抽象语法树的构造
	bool operator==(const Stmt& rhs);
};


class If: public Stmt {//语句if(E)S的构造
public:
	If(Expr* e, Stmt* s);
private:
	Expr* test;//E对应的节点
	Stmt* stmt;//S对应的节点
};

class Else: public Stmt {//else语句处理
public:
	Else(Expr* e, Stmt* s1, Stmt* s2);
private:
	Expr* test;
	Stmt* stmt1;
	Stmt* stmt2;
};

class While: public Stmt {//while语句处理
public:
	While();//创建一个子节点为空的节点
	void init(Expr* e, Stmt* s);//把子节点expr初始化为e，stmt初始化为s
private:
	Expr* test;
	Stmt* stmt;
};

class Do: public Stmt {//do语句
public:
	Do();
	void init(Expr* e, Stmt* s);
private:
	Expr* test;
	Stmt* stmt;
};

class Set: public Stmt {//赋值语句处理
public:
	Set(Id* i, Expr* e);
private:
	Id* id;
	Expr* exp;
};

class SetElem: public Stmt {//数组元素赋值处理
public:
	SetElem(Access* x, Expr* e);
private:
	Id* array;
	Expr* index;
	Expr* exp;
};

class Break: public Stmt {//break语句处理
public:
	Break();
private:
	Stmt* stmt;
};

class Seq: public Stmt {//实现一个语句序列
public:
	Seq(Stmt* s1, Stmt* s2);//s1->stmt1 s2->stmt2
private:
	Stmt* stmt1;
	Stmt* stmt2;
};
