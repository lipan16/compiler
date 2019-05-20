#include <fstream>

#include "Lexer.h"
#include "Parser.h"

ofstream io;

int main() {
	io.open("result.txt", ios::out);
	if (!io.is_open()) {
		cout << "Fail to Open File for Output" << endl;
		exit(1);
	}

	Lexer *lex = new Lexer("source.txt");

	//Token* tok;	do { tok = lex->scan();	} while (tok != NULL);

	Parser parser(lex);	
	parser.program();
	cout << endl;
	system("pause");
	return 0;
}
