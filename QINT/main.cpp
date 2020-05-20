#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;

int main() {

	/*QInt x, y;
	cin >> x;
	cin >> y;
	cout << (x ^ y);*/

	/*string binCode = "111100101010111110100001";

	bool* bin;

	bin = new bool[128];

	for (int i = 0; i < 104; i++) {
		bin[i] = 0;
	}
	for (int i = 104; i < 128; i++) {
		bin[i] = binCode[i-104] - 48;
	}


	string res = Convert::BinToHex(bin);

	cout << res << endl;

	string a = "002B";
	bin = Convert::HexToBin(a);*/

	//Convert::HexToDec("002B");
	
	/*QInt x;
	cin >> x;
	x = Convert::ToBu2(x);
	cout << Convert::QIntToStringNumber(x) << endl;
	bool* c = Convert::DecToBin(x);

	for (int i = 0; i < 128; i++) {
		cout << c[i];
	}*/

	/*QInt* a = new QInt("-5");

	Convert::DecToHex(*a);*/

	cout << Convert::BinToHex("1111111111111011");

	return 0;		
}