#pragma once
#include <map>
#include "Id.h"

using namespace std;

class Env {//运行环境
private:
	Env *prev;
	map<Word, Id> table;
public:
	Env(void);
	Env(Env* p);
	void put(Word w, Id i);
	Id get(const Word* w);
	friend ostream& operator<<(ostream& os, const Env& env);
};
