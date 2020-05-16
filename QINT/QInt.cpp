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

	
	for (int i = 0; i < LENGTH; i++) {
		this->data[i] = ~this->data[i];
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
