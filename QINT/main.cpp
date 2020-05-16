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

	QInt x2 = Convert::BinToDec(bit);
	cout << x2;
	
	
		
}