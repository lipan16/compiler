#pragma once
#include <map>
#include "Word.h"
#include "Expr.h"

using namespace std;

class Env {
public:
	Env(void);
	Env(Env* p);

	virtual ~Env(void);

	void put(Word w, Id i);
	Id get(const Word* w);
	friend ostream& operator<<(ostream& os, const Env& env);
private:
	Env *prev;
	map<Word, Id> table;
};

