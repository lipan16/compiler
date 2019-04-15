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
	static int line;//�к�

	Lexer(string sourceFileName);//���캯��
	Token* scan();//ɨ���ַ�������
private:
	ifstream source;//Դ�ļ���
	char peekChar;//�洢Ҫ�����ַ�
	vector<Word> words;//һ���洢Word������ ˳��� ����

	void reserve(Word w);//��˳�����ĩ�˲�������
	Word* findByString(string& str);//�����Ƿ��Ǳ�����
	void readChar();//��ȡһ���ַ�
	bool readChar(char c);//���ؽ�Ҫ��ȡ���ַ��Ƿ����ַ�c
};
