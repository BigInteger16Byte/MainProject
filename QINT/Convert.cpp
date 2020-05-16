#include"Convert.h"

//Prototype
string Div2String(string num, bool& bit);
string MultiStringTo2(string str);
string Power2String(int exp);
string Div2String(string num, bool& bit);



bool* Convert::DecToBin(QInt num) {
	bool* result = new bool[128];
	for (int i = 127; i >= 0; i--) {
		result[i] = num.GetBit(i);
	}

	return result;
}

QInt Convert::BinToDec(bool* bin) {
	int lengthOfbit = sizeof(bin) / (sizeof(*bin));
	QInt res;
	for (int i = 127; i >= 0; i--) {
		if (lengthOfbit >= 0) {
			res.SetBit(i, bin[lengthOfbit--]);
		}
		else {
			res.SetBit(i, 0);
		}
	}
	return res;
}

QInt Convert::ToBu2(QInt num) {
	QInt result;
	result = 0;
	result = ~num;;
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
	//Kiểm tra bit đầu
	if (x.GetBit(0) == 1) {
		x = Convert::ToBu2(x);
		result = "-";
	}
	string valueNotSign = "";
	for (int i = 127; i >= 0; i--) {
		if (x.GetBit(i) == 1) {//nếu là 1 thì mới cộng thêm
			valueNotSign = plusString(valueNotSign, Power2String(127 - i));
		}
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

	if (isNegative) {
		result = ToBu2(result);
	}

	return result;
}

/*------------ Các hàm hỗ trợ xử lý chuỗi---------------*/
string plusString(string a, string b) {
	{
		//Luon dat so dai hon ben tren
		if (a.length() < b.length()) {
			swap(a, b);
		}
		//Thuc hiện thao tác đặt phép cộng , thuật toán cơ ở tiểu học
		string res = "";
		int lengthA = a.length();
		int lengthB = b.length();
		int nho = 0; //Phép cộng sẽ có nhớ
		int resCol = 0; //Kết quả khi cộng xong tại 1 cột(%10)
		int endPlus = lengthA - lengthB; //Khi đã cộng xong hết cho B , các cột còn lại chỉ cần hạ xuống
		for (int i = lengthA - 1; i >= 0; i--) {
			//Kiểm tra xem hết phép cộng chưa
			if (i >= endPlus) {
				resCol = (int)(a[i] - '0') + (int)(b[i - endPlus] - '0') + nho;
			}
			else if (nho != 0) {   //Sau khi đã cộng hết b , thì check nhớ
				resCol = (int)(a[i] - '0') + nho;
			}
			else if (nho == 0) {  //hạ xuống
				resCol = (int)(a[i] - '0');
			}

			nho = resCol / 10;
			resCol %= 10;
			res += to_string(resCol);

		}

		//Nếu tại i=0 mà bit nhớ vẫn còn
		if (nho != 0) {
			res += to_string(nho);
		}

		//Vì kết quả đang lưu ngược nên phải revert lại
		string myResult = "";
		int length = res.length();
		for (int i = length - 1; i >= 0; i--) {
			myResult += res[i];
		}
		return myResult;
	}
}

string MultiStringTo2(string str) {
	//lưu giá trị đảo ngược của phép nhân
	string resTemp = "";
	//dùng thuật toán cơ bản của tiểu học:
	int length = str.length();
	int nho = 0;
	int resCol = 0;
	for (int i = length - 1; i >= 0; i--) {
		resCol = (int)(str[i] - '0') * 2 + nho;
		nho = resCol / 10;
		resCol %= 10;
		resTemp += to_string(resCol);
	}

	//Nếu bị tràn :
	if (nho != 0) {
		resTemp += to_string(nho);
	}

	string myResult = "";
	int myLength = resTemp.length();
	for (int i = myLength - 1; i >= 0; i--) {
		myResult += resTemp[i];
	}
	return myResult;
}

string Power2String(int exp) {
	string res = "1";

	if (exp < 0)  return 0;

	for (int i = 0; i < exp; i++) {
		res = MultiStringTo2(res);
	}
	return res;

}

string Div2String(string num , bool& bit) {  //Bit du sau khi chia 2
	if ((int)(num[num.length() - 1] - '0') % 2 == 0)
		bit = 0;
	else
		bit = 1;

	//chia cho 2 , cung la 1 thuat toan co ban tieu hoc
	int length = num.length();
	int resCol = 0;
	int mod = 0;
	string result = "";
	for (int i = 0; i < length; i++) {
		resCol = (int)(num[i] - '0') + mod * 10;
		mod = resCol % 2;
		resCol /= 2;
		if (resCol == 0 && i == 0) {   //Khi gia tri tai i = 0 < 2 thi khong them 0 vao
			continue;
		}
		result += to_string(resCol);
	}
	return result;
}