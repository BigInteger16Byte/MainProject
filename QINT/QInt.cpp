#include"QInt.h"


QInt::QInt(){
	for (int i = 0; i < LENGTH; i++) {
		data[i] = 0;
	}
}
QInt& QInt::operator =(unsigned int x) {
	for (int i = 0; i < 3; i++) {
		data[i] = 0;
	}
	data[3] = x;
	return *this;
}

QInt& QInt::operator~() {

	QInt result;
	result = 0;
	for (int i = 0; i < LENGTH; i++) {
		result.data[i] = ~data[i];
	}

	return result;
}


bool QInt::GetBit(int vt) {
	//Tìm ra giá trị index trong data
	int index = vt / BIT32;
	//Với vt thì nó ứng với index bao nhiêu trong BIT32 ( dò cùng với index )
	int indexbit = BIT32 - 1 - vt % BIT32;
	return (data[index] >> indexbit) & 1;
}


void QInt::SetBit(int vt, bool  bit) {
	//Tìm ra giá trị index trong data
	int index = vt / BIT32;
	//Với vt thì nó ứng với index bao nhiêu trong BIT32 ( dò cùng với index )
	int indexbit = BIT32 - 1 - vt % BIT32;

	//công thức bật / tất bit như trong lý thuyết cô đã dạy
	if (bit == 1) {
		data[index] = (1 << indexbit) | data[index];
	}
	else {
		data[index] = ~(1 << indexbit) & data[index];
	}
}

bool* QInt::ToBin() {
	bool* result = new bool[128];
	for (int i = 127; i >= 0; i--) {
		result[i] = GetBit(i);
	}

	return result;
}

QInt QInt::BinToDec(bool* bin) {
	QInt res;
	for (int i = 127; i >= 0; i--) {
		res.SetBit(i, bin[i]);
	}
	return res;
}

QInt QInt::ToBu2() {
	QInt result;
	result = 0;
	result = ~*this;;
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

string QInt::convertQIntToString() {
	string result = "";
	//Kiểm tra bit đầu
	if (this->GetBit(0) == 1) {
		*this = this->ToBu2();
		result = "-";
	}
	string valueNotSign = "";
	for (int i = 127; i >= 0; i--) {
		if (this->GetBit(i) == 1){//nếu là 1 thì mới cộng thêm
			valueNotSign = plusString(valueNotSign, Power2String(127 - i));
		}
	}
	result += valueNotSign;
	return result;
}

/*------------ Các hàm hỗ trợ xử lý chuỗi---------------*/
string plusString(string a , string b) {
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