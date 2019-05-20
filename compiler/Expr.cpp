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



int Temp::count = 0;

Temp::Temp(DataType* p): Expr(Word::WordTEMP, p) {
	number = ++count;
}

string Temp::toString() const {
	stringstream result;
	result << "t" << number;
	return result.str();
}

ostream& operator<<(ostream& os, const Temp& temp) {
	os << "Temp " << temp.toString() << endl;
	return os;
}



Constant* Constant::ConstantTRUE = new Constant(Word::WordTRUE, DataType::TypeBOOL);
Constant* Constant::ConstantFALSE = new Constant(Word::WordFALSE, DataType::TypeBOOL);

Constant::Constant(Token* tok, DataType* p): Expr(tok, p) {

}

Constant::Constant(int i) : Expr(new Num(i), DataType::TypeINT) {

}

ostream& operator<<(ostream& os, const Constant& constant) {
	os << "Constant Item: ";
	os << *(constant.op) << " " << *(constant.type) << endl;
	return os;
}