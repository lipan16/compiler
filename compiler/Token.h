#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef enum tag {
	BASIC = 256, BREAK, IF, ELSE, DO, WHILE, ID, INDEX, TRUE, FALSE,
	OR, AND, EQ, NE, LE, GE, PP, AE, SS, SE, ME, DE, MINUS,
	NUM, REAL, TEMP, KEYWORD, TAG_NULL
	//���ͻ��֣������������ͣ�break��if,else,do,while,id,index,true,false,||,&&,==,!=,<=,>=,++,+=,--,-=,*=,/=,-,��ֵ��ʵ����temp��keyword�����������
} Tag; //����index��tempΪ������������������and֮���Դ�256��ʼ��0-255����ASCII�������Щ�ַ�

class Token {
public:
	Tag t_tag;//ö�ٱ���

	Token();
	Token(Tag t);//��t����һ��token��������t_tag=t
	Token(char c);//��c����һ��token��������t_tag=c
	virtual string toString() const;
	bool operator==(const Token& rhs) {//����==�����
		return this->t_tag == rhs.t_tag;
	}
	friend ostream& operator<<(ostream& os, const Token& tok);//����<<����������
};

class Num: public Token {//������
public:
	const int n_value;

	Num(int val);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Num& tok);
};

class Real: public Token {//С����
private:
	float r_value;
public:
	Real(float val);
	virtual string toString() const;
	friend ostream& operator<<(ostream& os, const Real& tok);
};