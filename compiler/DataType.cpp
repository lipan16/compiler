#include "DataType.h"

DataType* DataType::TypeNULL = new DataType("null", TAG_NULL, 0);
DataType* DataType::TypeCHAR = new DataType("char", BASIC, 1);
DataType* DataType::TypeBOOL = new DataType("bool", BASIC, 1);
DataType* DataType::TypeFLOAT = new DataType("float", BASIC, 4);
DataType* DataType::TypeINT = new DataType("int", BASIC, 4);//int型，基本数据类型，数据宽度

DataType::DataType():Word("null", TAG_NULL), d_width(0) {}

DataType::DataType(string str, Tag t, int w) : Word(str, t), d_width(w) {}


bool DataType::operator==(const DataType& rhs) const {
	return this->w_lexme.compare(rhs.w_lexme) == 0 && this->d_width == rhs.d_width;
}

ostream& operator<<(ostream& os, const DataType& type) {
	os << "Basic Type: " << type.w_lexme << endl;
	return os;
}



bool DataType::numeric() const {//是否是数值型
	if (*this == *DataType::TypeINT || *this == *DataType::TypeFLOAT || *this == *DataType::TypeCHAR) {
		return true;
	} else {
		return false;
	}
}

DataType* max(DataType* p1, DataType* p2) {
	if (!p1->numeric() && !p2->numeric()) {//p1,p2都不是数值型
		return DataType::TypeNULL;
	} else if (*p1 == *DataType::TypeFLOAT || *p2 == *DataType::TypeFLOAT) {//有一个是float型，则数据类型是float型
		return DataType::TypeFLOAT;
	} else if (*p1 == *DataType::TypeINT || *p2 == *DataType::TypeINT) {//在不是float的基础上有一个是int型，则数据类型是int型
		return DataType::TypeINT;
	} else {
		return DataType::TypeCHAR;//数值型的优先级float,int,char
	}
}

DataType* check(DataType* p1, DataType* p2) {//检查一下两者类型是否一致
	if (*p1 == *DataType::TypeBOOL && *p2 == *DataType::TypeBOOL) {
		return DataType::TypeBOOL;
	} else if (*p1 == *DataType::TypeINT && *p2 == *DataType::TypeINT) {
		return DataType::TypeBOOL;
	} else if (*p1 == *DataType::TypeFLOAT && *p2 == *DataType::TypeFLOAT) {
		return DataType::TypeBOOL;
	} else if (*p1 == *DataType::TypeCHAR && *p2 == *DataType::TypeCHAR) {
		return DataType::TypeBOOL;
	} else {
		return DataType::TypeNULL;
	}
}