#include "Id.h"
#include "Lexer.h"

Id* Id::IdNULL = new Id();

Id::Id() {}

Id::Id(Token* id, DataType* p, int b):op(id), type(p), offset(b) {

}

bool Id::operator==(const Id& rhs) {
	return this->op == rhs.op && this->type == rhs.type && this->offset == rhs.offset;
}

void Id::error(string str) {
	cerr << "Near Line " << lexerLine << ": " << str << endl;
	io << "Near Line " << lexerLine << ": " << str << endl;
}

ostream& operator<<(ostream& os, const Id& id) {
	os << *(id.type) << "Offset: " << id.offset << endl;
	return os;
}
