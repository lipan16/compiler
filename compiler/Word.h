#pragma once
#include "Token.h"
#include <iostream>

using namespace std;

class Word: public Token {//单词类
public:
	string w_lexme;

	Word();
	Word(string str, Tag t);

	virtual string toString() const;
	bool operator==(const Word& rhs);//w_lexme的比较
	friend bool operator<(const Word& lhs, const Word& rhs);//重载<运算符
	friend ostream& operator<<(ostream& os, const Word& word);

	static Word* WordPLUS;// ++
	static Word* WordSUBS;// --
	static Word* WordAE;// +=
	static Word* WordSE;// -=
	static Word* WordME;// *=
	static Word* WordDE;// /=
	
	static Word* WordAND;//&&
	static Word* WordOR;//||
	static Word* WordEQ;//==
	static Word* WordNE;//!=
	static Word* WordLE;//<=
	static Word* WordGE;//>=
	static Word* WordMINUS;//-
	static Word* WordTRUE;//true
	static Word* WordFALSE;//false
	static Word* WordTEMP;//temp
	static Word* WordNULL;//null
};