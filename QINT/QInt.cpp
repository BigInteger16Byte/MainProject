#include"QInt.h"
#include"Convert.h"

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

	QInt res;

	for (int i = 0; i < LENGTH; i++) {
		res.data[i] = ~this->data[i];
	}

	return res;
}

QInt QInt::operator^(QInt num) {
	QInt result;
	for (int i = 0; i < LENGTH; i++) {
		//xor từng cặp byte -> tự so bit
		result.data[i] = this->data[i] ^ num.data[i];
	}
	return result;
}

QInt QInt::operator+(QInt num) {
	QInt result;
	result = 0;
	int bitNho = 0; //Phep cong 2 bit thi bitNho toi da la 1
	for (int i = 127; i >= 0; i--) {
		int sum = this->GetBit(i) + num.GetBit(i) + bitNho;
		if (sum == 0) {
			bitNho = 0;
			result.SetBit(i, 0);
		}
		else if (sum == 1) {
			bitNho = 0;
			result.SetBit(i, 1);
		}
		else if (sum == 2) {
			bitNho = 1;
			result.SetBit(i, 0);
		}
		else if (sum == 3) {
			bitNho = 1;
			result.SetBit(i, 1);
		}
	}

	return result;
}

QInt QInt::operator*(QInt num) {
	//Ap dung thuat toan nhan voi so khong dau(chuyen so co dau thanh khong dau)
	bool bitNho = 0;
	QInt A;
	QInt temp = *this;
	int k = 127; //So bit cua num
	while (k >= 0) {
		bool endBitQ = num.GetBit(k);
		if (endBitQ == 1) {
			A = A + temp;
		}
		//Shift left để mỗi lần nhân theo cột thì lần nhân tiếp theo dồn qua trái ( thuật toán nhân tiểu học )
		//temp = temp << 1;
		k = k - 1; //Nhan 1 so trong num roi thi chuyen sang so tiep theo
	}

	return A;
	
}

QInt QInt::operator=(const QInt& QInt) {
	for (int i = 0; i < LENGTH; i++) {
		this->data[i] = QInt.data[i];
	}

	return *this;
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

QInt QInt::operator>>(int num) {
	QInt res;
	res = 0;
	for (int i = 0; i < LENGTH; i++) {
		res.data[i] = this->data[i] >> num;
	}
	return res;
}

ostream& operator<<(ostream& out,  QInt num){
	// TODO: insert return statement here
	out << Convert::QIntToStringNumber(num);
	return out;
}

istream& operator>>(istream& is, QInt& num) {
	string temp;
	is >> temp;
	num = Convert::StringNumberToQInt(temp);
	return is;
}


bool* stringToBin(string str) { // Input là 1 chuỗi , chuyển nó thành bin và thêm 0 vào cho đủ 128

	bool* bin = new bool[128];
	if (str.length() > 128) {
		cout << "tran so me roi kia" << endl;
	}
	int countBit = 127;
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == '1')
			bin[countBit] = 1;
		else if (str[i] == '0')
			bin[countBit] = 0;

		countBit--;
	}

	while (countBit >= 0)
	{
		bin[countBit] = 0;
		countBit--;
	}

	return bin;

}

string delete0(string str) {
	int vt = 0;
	for (vt = 0; vt < str.length(); vt++)
	{
		if (str[vt] != '0')
			break;
	}
	return str.substr(vt);
}