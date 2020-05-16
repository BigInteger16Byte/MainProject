#pragma once
#include"QInt.h"
class Convert {
	
public : 
	static bool* DecToBin(QInt num);
	static QInt BinToDec(bool* bin);
	static QInt ToBu2(QInt num);
	static string QIntToStringNumber(QInt num); //support cho ham xuat
	static QInt StringNumberToQInt(string str); // support cho ham nhap
};