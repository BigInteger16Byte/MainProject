#include"QInt.h"
#include<iostream>
using namespace std;
int main() {
	QInt x;
	x = 123;
	for (int i = 0; i < 127; i++){
		cout << x.GetBit(i);
	}
	
}