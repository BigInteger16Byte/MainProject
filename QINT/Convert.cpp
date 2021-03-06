﻿#include"Convert.h"

//Prototype
string plusString(string a, string b);
string MultiStringTo2(string str);
string Power2String(int exp);
string Div2String(string num, bool& bit);



string Convert::DecToBin(QInt num) {
	string result = "";
	for (int i = 0; i <128; i++) {
		if (num.GetBit(i) == 1) {
			result += "1";
		}
		else if (num.GetBit(i)==0) {
			result += "0";
		}
	}
	return result;
}
// Chổ này mà string bin ngắn hơn 128 kí tự là fail đó tân à
QInt Convert::BinToDec(string bin) {
	
	QInt res;
	for (int i = 127; i >= 0; i--) {
		if(bin[i]=='0') 
			res.SetBit(i, 0);
		else if(bin[i]=='1') 
			res.SetBit(i, 1);
	}
	return res;
}

/**
 * Chuyển đổi dãy số nhị phân thành mã hex
 * Tham số đầu vào: string tối đa 128 kí tự không bao gồm dấu -
 * Output: một string hex nhỏ nhất vừa đủ biểu diễn chuổi bin
 */
string Convert::BinToHex(string bin)
{
	// Trim số 0 ở đầu:
	for (int i = 0; i < bin.length(); i++) {
		if (bin[0]=='1') {
			break;
		}
		bin = bin.substr(1);
		i--;
	}

	// Trường hợp bin = "";
	if(bin.length() == 0 || bin.length() == 1)
		return "";

	string hexArr[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F" };

	string result = "";

	int surplus = 0; /* Lưu trữ số dư khi gom nhóm 4 bit và mod 16 */

	for (int i = bin.length() - 1; i >= 0; i -= 4) {

		/* Gom mỗi lần 4 bit lưu vào biến surplus */
		for (int j = 0; j < 4; j++) {
			if ((i - j) >= 0) {
				surplus += (bin[i - j] - '0') * (int)pow(2, j);
			}
		}

		surplus %= 16; // Lấy phần dư khi mod 16 đồng thời nó là index của hexArr

		result += hexArr[surplus];
		surplus = 0; // Reset lại biến
	}

	reverse(result.begin(), result.end());
	return string(result);
}

/**
 * Chuyển đổi dãy số hex thành mã nhị phân
 * Tham số đầu vào: string hex tùy ý (truthy) không bao gồm dấu -
 * Output: một string Bin vừa đủ của chuổi hex
*/
string Convert::HexToBin(string hex)
{
	string binArr[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };

	// result chứa string trung gian, pointer res trả về
	string result = ""; 
	bool* res = new bool[128];

	/* Chuyển từng kí tự của chuổi Hex thành 4-bit binary */
	for (int i = 0; i < hex.length(); i++) {
		// TH kí tự là số 0 -> 9
		if (hex[i] >= '0' && hex[i] <= '9') {
			result += binArr[hex[i] - '0'];
		}
		// TH kí tự là chử cái A -> F
		else {
			result += binArr[hex[i] - 55]; // const 55 ta có thể xem bảng mã ASCII mục đích A:65 -> cần lấy index 10 của arr nên sub 55
		}
	}

	// Trim số 0 ở đầu:
	for (int i = 0; i < result.length(); i++) {
		if (result[0] == '1') {
			break;
		}
		result = result.substr(1);
		i--;
	}

	// Trường hợp result = "";
	if (result.length() == 0 || result.length() == 1)
		return "";

	return (string)(result);
}

/**
 * Chuyển đổi dãy số Hex sang hệ dec
 * Tham số đầu vào: string hex tùy ý (truthy) không bao gồm dấu -
 * Output: một QInt biểu diễn số hex đó
*/
QInt Convert::HexToDec(string hex)
{
	/* HEX -> DEC: ta không nhất thiết phải chuyển trực tiếp mà thay vào đó ta tận dụng tài nguyên sẵn có */

	string bin = Convert::HexToBin(hex);  // Chuyển HEX -> BIN
	
	string chainZero = "";
	for (int i = 0; i < 128 - bin.length(); i++) {
		chainZero += "0";
	}
	bin = chainZero + bin;
	
	QInt dec = Convert::BinToDec(bin);	 // Chuyển BIN -> DEC

	return QInt(dec);
}

/**
 * Chuyển đổi dãy số Dec sang hệ Hex
 * Tham số đầu vào: QInt
 * Output: một string Hex biểu diễn số QInt đó
*/
string Convert::DecToHex(QInt dec)
{
	/* DEC -> HEX: ta không nhất thiết phải chuyển trực tiếp mà thay vào đó ta tận dụng tài nguyên sẵn có */

	string bin = Convert::DecToBin(dec);  // Chuyển DEC -> BIN
	string hex = Convert::BinToHex(bin);	 // Chuyển BIN -> HEX

	return string(hex);
}

QInt Convert::ToBu2(QInt num) {
	QInt result;
	result = 0;
	result = ~num;
	//+1 de chuyen sang bu 2
	int bitNho = 1;
	for (int i = 127; i >= 0; i--) {
		//Khi bit nhớ = 1 thì mới thực hiện cộng vào
		if (bitNho == 1) {
			bool curBit = result.GetBit(i);
			if (curBit == 1) {
				result.SetBit(i, 0);
			}
			else {
				bitNho = 0;
				result.SetBit(i, 1);
			}
		}
	}
	return result;
}

string Convert::QIntToStringNumber(QInt x) {
	string result = "";
	bool isFull0 = false;
	//Kiểm tra bit đầu
	if (x.GetBit(0) == 1) {
		x = Convert::ToBu2(x);  //Đảo từ âm lại thành số dương nhưng thêm dấu trừ
		result = "-";
	}
	string valueNotSign = "";
	for (int i = 127; i >= 0; i--) {
		if (x.GetBit(i) == 1) {//nếu là 1 thì mới cộng thêm
			valueNotSign = plusString(valueNotSign, Power2String(127 - i));
		}
	}
	if (valueNotSign == "") {
		valueNotSign = "0";
	}
	result += valueNotSign;
	return result;
}

QInt Convert::StringNumberToQInt(string num) {

	QInt result;
	bool isNegative = false;
	if (num[0] == '-') {
		isNegative = true;
		//Chuyen so dau tien thanh 0 de thuc hien phep chia
		num[0] = '0';
	}
	else if (num[0] == '+') {
		num[0] = '0';
	}
	bool bit;
	int vt = 127;
	while (num!="0" && num!="")
	{
		num = Div2String(num, bit);
		result.SetBit(vt, bit);
		vt--;
	}

	//Khi vị trí nhỏ hơn 0 => tràn số ( khi nhập )
	if (vt < 0) {
		return QInt("0");
	}

	if (isNegative) {
		result = ToBu2(result);
	}

	return result;
}
