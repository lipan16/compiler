#include "Logical.h"

Logical::Logical(Token* tok, Expr* e1, Expr* e2): Expr(tok, NULL), exp1(e1), exp2(e2) {
	DataType *checkedType = check(e1->type, e2->type);
	type = checkedType;
	if (*type == *DataType::TypeNULL) {
		error("Type Error");
	}
};

string Logical::toString() const {
	return exp1->toString() + " " + op->toString() + " " + exp2->toString();
}



Or::Or(Token* tok, Expr* e1, Expr* e2):Logical(tok, e1, e2) {

}



And::And(Token* tok, Expr* e1, Expr* e2):Logical(tok, e1, e2) {

}



Not::Not(Token* tok, Expr* e):Logical(tok, e, e) {

}

string Not::toString() const {
	return op->toString() + " " + exp2->toString();
}



Rel::Rel(Token* tok, Expr* e1, Expr* e2):Logical(tok, e1, e2) {

}
