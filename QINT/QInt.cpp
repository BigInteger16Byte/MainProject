#include"QInt.h"

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

//QInt& operator~(QInt num) {
//	QInt result;
//	result = 0;
//	for (int i = 0; i < LENGTH; i++) {
//		result.data[i] = ~num.data[i];
//	}
//
//	return result;
//}

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

//Các thao tác chuyển đổi

//QInt QInt::Bu2() {
//	//Đảo bit
//	
//}

bool* QInt::ToBin() {
	bool* result = new bool[128];
	for (int i = 127; i >= 0; i--) {
		result[i] = GetBit(i);
	}

	return result;
}

