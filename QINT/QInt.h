#pragma once

/* Default lib */
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

	/*               -----------------CONSTRUCTOR-----------------           */

	QInt();
	QInt(string);



	/*               -----------------OVERLOADING-----------------           */

	/* Opeartor overloading */
	QInt& operator=(unsigned int);
	
	QInt operator - (QInt const&); // friend QInt operator + (QInt const &, QInt const &);
	QInt operator / (QInt const&); // friend QInt operator / (QInt const &, QInt const &);

	/* Shift  */
	QInt& operator << (unsigned int); // friend QInt operator + (QInt const &, QInt const &);

	/* Rotate */
	QInt& rotateRight();	// Mỗi lần chỉ cần xoay 1 bit (Đề yêu cầu)

	/* Bitwise */
	QInt& operator~();  // đảo bit nhưng không làm thay đổi data(Trả về 1 giá trị mới)
	QInt operator^(QInt);
	QInt operator&(QInt const&);
	QInt operator|(QInt const&);

	/* IO Overloading */
	friend ostream& operator<< (ostream&, const QInt);
	friend istream& operator>>(istream&, QInt&);



	/*               -------------------OTHERS-------------------           */

	/* Supporter */
	bool GetBit(int);
	void SetBit(int, bool);



	/*               -----------------DESTRUCTOR-----------------           */

	~QInt() {};
};
