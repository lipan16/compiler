#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef enum tag {
	AND = 256, BASIC, BREAK, DO, ELSE, EQ, FALSE, GE, IF, ID,
	INDEX, LE, MINUS, NE, NUM, OR, REAL, TEMP, TRUE, WHILE, KEYWORD, OPERATION,
	TAG_NULL
	//类型划分：与运算，基本数据类型，break，do，else,==,false,>=,if,id,index,<=,min,-,!=,整数，或运算，实数，temp，true，while，关键字, 运算符, 定义空
} Tag; //其中index，temp为后面的语义分析作服务，and之所以从256开始是0-255给了ASCII编码的那些字符

class Token {
public:
	Tag t_tag;//枚举变量

	Token();
	Token(Tag t);//以t构造一个token对象，它的t_tag=t
	Token(char c);//以c构造一个token对象，它的t_tag=c
	virtual string toString() const;
	bool operator==(const Token& rhs) {//重载==运算符
		return this->t_tag == rhs.t_tag;
	}
	friend ostream& operator<<(ostream& os, const Token& tok);//重载<<输出流运算符
};

class Num: public Token {//整数类
public:
	const int n_value;

	Num(int val);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Num& tok);
};

class Real: public Token {//小数类
private:
	float r_value;
public:
	Real(float val);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Real& tok);
};