#include "Expr.h"

Expr* Expr::ExprNULL = new Expr();

Expr::Expr() {}

Expr::Expr(Token* tok, DataType* p):op(tok), type(p) {//构造一个节点对象

}

bool Expr::operator==(const Expr& rhs) {
	return this->op == rhs.op && this->type == rhs.type;
}

string Expr::toString() const {
	return op->toString();
}

ostream& operator<<(ostream& os, const Expr& expr) {
	os << "Expr Item: ";
	os << "Op " << expr.op << " Type " << expr.type << endl;
	return os;
}



Id* Id::IdNULL = new Id();

Id::Id() {}

Id::Id(Token* id, DataType* p, int b):Expr(id, p), offset(b) {

}

bool Id::operator==(const Id& rhs) {
	return this->op == rhs.op && this->type == rhs.type && this->offset == rhs.offset;
}

ostream& operator<<(ostream& os, const Id& id) {
	os << *(id.type) << "Offset: " << id.offset << endl;
	return os;
}
