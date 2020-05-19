﻿#pragma once

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


	/*               -----------------OVERLOADING-----------------           */

	/* Opeartor overloading */
	QInt& operator=(unsigned int);
	
	//QInt& operator - (QInt const&); // friend QInt operator + (QInt const &, QInt const &);
	//QInt& operator / (QInt const&); // friend QInt operator / (QInt const &, QInt const &);

	/* Shift */
	QInt& operator << (unsigned int); // friend QInt operator + (QInt const &, QInt const &);

	/* Rotate */
	QInt rotateRight();	// Mỗi lần chỉ cần xoay 1 bit (Đề yêu cầu)

	/* Bitwise */
	QInt& operator~();  // đảo bit nhưng không làm thay đổi data(Trả về 1 giá trị mới)
	QInt operator^(QInt);
	QInt operator+(QInt);
	QInt operator*(QInt);
	QInt operator>>(int);  //note
	QInt operator=(const QInt&);

	QInt& operator&(QInt const&);
	QInt& operator|(QInt const&);
	/* IO Overloading */
	friend ostream& operator<< (ostream&, const QInt);
	friend istream& operator>>(istream&, QInt&);



	/*               -------------------OTHERS-------------------           */

	/* Supporter */
	bool GetBit(int);
	void SetBit(int, bool);

	/* Output */
	string toDecString();
	string toBinaryString();
	string toHexString();


	/*               -----------------DESTRUCTOR-----------------           */

	~QInt() {};
};


/*               -----------------MỘT SỐ HÀM HỖ TRỢ TRONG VIỆC INPUT OUTPUT(xóa 0 thừa , thêm 0 cho đủ 128bit)-----------------           */
bool* stringToBin(string str);//Tam thoi chua dung toi // Input là 1 chuỗi , chuyển nó thành bin và thêm 0 vào cho đủ 128
string delete0(string str); //Khi convert ra string để output thì phải delete bớt 0