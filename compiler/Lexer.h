#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Word.h"
#include "DataType.h"

using namespace std;

extern std::ofstream io;

class Lexer {
public:
	static int line;//行号

	Lexer(string sourceFileName);//构造函数
	Token* scan();//扫描字符并分析
private:
	ifstream source;//源文件名
	char peekChar;//存储要读的字符
	vector<Word> words;//一个存储Word的序列 顺序表 向量

	void reserve(Word w);//在顺序表中末端插入数据
	Word* findByString(string& str);//查找是否是保留字
	void readChar();//读取一个字符
	bool readChar(char c);//返回将要读取的字符是否是字符c
};
