#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;
void Test_CoutBit(QInt x) {
	for (int i = 0; i <128; i++) {
		cout << x.GetBit(i);
	}
	cout << endl;
}
int main() {

	QInt x, y;
	cin >> x;

	Test_CoutBit(x);
	x = x >> 2;
	Test_CoutBit(x);
	cout << x;

		
	return 0;
	
		
}