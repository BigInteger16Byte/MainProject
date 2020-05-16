#include"QInt.h"
#include<iostream>
using namespace std;
int main() {
	QInt x;
	x = 123123;
	
	for (int i = 0; i < 128; i++) {
		cout << x.GetBit(i);
	}
	cout << endl;
	cout << x.convertQIntToString() << endl;
	/*cout << endl;
	bool* bit = x.ToBin();
	for (int i = 0; i < 128; i++) {
		cout << bit[i];
	}

	QInt test = x.ToBu2();

	cout << endl;
	for (int i = 0; i < 128; i++) {
		cout << test.GetBit(i);
	}*/

	
		
}