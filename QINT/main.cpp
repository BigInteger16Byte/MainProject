#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;

//hàm này để in ra dãy 128 bit để test
void testBit(QInt x) {
	for (int i = 0; i < 128; i++) {
		cout << x.GetBit(i);
		if ((i+1)%32==0)  cout << endl;
	}
	cout << endl;
}

// Kiểm tra tràn số đầu vào
// Chuổi Bin dài hơn 128 kí tự
// Chuổi Dec dài hơn 39 kí tự or bằng 38 và lớn hơn chuổi "170141183460469231731687303715884105727" (so sánh chuổi 2^127 - 1)
// Chuổi Hex dài hơn 32 kí tự or bằng 32 và lớn hơn chuổi "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"


int main() {
<<<<<<< HEAD
	/*double c = pow(2,127);

	string k = to_string(c);
	cout << k;*/
	/*
	QInt a;
	cin >> a;
	a = a >> 2;
	cout << a;*/
	
	QInt a("788323282258381939236275890776");
	QInt b("-27388934683056007097503944712");

	cout << a / b;
=======
	
	QInt a, b;
	cin >> a;
	cin >> b;
	cout << a * b << endl;
>>>>>>> 008b9492db9d0b382de7af01a69884517a755388
}
