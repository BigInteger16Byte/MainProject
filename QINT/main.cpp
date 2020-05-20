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
<<<<<<< HEAD
	/*string test = Convert::HexToBin("DB6227CE935D04010E3C3");

	if (test == "110110110110001000100111110011101001001101011101000001000000000100001110001111000011") {
		cout << "tu";
	}
	else {
		cout << "fal";
	}*/

	cout << Convert::HexToDec("A99FDF503E1DD54FCB92B24BE16A52FC");

	//-114812731097961891092328483067729915140
=======

>>>>>>> e114dd95f3b907cabc86331641e0b264a2c4d05d
}
