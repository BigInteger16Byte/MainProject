#include"QInt.h"
#include"Convert.h"

string div2String(string num, bool& bit) {  //Bit du sau khi chia 2
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

QInt::QInt(){
	for (int i = 0; i < LENGTH; i++) {
		data[i] = 0;
	}
}

/**
 * Constructor (string, int flag)		// flag = 0 (default): String src type Dec
 * Tat ca deu chuyen ve bool*			// flag = 1: String src type Bin
 */										// flag = 2: String src type Hex

QInt::QInt(string src, int flag)
{
	string clone = src; // Clone dec
	bool* bin = new bool[128]; // Dummy arr

	bool isNegativeNumber = false;

	switch (flag) {
		case 0: { // src vao la chuoi Dec

			int count = 0; // Biến đếm xem sau bao nhiêu lần chia string clone / 2 thì string clone thành ""
			bool surPlus; // Số dư mỗi lần chia

			// Nếu string là số âm thì tạm tách bỏ để tính
			if (src[0] == '-') {
				clone = clone.substr(1);
				isNegativeNumber = true;
			}

			// Chia 2 liên tục và lưu số dư vào vị trí tương ứng arr dummy
			while (clone.length() != 0) {
				clone = div2String(clone, surPlus);
				bin[127 - count] = surPlus;
				count++;
			}

			// Khi số lần lặp không đủ chiều dài ar dummy thì thêm 0 vào 
			for (int i = 127 - count; i >= 0; i--) {
				bin[i] = 0;
			}

			// Setbit cho con trỏ this
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 32; j++) {
					this->SetBit(i * 32 + j, bin[i * 32 + j]);
				}
			}

			// Nếu là số âm thì ta lưu dưới dạng bù 2
			if (isNegativeNumber) {
				*this = Convert::ToBu2(*this);
			}

			/*cout << "Sau bu 2" << endl;
			for (int i = 0; i < 128; i++) {
				cout << this->GetBit(i);
			}
			cout << endl;*/

			break;
		}
		case 1: { // Truong hop src vao la string Bin

			bool addHead = 0;
			
			int len = src.length();

			// Neu string chua du 128 bit length thi them so 0 or 1 vao dau
			for (int i = 0; i < 128 - len; i++) {
				bin[i] = addHead;
			}

			// Gan src vao khuc sau cua Bin
			for (int i = 128 - len; i < 128; i++) {
				bin[i] = (src[i - 128 + len] == '0') ? 0 : 1;
			}

			// Setbit cho con trỏ this
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 32; j++) {
					this->SetBit(i * 32 + j, bin[i * 32 + j]);
				}
			}

			/*cout << "Sau bu 2" << endl;
			for (int i = 0; i < 128; i++) {
				cout << this->GetBit(i);
			}
			cout << endl;*/

			break;
		}
		case 2: { // Truong hop src vao la string Hex

			// Vi khong co dinh nghi so Hex am duong nen ta chuyn Hec thanh Bin va khong quan tam dau
			string binary = Convert::HexToBin(src);

			int len = binary.length();

			// Neu string chua du 128 bit length thi them so 0 or 1 vao dau
			for (int i = 0; i < 128 - len; i++) {
				bin[i] = 0;
			}

			// Gan binary vao
			for (int i = 128 - len; i < 128; i++) {
				bin[i] = binary[i - (128 - len)] == '0' ? 0 : 1;
			}

			// Setbit cho con trỏ this
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 32; j++) {
					this->SetBit(i * 32 + j, bin[i * 32 + j]);
				}
			}

			//cout << "Sau bu 2" << endl;
			//for (int i = 0; i < 128; i++) {
			//	cout << this->GetBit(i);
			//}
			//cout << endl;

			break;
		}

		default:
			*this = QInt("");
	}
}

QInt& QInt::operator =(unsigned int x) {
	for (int i = 0; i < 3; i++) {
		data[i] = 0;
	}
	data[3] = x;
	return *this;
}

QInt QInt::operator ~() {

	QInt res;
	res = 0;
	for (int i = 0; i < LENGTH; i++) {
		res.data[i] = ~this->data[i];
	}

	return res;
}

QInt QInt::operator ^(QInt num) {
	QInt result;
	for (int i = 0; i < LENGTH; i++) {
		//xor từng cặp byte -> tự so bit
		result.data[i] = this->data[i] ^ num.data[i];
	}
	return result;
}

/**
 * Nạp chồng toán tử &
 * Sử dụng: QInt res = (QInt)a & (QInt)b
 * Note: Trả về QInt mới, không thay đổi *this
*/
QInt QInt::operator &(QInt const& num)
{
	QInt result;

	for (int i = 0; i < LENGTH; i++) {
		//and từng bit tương ứng với nhau
		result.data[i] = this->data[i] & num.data[i];
	}

	return QInt(result);
}

/**
 * Nạp chồng toán tử |
 * Sử dụng: QInt res = (QInt)a | (QInt)b
 * Note: Trả về QInt mới, không thay đổi *this
*/
QInt QInt::operator |(QInt const& num)
{
	QInt result;

	for (int i = 0; i < LENGTH; i++) {
		//or từng bit tương ứng với nhau
		result.data[i] = this->data[i] | num.data[i];
	}

	return QInt(result);
}

QInt QInt::operator +(QInt num) {
	QInt result;
	result = 0;
	int bitNho = 0; //Phep cong 2 bit thi bitNho toi da la 1
	for (int i = 127; i >= 0; i--) {
		int sum = this->GetBit(i) + num.GetBit(i) + bitNho;
		result.SetBit(i, sum % 2);	// Set bit tai vi tri i la so du cua sum voi 2
		bitNho = sum / 2;
	}

	return result;
}

QInt QInt::operator *(QInt num) {
	//Ap dung thuat toan nhan voi so khong dau(chuyen so co dau thanh khong dau)
	bool bitNho = 0;
	QInt A;
	QInt temp = *this;
	if (num.GetBit(0) == 1 && temp.GetBit(0) == 1) {
		temp = Convert::ToBu2(temp);
		num = Convert::ToBu2(num);
	}
	int k = 127; //So bit cua num
	while (k >= 0) {
		bool endBitQ = num.GetBit(k);
		if (endBitQ == 1) {
			A = A + temp;
		}
		//Shift left để mỗi lần nhân theo cột thì lần nhân tiếp theo dồn qua trái ( thuật toán nhân tiểu học )
		temp = temp << 1;
		k = k - 1; //Nhan 1 so trong num roi thi chuyen sang so tiep theo
	}

	return A;
	
}

QInt QInt::operator =(const QInt& QInt) {
	for (int i = 0; i < LENGTH; i++) {
		this->data[i] = QInt.data[i];
	}

	return *this;
}

/**
 * Để trừ 2 a - b ta chuyển thành a + (-b)
 */
QInt QInt::operator-(QInt num)
{
	// Chuyen so b sang bu 2 de the hien so am va tien hanh cong voi a
	QInt numBu2 = Convert::ToBu2(num);

	int remain = 0; // So du
	int sum = 0;	// Temporary sum

	for (int i = 127; i >= 0; i--) {
		sum = this->GetBit(i) + numBu2.GetBit(i) + remain;

		this->SetBit(i, sum % 2);	// Set bit tai vi tri i la so du cua sum voi 2
		remain = sum / 2;			// Bien nho la so nguyen cua sum voi 2

		// Reset sum
		sum = 0;
	}

	return QInt(*this);
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

QInt QInt::operator<<(unsigned int num)
{
	// Convert *this -> string Bin
	string bin = Convert::DecToBin(*this);

	string header = bin.substr(0, num); // cat phan header roi chuyen thah 0 xong noi vao duoi
	bin = bin.substr(num);

	// Convert header -> string 0
	for (int i = 0; i < header.length(); i++) {
		header[i] = '0';
	}

	// Noi phan strong 0 vao duoi
	bin += header;

	// Dat lai bit
	for (int i = 0; i < 128; i++) {
		this->SetBit(i, bin[i] == '0' ? 0 : 1);
	}

	return QInt(*this);
}

QInt QInt::operator >>(unsigned int offset) {

	QInt res = *this;
	//Don bit sang phai , thuc hien phep don bit voi so lan offset
	for (int i = 0; i < offset; i++) {
		for (int j = SIZE - 1; j >= 1; j--) {
			res.SetBit(j, res.GetBit(j - 1));
		}
		if (res.GetBit(0) == 1) {
			res.SetBit(0, 1);
		}
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





// Tui vua update constructor co the tao QInt tu String Dec (-, +), string Bin, string Hex	:==D


//Tam thoi chua dung den
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