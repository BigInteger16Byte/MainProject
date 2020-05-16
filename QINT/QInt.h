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
	bool GetBit(int vt);
	void SetBit(int vt, bool bit);
	
	//Convert
	string convertQIntToString();

	//Cac ham chuyen doi se khong lam thay doi gia tri data , ma thay doi 1 bien result khac
	bool* ToBin();
	QInt BinToDec(bool *bin);
	QInt ToBu2();

};


/*------------ Các hàm hỗ trợ xử lý chuỗi---------------*/
//Cộng 2 chuỗi như số
string plusString(string a, string b);
//Hàm nhân cho 2 phục vụ tính lũy thừa 2
string MultiStringTo2(string str);
//lũy thừa 2 số như string   2^exp
string Power2String(int exp);