#pragma once
#include <map>
#include "Word.h"
#include "Expr.h"

using namespace std;

class Env {//把字符串词法单元映射为类ID的对象
public:
	Env(void);
	Env(Env* p);
	void put(Word w, Id i);
	Id get(const Word* w);
	friend ostream& operator<<(ostream& os, const Env& env);
private:
	Env *prev;
	map<Word, Id> table;
};
