#pragma once
#include <string>
#include <cmath>
#include "Lexer.h"
#include "Token.h"
#include "DataType.h"
//#include "syntaxtree.h"
#include "Stmt.h"
#include "Env.h"
#include "Logical.h"

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

struct syntax_node { //�﷨���Ľ��
	int lexerLine;//�к�
	string str;
	struct syntax_node* bro;//�﷨��Ԫ�ֵܽ��
	struct syntax_node* son;//�﷨��Ԫ���ӽ��
};


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
	syntax_node* decls();//����decls�﷨��Ԫ decls -> decls decl |e
	DataType* type();//����type�﷨��Ԫ
	DataType* dims(DataType* p);//������������
	syntax_node* block();//����block�﷨��Ԫ block -> {decls stmts}
	syntax_node* stmts();//����stmts�﷨��Ԫ stmts -> stmts stmt |e
	syntax_node* stmt();//����stmt�﷨��Ԫ
	syntax_node* assign();//��ֵ���
	syntax_node* boolExpr();//����bool�﷨��Ԫ bool -> bool || join |join
	syntax_node* join();//����jioin�﷨��Ԫ
	syntax_node* equality();//����equality�﷨��Ԫ
	syntax_node* rel();//����rel�﷨��Ԫ
	syntax_node* expr();//����expr�﷨��Ԫ
	syntax_node* term();//����term�﷨��Ԫ
	syntax_node* unary();//����unary�﷨��Ԫ
	syntax_node* factor();//����factor�﷨��Ԫ
	//Access* offset(Id* a);//���������ַ

	syntax_node* makenode(string);
	void showtree(syntax_node*,int);
};
