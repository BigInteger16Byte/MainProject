#pragma once
#include <stdio.h>
#include <string>
#include <iostream>

#define BIT32 32   //4 byte
class QInt {

private:
	int data[4];//Khởi tạo data 16 byte = 128 bit
public:
	QInt& operator=(unsigned int x);
	bool GetBit(int vt);
};