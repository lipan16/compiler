#include "Stmt.h"

Stmt* Stmt::StmtNULL = new Stmt();
Stmt* Stmt::Enclosing = Stmt::StmtNULL;

Stmt::Stmt(void) {}

bool Stmt::operator==(const Stmt& rhs) {
	return this->after == rhs.after && this->lexerLine == rhs.after;
}

void Stmt::gen(int b, int a) {

}



If::If(Expr* e, Stmt* s):test(e), stmt(s) {
	if (*test->type == *DataType::TypeBOOL) {//条件是bool类型

	} else {
		test->error("Require BOOL in If Stmt");//错误处理
	}
}

void If::gen(int b, int a) {
	int label = newLabel();
	test->jumping(0, a);
	emitLabel(label);
	stmt->gen(label, a);
}



Else::Else(Expr* e, Stmt* s1, Stmt* s2):test(e), stmt1(s1), stmt2(s2) {
	if (*test->type == *DataType::TypeBOOL) {//条件是bool类型

	} else {
		test->error("Require BOOL in If Stmt");
	}
}

void Else::gen(int b, int a) {
	int label1 = newLabel();
	int label2 = newLabel();
	test->jumping(0, label2);

	emitLabel(label1);
	stmt1->gen(label1, a);
	stringstream gt;
	gt << "goto L" << a;
	emit(gt.str());

	emitLabel(label2);
	stmt2->gen(label2, a);
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

void While::gen(int b, int a) {
	after = a;
	test->jumping(0, a);
	int label = newLabel();
	emitLabel(label);
	stmt->gen(label, b);

	stringstream gt;
	gt << "goto L" << b;
	emit(gt.str());
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

void Do::gen(int b, int a) {
	after = a;
	int label = newLabel();
	stmt->gen(b, label);
	emitLabel(label);
	test->jumping(b, 0);
}



Set::Set(Id* i, Expr* e):id(i), exp(e) {
	if (*check(id->type, exp->type) == *DataType::TypeNULL) {
		error("Type Error");
	}
}

void Set::gen(int b, int a) {
	emit(id->toString() + " = " + exp->gen()->toString());
}



SetElem::SetElem(Access* x, Expr* e): array(x->array), index(x->index), exp(e) {
	if (*check(x->type, exp->type) == *DataType::TypeNULL) {
		error("Type Error");
	}
}

void SetElem::gen(int b, int a) {
	string s1 = index->reduce()->toString();
	string s2 = exp->reduce()->toString();
	emit(array->toString() + " [ " + s1 + " ] = " + s2);
}



Break::Break() {
	if (*Stmt::StmtNULL == *Stmt::Enclosing) {
		error("Unenclosed Break");
	}
	stmt = Enclosing;
}

void Break::gen(int b, int a) {
	stringstream gt;
	gt << "goto L" << stmt->after;
	emit(gt.str());
}



Seq::Seq(Stmt* s1, Stmt* s2):stmt1(s1), stmt2(s2) {//实现一个语句序列

}

void Seq::gen(int b, int a) {
	if (*stmt1 == *Stmt::StmtNULL) {
		stmt2->gen(b, a);
	} else if (*stmt2 == *Stmt::StmtNULL) {
		stmt1->gen(b, a);
	} else {
		int label = newLabel();
		stmt1->gen(b, label);
		emitLabel(label);
		stmt2->gen(label, a);
	}
}
