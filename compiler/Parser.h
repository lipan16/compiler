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

/*�ķ���
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
	Parser(Lexer* l);//�Ե�ǰ�ʷ�����һ���﷨������
	void error(string msg);//�������
	void match(int t);//ƥ��
	void program();//�﷨�����Ŀ�ʼ�������﷨��Ԫprogram��program -> block
private:
	Lexer* p_lex;//�﷨�������Ĵʷ�������
	Token* look;//��ǰ��һ���ʷ���Ԫ
	Env* top;//��ǰ�򶥲�ķ��ű�
	int used;//���ڱ����������ֵ��еĴ洢λ��

	void move();//����һ���ʷ���Ԫ
	void decls();//����decls�﷨��Ԫ decls -> decls decl |e
	DataType* type();//����type�﷨��Ԫ
	DataType* dims(DataType* p);//������������
	Stmt* block();//����block�﷨��Ԫ block -> {decls stmts}
	Stmt* stmts();//����stmts�﷨��Ԫ stmts -> stmts stmt |e
	Stmt* stmt();//����stmt�﷨��Ԫ
	Stmt* assign();//��ֵ���
	Expr* boolExpr();//����bool�﷨��Ԫ bool -> bool || join |join
	Expr* join();//����jioin�﷨��Ԫ
	Expr* equality();//����equality�﷨��Ԫ
	Expr* rel();//����rel�﷨��Ԫ
	Expr* expr();//����expr�﷨��Ԫ
	Expr* term();//����term�﷨��Ԫ
	Expr* unary();//����unary�﷨��Ԫ
	Expr* factor();//����factor�﷨��Ԫ
	Access* offset(Id* a);//���������ַ
};
