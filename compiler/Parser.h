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

/*文法：
program -> block
block   -> { decls stmts }
decls   -> decls decl |e
decl	-> type id ;
type	-> type [ Num ] 
		-> basic
stmts	-> stmts stmt |e
stmt	-> loc = bool
		-> if ( bool ) stmt
		-> if ( bool ) else stmt
		-> while ( bool ) stmt
		-> do stmt while ( bool ) ;
		-> break ;
		-> block
loc		-> loc [ bool ]
		-> id
bool	-> bool || join
		-> join
join	-> join && equality
		-> equality
equality-> equality == rel
		-> equality != rel
		-> rel
rel		-> expr < expr
		-> expr <= expr
		-> expr >= expr
		-> expr > expr
		-> expr
expr	-> expr + term
		-> expr - term
		-> term
term	-> term * unary
		-> term / unary
		-> unary
unary	-> ! unary
		-> - unary
		-> factor
factor	-> ( bool )
		-> loc
		-> num
		-> real
		-> true
		-> false

*/


class Parser {
public:
	Parser(Lexer* l);//以当前词法构造一个语法分析器
	void error(string msg);//错误输出
	void match(int t);//匹配
	void program();//语法分析的开始，最大的语法单元program，program -> block
private:
	Lexer* p_lex;//语法分析器的词法分析器
	Token* look;//向前看一个词法单元
	Env* top;//当前或顶层的符号表
	int used;//用于变量声明在字典中的存储位置

	void move();//读下一个词法单元
	void decls();//处理decls语法单元 decls -> decls decl |e
	DataType* type();//处理type语法单元
	DataType* dims(DataType* p);//处理数组类型
	Stmt* block();//处理block语法单元 block -> {decls stmts}
	Stmt* stmts();//处理stmts语法单元 stmts -> stmts stmt |e
	Stmt* stmt();//处理stmt语法单元
	Stmt* assign();//赋值语句
	Expr* boolExpr();//处理bool语法单元 bool -> bool || join |join
	Expr* join();//处理jioin语法单元
	Expr* equality();//处理equality语法单元
	Expr* rel();//处理rel语法单元
	Expr* expr();//处理expr语法单元
	Expr* term();//处理term语法单元
	Expr* unary();//处理unary语法单元
	Expr* factor();//处理factor语法单元
	Access* offset(Id* a);//计算数组地址
};
