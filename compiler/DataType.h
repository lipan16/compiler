#pragma once
#include <iostream>
#include <sstream>
#include "Word.h"

using namespace std;

class DataType: public Word {//数据类型类
public:
	int d_width;

	bool numeric() const;//是否是数值型int,char,float

	DataType();
	DataType(string str, Tag t, int w);

	bool operator==(const DataType& rhs) const;
	friend ostream& operator<<(ostream& os, const DataType& type);

	static DataType* TypeINT;
	static DataType* TypeFLOAT;
	static DataType* TypeCHAR;
	static DataType* TypeBOOL;
	static DataType* TypeNULL;
};

DataType* max(DataType* p1, DataType* p2);
DataType* check(DataType* p1, DataType* p2);

class Array: public DataType {//数组类
public:
	int a_size;//数组长度
	DataType* a_of;//数据类型

	Array(int sz, DataType* p);
	virtual string toString() const;
};
