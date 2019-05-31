#include "Word.h"

Word* Word::WordPLUS = new Word("++", PP);
Word* Word::WordSUBS = new Word("--", SS);
Word* Word::WordAE = new Word("+=", AE);
Word* Word::WordSE = new Word("-=", SE);
Word* Word::WordME = new Word("*=", ME);
Word* Word::WordDE = new Word("/=", DE);

Word* Word::WordAND = new Word("&&", AND);
Word* Word::WordOR = new Word("||", OR);
Word* Word::WordEQ = new Word("==", EQ);
Word* Word::WordNE = new Word("!=", NE);
Word* Word::WordLE = new Word("<=", LE);
Word* Word::WordGE = new Word(">=", GE);
Word* Word::WordMINUS = new Word("minus", MINUS);
Word* Word::WordTRUE = new Word("true", TRUE);
Word* Word::WordFALSE = new Word("false", FALSE);
Word* Word::WordTEMP = new Word("temp", TEMP);
Word* Word::WordNULL = new Word("null", TAG_NULL);

Word::Word(string str, Tag t):Token(t), w_lexme(str) {}

string Word::toString() const {
	return w_lexme;
}

bool Word::operator==(const Word& rhs) {
	return this->w_lexme.compare(rhs.w_lexme) == 0;
}

bool operator<(const Word& lhs, const Word& rhs) {
	return lhs.w_lexme.compare(rhs.w_lexme) < 0;
}

ostream& operator<<(ostream& os, const Word& word) {
	if (word.t_tag == ID) {
		os << "Word£º";
	} else if ((266 <= word.t_tag&&word.t_tag <= 278) || word.t_tag == '+' || word.t_tag == '*' || word.t_tag == '/') {
		os << "Operater£º";
	} else {
		os << "KeyWord: ";
	}
	os << word.w_lexme << "\n";
	return os;
}
