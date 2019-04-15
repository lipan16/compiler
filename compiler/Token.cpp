#include "Token.h"
#include <sstream>

Token::Token() {

}

Token::Token(Tag t): t_tag(t) {

}

Token::Token(char t) : t_tag((Tag) t) {

}

string Token::toString() const {
	stringstream result;
	switch (t_tag) {
	case AND:
		result << "&&";		break;
	case OR:
		result << "||";		break;
	case EQ:
		result << "==";		break;
	case GE:
		result << ">=";		break;
	case LE:
		result << "<=";		break;
	case NE:
		result << "!=";		break;
	case BREAK:
		result << "break";		break;
	case DO:
		result << "do";		break;
	case WHILE:
		result << "while";		break;
	case IF:
		result << "if";		break;
	case ELSE:
		result << "else";		break;
	case FALSE:
		result << "false";		break;
	case TRUE:
		result << "true";		break;
	default:
		result << (char) t_tag;		break;
	}
	return result.str();//返回流中的内容
}

ostream& operator<<(ostream& os, const Token& tok) {
	os << tok.toString() << "\n";
	return os;
}



Num::Num(int val):Token(NUM), n_value(val) {//值写到n_value中

}

string Num::toString() const {
	stringstream result;
	result << n_value;
	return result.str();
}

ostream& operator<<(ostream& os, const Num& tok) {
	os << tok.toString() << "\n";
	return os;
}



Real::Real(float val):Token(REAL), r_value(val) {

}

string Real::toString() const {
	stringstream result;
	result << r_value;
	return result.str();
}

ostream& operator<<(ostream& os, const Real& tok) {
	os << tok.toString() << "\n";
	return os;
}