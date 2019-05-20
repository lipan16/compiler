#include "Op.h"

Op::Op(Token* tok, DataType* p):Expr(tok, p) {

}



Arith::Arith(Token* tok, Expr* e1, Expr* e2):Op(tok, NULL), exp1(e1), exp2(e2) {
	type = max(exp1->type, exp2->type);
	if (*type == *DataType::TypeNULL) {
		error("Type Error");
	}
};

string Arith::toString() const {
	return exp1->toString() + " " + op->toString() + " " + exp2->toString();
}



Unary::Unary(Token* tok, Expr* e):Op(tok, NULL), exp(e) {
	type = max(DataType::TypeINT, e->type);
	if (*type == *DataType::TypeNULL) {
		error("Type Error");
	}
};

string Unary::toString() const {
	return op->toString() + " " + exp->toString();
}



Access::Access(Id* a, Expr* i, DataType* p): Op(new Word("[]", INDEX), p), array(a), index(i) {

}

string Access::toString() const {
	return array->toString() + " [ " + index->toString() + " ] ";
}