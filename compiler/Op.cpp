#include "Op.h"

Op::Op(Token* tok, DataType* p):Expr(tok, p) {

}



Expr* Op::reduce() {
	Expr* x = gen();
	Temp* temp = new Temp(type);
	stringstream result;
	result << temp->toString() << " = " << x->toString();
	emit(result.str());
	return temp;
}

Arith::Arith(Token* tok, Expr* e1, Expr* e2):Op(tok, NULL), exp1(e1), exp2(e2) {
	type = max(exp1->type, exp2->type);
	if (*type == *DataType::TypeNULL) {
		error("Type Error");
	}
};



Expr* Arith::gen() {
	return new Arith(op, exp1->reduce(), exp2->reduce());
}

string Arith::toString() const {
	return exp1->toString() + " " + op->toString() + " " + exp2->toString();
}


Unary::Unary(Token* tok, Expr* e):Op(tok, NULL), exp(e) {
	//exp = new Expr(*e);

	type = max(DataType::TypeINT, e->type);
	if (*type == *DataType::TypeNULL) {
		error("Type Error");
	}
};


Expr* Unary::gen() {
	return new Unary(op, exp->reduce());
}

string Unary::toString() const {
	return op->toString() + " " + exp->toString();
}


Access::Access(Id* a, Expr* i, DataType* p): Op(new Word("[]", INDEX), p), array(a), index(i) {

}

Expr* Access::gen() {
	return new Access(array, index->reduce(), type);
}

void Access::jumping(int t, int f) {
	emitJumps(reduce()->toString(), t, f);
}

string Access::toString() const {
	return array->toString() + " [ " + index->toString() + " ] ";
}