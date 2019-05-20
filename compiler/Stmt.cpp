#include "Stmt.h"

Stmt* Stmt::StmtNULL = new Stmt();
Stmt* Stmt::Enclosing = Stmt::StmtNULL;

Stmt::Stmt(void) {}

bool Stmt::operator==(const Stmt& rhs) {
	return this->after == rhs.after && this->lexerLine == rhs.after;
}



If::If(Expr* e, Stmt* s):test(e), stmt(s) {
	if (*test->type == *DataType::TypeBOOL) {//条件是bool类型

	} else {
		test->error("Require BOOL in If Stmt");//错误处理
	}
}



Else::Else(Expr* e, Stmt* s1, Stmt* s2):test(e), stmt1(s1), stmt2(s2) {
	if (*test->type == *DataType::TypeBOOL) {//条件是bool类型

	} else {
		test->error("Require BOOL in If Stmt");
	}
}



While::While() {
	test = Expr::ExprNULL;
	stmt = Stmt::StmtNULL;
}

void While::init(Expr* e, Stmt* s) {
	test = e;
	stmt = s;
	if (*test->type == *DataType::TypeBOOL) {

	} else {
		test->error("Require BOOL in While Stmt");
	}
}



Do::Do() {}

void Do::init(Expr* e, Stmt* s) {
	test = e;
	stmt = s;
	if (*test->type == *DataType::TypeBOOL) {

	} else {
		test->error("Require BOOL in Do-While Stmt");
	}
}



Set::Set(Id* i, Expr* e):id(i), exp(e) {
	if (*check(id->type, exp->type) == *DataType::TypeNULL) {
		error("Type Error");
	}
}



SetElem::SetElem(Access* x, Expr* e): array(x->array), index(x->index), exp(e) {
	if (*check(x->type, exp->type) == *DataType::TypeNULL) {
		error("Type Error");
	}
}


Break::Break() {
	if (*Stmt::StmtNULL == *Stmt::Enclosing) {
		error("Unenclosed Break");
	}
	stmt = Enclosing;
}



Seq::Seq(Stmt* s1, Stmt* s2):stmt1(s1), stmt2(s2) {//实现一个语句序列

}
