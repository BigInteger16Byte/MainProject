#include"QInt.h"

QInt& QInt::operator =(unsigned int x) {
	for (int i = 0; i < 3; i++) {
		data[i] = 0;
	}
	data[3] = x;
	return *this;
}

bool QInt::GetBit(int vt) {
	//Tìm ra giá trị index trong data
	int index = vt / BIT32;
	//Với vt thì nó ứng với index bao nhiêu trong BIT32 ( dò cùng với index )
	int indexbit = BIT32 - 1 - vt % BIT32;
	return (data[index] >> indexbit) & 1;
}