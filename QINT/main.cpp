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


int main() {

}
