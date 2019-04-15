#include "Word.h"

Word* Word::WordPLUS = new Word("++", OPERATION);
Word* Word::WordSUBS = new Word("--", OPERATION);
Word* Word::WordSE = new Word("-=", OPERATION);
Word* Word::WordADD = new Word("+", OPERATION);
Word* Word::WordAE = new Word("+=", OPERATION);
Word* Word::WordMUL = new Word("*", OPERATION);
Word* Word::WordME = new Word("*=", OPERATION);
Word* Word::WordDIV = new Word("/", OPERATION);
Word* Word::WordDE = new Word("/=", OPERATION);

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
	} else if (word.t_tag == AND ||word.t_tag == OR ||word.t_tag == EQ || word.t_tag == GE || word.t_tag == LE || word.t_tag == MINUS || word.t_tag == NE || word.t_tag == OPERATION) {
		os << "Operater£º";
	} else{
		os << "KeyWord: ";
	}
	os << word.w_lexme << "\n";
	return os;
}
