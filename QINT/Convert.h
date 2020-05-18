#pragma once
/* My lib */
#include"QInt.h"

/* Default lib */
#include<iostream>
using namespace std;

class Convert {
	
public :
	/*               -----------------CONVERTERS-----------------           */

	/* BIN <-> DEC */
	static bool* DecToBin(QInt);
	static QInt BinToDec(bool*);
	
	/* BIN <-> HEX*/
	static string BinToHex(bool*);
	static QInt HexToBin(string);
	
	/* HEX<-> DEC */
	static QInt HexToDec(string);
	static string DecToHex(QInt);


	/*               -----------------OTHERS-----------------           */

	/* Method trung gian */
	static QInt ToBu2(QInt);

	/* Supporter */
	static string QIntToStringNumber(QInt); //support cho ham xuat
	static QInt StringNumberToQInt(string); // support cho ham nhap
};