#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;
int main() {
	QInt x;
	cin >> x;
	
	bool* bit = Convert::DecToBin(x);
	for (int i = 0; i < 128; i++) {
		cout << bit[i];
	}
	cout << endl;

	QInt test = Convert::BinToDec(bit);

	cout << test;
		
	return 0;
	
		
}