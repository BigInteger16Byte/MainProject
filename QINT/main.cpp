#include"QInt.h"
#include"Convert.h"
#include<iostream>
using namespace std;

int main() {
	string test = Convert::HexToBin("DB6227CE935D04010E3C3");

	if (test == "110110110110001000100111110011101001001101011101000001000000000100001110001111000011") {
		cout << "tu";
	}
	else {
		cout << "fal";
	}
}
