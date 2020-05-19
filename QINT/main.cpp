#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;

int main() {

	QInt test;
	cin >> test;
	string a = Convert::DecToBin(test);
	

	QInt test2 = Convert::BinToDec(a);
	cout << test2 << endl;
}

