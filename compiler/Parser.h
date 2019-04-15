#pragma once
#include "Lexer.h"
#include "Token.h"
#include "Stmt.h"
#include "DataType.h"
#include "Env.h"
#include "Logical.h"
#include <string>

using namespace std;

extern std::ofstream io;

class Parser {
public:
	Parser(Lexer* l);

	void error(string msg);
	void match(int t);
	void program();

private:
	Lexer* p_lex;
	Token* look;
	Env* top;
	int used;

	void move();
	void decls();
	DataType* type();
	DataType* dims(DataType* p);

	Stmt* block();
	Stmt* stmts();
	Stmt* stmt();
	Stmt* assign();

	Expr* boolExpr();
	Expr* join();
	Expr* equality();
	Expr* rel();
	Expr* expr();
	Expr* term();
	Expr* unary();
	Expr* factor();
	Access* offset(Id* a);
};

