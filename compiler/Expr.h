#pragma once
#include "Node.h"
#include "Token.h"
#include "Word.h"
#include "DataType.h"

#include <sstream>
#include <iostream>

using namespace std;

class Expr: public Node {//表达式节点构造类，处理布尔表达式和跳转代码
public:
	Token* op;//该节点上的运算符
	DataType* type;//该节点类型
	static Expr* ExprNULL;

	Expr();
	Expr(Token* tok, DataType* p);//以运算符和类型构造一个节点对象
	bool operator==(const Expr& rhs);
	virtual Expr* gen();//返回一个“项”，该项可以成为一个三地址指令的右部。如给定一个表达式E=E1+E2,方法gen返回一个项x1+x2，其中x1，x2存放E1，E2值的地址，如果这个对象是一个地址就返回this值
	virtual Expr* reduce();//归约，把一个表达式计算成为一个单一的地址返回一个常量，标识符，或者临时名字
	virtual void jumping(int t, int f);
	virtual void emitJumps(string test, int t, int f);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Expr& expr);
};

class Id: public Expr {//叶子节点类
public:
	static Id* IdNULL;

	Id();
	Id(Token* id, DataType* p, int b);
	bool operator==(const Id& rhs);
	friend ostream& operator<<(ostream& os, const Id& id);
private:
	int offset;//该标识符的相对地址
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

	Constant(Token* tok, DataType* p);//构造一个标号为tok，类型为p的叶子节点
	Constant(int i);//重载，根据i创建一个常量对象
	friend ostream& operator<<(ostream& os, const Constant& constant);//重载输出<<运算符
	virtual void jumping(int t, int f);//布尔表达式的跳转
};