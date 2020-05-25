#include"QInt.h"
#include"Convert.h"
#include"SupportFunction.h"

QInt::QInt() {
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
	bool isOverFlow = false;
	bool isNegativeNumber = false;

	switch (flag) {
	case 0: { // src vao la chuoi Dec


	//check overflow
		if (compareTwoStringLikeNumber(src, UPPER_LIMIT) > 0)
			isOverFlow = true;
		if (compareTwoStringLikeNumber(src, LOWER_LIMIT) < 0)
			isOverFlow = true;


		int count = 0; // Biến đếm xem sau bao nhiêu lần chia string clone / 2 thì string clone thành ""
		bool surPlus; // Số dư mỗi lần chia

		// Nếu string là số âm thì tạm tách bỏ để tính
		if (src[0] == '-') {
			clone = clone.substr(1);
			isNegativeNumber = true;
		}

		// Chia 2 liên tục và lưu số dư vào vị trí tương ứng arr dummy
		while (clone.length() != 0) {
			clone = Div2String(clone, surPlus);
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
		if (len > 128) isOverFlow = true;

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
		*this = QInt("0");
	}

	if (isOverFlow == true)
		*this = QInt("0");
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
	QInt res;

	// Chuyen so b sang bu 2 de the hien so am va tien hanh cong voi a
	QInt numBu2 = Convert::ToBu2(num);

	int remain = 0; // So du
	int sum = 0;	// Temporary sum

	for (int i = 127; i >= 0; i--) {
		sum = this->GetBit(i) + numBu2.GetBit(i) + remain;

		res.SetBit(i, sum % 2);	// Set bit tai vi tri i la so du cua sum voi 2
		remain = sum / 2;			// Bien nho la so nguyen cua sum voi 2

		// Reset sum
		sum = 0;
	}

	return QInt(res);
}

QInt QInt::operator /(QInt num)
{

	// TH cơ sở:

	/* Nếu a == 0 => kq = 0, if b ==0 => kq = 0 (biểu thị phép tính không thực hiện được) */
	if (Convert::QIntToStringNumber(*this) == "0" || Convert::QIntToStringNumber(num) == "0") { // == "" là do method convert cua ong tra ve "" khi QInt = 0
		return QInt("0");
	}

	string A(128, '0'); // Contain surplus (số dư)

	if (this->GetBit(0)) {
		string A(128, '1'); // Contain surplus (số dư)
	}

	string Q = Convert::DecToBin(*this); // Contain quotient (thương)

	int k = 128; // Number of loop (k = n)

	int countFlagNegativeNumber = 0; // Đếm xem 2 số a và b có bao nhiêu số âm

	// Nếu số chia hoặc bị chia là số âm thì cứ chuyển nó về số dương và thực hiện phép tính. Sau đó mới quan tâm dấu trả về

	if (Q[0] == '1') {
		countFlagNegativeNumber++;
		Q = Convert::DecToBin(Convert::ToBu2(*this));
	}

	if (num.GetBit(0)) {
		countFlagNegativeNumber++;
		num = Convert::ToBu2(num);
	}

	while (k > 0) {

		// Dịch trái A:
		A += Q[0];
		A = A.substr(1);

		// Dịch trái Q:
		Q += "0";
		Q = Q.substr(1);

		// A - M:
		A = Convert::DecToBin(QInt(A, 1) - num);

		if (A[0] == '1') { // Nếu A - M < 0 thì gán lại kí tự cuối cùng của Qo = 0 và A = A + M;
			Q[127] = '0';
			A = Convert::DecToBin(QInt(A, 1) + num);
		}
		// Ngược lại thì gán Qo = 1;
		else {
			Q[127] = '1';
		}

		k--;
	}

	// Kiểm tra dấu trả về:
	if (countFlagNegativeNumber % 2) {
		return QInt(Convert::ToBu2(QInt(Q, 1)));
	}

	return QInt(QInt(Q, 1));
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

QInt QInt::rotateRight()
{
	string bin = Convert::DecToBin(*this);

	string endChar = bin.substr(bin.length() - 1);

	bin = endChar + bin;

	for (int i = 0; i < 128; i++) {
		this->SetBit(i, bin[i] == '0' ? 0 : 1);
	}

	return QInt(*this);
}

QInt QInt::rotateLeft() {
	QInt res = *this;
	bool mostLeft = res.GetBit(0);
	res = res << 1;
	res.SetBit(SIZE - 1, mostLeft);

	return res;
}

ostream& operator<<(ostream& out, QInt num) {
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

