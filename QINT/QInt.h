#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
#define BIT32 32   //4 byte
#define LENGTH 4 // length of data
/*
Bitwise operator:
SHL : <<
SHR : >>
NOT : ~
AND : &
XOR : ^
OR : |
*/
class QInt {

private:
	int data[4];//Khởi tạo data 16 byte = 128 bit
public:
	QInt();
	QInt& operator=(unsigned int x);
	// đảo bit nhưng không làm thay đổi data(Trả về 1 giá trị mới)
	QInt& operator~();
	QInt operator^(QInt num);
	bool GetBit(int vt);
	void SetBit(int vt, bool bit);
	


	friend ostream& operator<< (ostream& op, const QInt num);
	friend istream& operator>>(istream& is, QInt& num);
};
