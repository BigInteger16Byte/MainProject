#include"QInt.h"
#include"Convert.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;


// Ta quy uoc: 0 (he 10), 1(he 2), 2(he 16)
int getFormat(string val) {
    if (val == "2") {// Tinh toan tren he 2
        return 1;
    }
    if (val == "10") {// Tinh toan tren he 10
        return 0;
    }
    if (val == "16") {// Tinh toan tren he 16
        return 2;
    }
}


void writeToFile(ofstream& out, int formatDes, QInt num) {
	string res = "";
	{
		if (formatDes == 0) { // Chuyen thanh he 10
			res = Convert::QIntToStringNumber(num);
			out << delete0(res) << endl;
		}
		if (formatDes == 1) { // Chuyen thanh he 2
			res = Convert::DecToBin(num);

			// Trim 0 header
			out << delete0(res) << endl;
		}
		if (formatDes == 2) { // Chuyen thanh he 16
			res = Convert::DecToHex(num);
			out << delete0(res) << endl;
		}
	}
}


void testBit(QInt x) {
	for (int i = 0; i < 128; i++) {
		cout << x.GetBit(i);
		if ((i + 1) % 32 == 0)  cout << endl;
	}
	cout << endl;
}

// Kiểm tra tràn số

/* Tràn trên */
// Chuổi Bin dài hơn 128 kí tự
// Chuổi Dec dài hơn 39 kí tự or bằng 39 và lớn hơn chuổi "170141183460469231731687303715884105727" (so sánh chuổi 2^127 - 1) , Miền giá trị [ -2^127 , 2^127-1 ]
// Chuổi Hex dài hơn 32 kí tự, max: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" 32F

/* Tràn dưới */
// Chuổi Bin dài hơn 128 kí tự
// Chuổi Dec dài hơn 40 kí tự (thêm dấu trừ của số âm) or bằng 30 và nhỏ hơn chuổi "-170141183460469231731687303715884105728" (so sánh chuổi -2^127) , Miền giá trị [ -2^127 , 2^127-1 ]
// Chuổi Hex bé hơn "0", không âm

// Nhưng mà nếu phần dài hơn đó toàn là số 0 thì nó vẫn đúng
//https://stackoverflow.com/questions/30394086/integer-division-overflows
//https://www.geeksforgeeks.org/check-integer-overflow-multiplication/
//https://stackoverflow.com/questions/1633561/how-to-detect-overflow-when-subtracting-two-signed-32-bit-numbers-in-c
//https://www.geeksforgeeks.org/check-for-integer-overflow/
//https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

//bool isOverflow(string src, int format = 0) {
//    /* Bin overflow */
//    string cloneSrc = src;
//
//    switch (format)
//    {
//    case 0: { // default he Dec
//        if (cloneSrc[0] != '-') {
//            // So duong
//            cloneSrc = delete0(cloneSrc); // xoa so 0 o dau
//
//            if (cloneSrc.length() > 39 || (cloneSrc.length() == 39 && cloneSrc > "170141183460469231731687303715884105727")) {
//                return false;
//            }
//        }
//        else {
//            // So am
//            cloneSrc = cloneSrc.substr(1); // cat bo dau tru
//            cloneSrc = delete0(cloneSrc); // xoa so 0 o dau
//
//            if (cloneSrc.length() > 39 || (cloneSrc.length() == 39 && cloneSrc > "170141183460469231731687303715884105728")) {
//                return false;
//            }
//        }
//
//        break;
//    }
//
//    case 1: { // He Bin
//        if (cloneSrc.length() > 128) {
//            return false;
//        }
//
//        break;
//    }
//
//    case 2: { // He Hex
//        cloneSrc = delete0(cloneSrc); // xoa so 0 o dau
//
//        if (cloneSrc.length() > 32) {
//            return false;
//        }
//
//        break;
//    }
//
//    default:  
//        return true;
//    }
//}


// So sanh 2 QInt xem thang nao lon hon (a>b => 1, a<b => -1, a=b => 0)
int compareTwoQInt(QInt a, QInt b) {
    bool signA = a.GetBit(0);
    bool signB = b.GetBit(0);

    // Kiểm tra trường hợp cơ sở: số âm luôn nhỏ hơn số dương và ngược lại 
    if (signA == 0 && signB == 1) {
        return 1; // a > b
    }
    if (signA == 1 && signB == 0) {
        return -1; // a < b
    }

    // Nếu 2 số cùng là số dương thì ta só sánh đô dài và so sánh chuổi
    if (signA == 0) {
        string decA = Convert::QIntToStringNumber(a);
        string decB = Convert::QIntToStringNumber(b);

        if (decA == decB) {
            return 0;
        }
        if (decA.length() > decB.length()) {
            return 1;
        }
        if (decA.length() < decB.length()) {
            return -1;
        }
        if (decA > decB) {
            return 1;
        }
        else {
            return -1;
        }
    }

    // Tương tự th 2 số cùng dương, ở đây ta tách dấu trừ đi và kiểm tra
    if (signA == 1) { // Số âm
        string decA = Convert::QIntToStringNumber(a).substr(1); // bo dau -
        string decB = Convert::QIntToStringNumber(b).substr(1); // bo dau -

        if (decA == decB) {
            return 0;
        }
        if (decA.length() > decB.length()) {
            return -1;
        }
        if (decA.length() < decB.length()) {
            return 1;
        }
        if (decA > decB) {
            return -1;
        }
        else {
            return 1;
        }
    }
}

// Kiểm tra quá trình tính toán có xãy ra overflow hay không
// Tham số đầu vào: số a, số b, kết quả của phép tính, toán tử
// Đầu ra: nếu phat hiện tràn trả về 1, không tràn trả về 0
bool isDeadthZone(QInt a, QInt b, QInt res, char opera) {

    //overflow on number
    
    switch (opera) {
        case '+': { // Add
            if (a.GetBit(0) == 0 && b.GetBit(0) == 0 && res.GetBit(0) == 1) {
                return true;
            }
            if (a.GetBit(0) == 1 && b.GetBit(0) == 1 && res.GetBit(0) == 0) {
                return true;
            }
            return false;

            break;
        }
        case '-': { // Sub
            if ((compareTwoQInt(res, a) == -1 ? 1 : 0) != compareTwoQInt(b, QInt("0")) == 1 ? 1 : 0) {
                return true;
            }

            return false;

            break;
        }
        case '*': { // Multi
            if (compareTwoQInt(a, QInt("0")) == 0 || compareTwoQInt(b, QInt("0")) == 0) {
                return false; // Neu a=0 or b=0 thi se ko tran
            }
            if (Convert::QIntToStringNumber(a) == LOWER_LIMIT && Convert::QIntToStringNumber(b) == "-1") {
                return true;
            }
            if (Convert::QIntToStringNumber(a) == "-1" && Convert::QIntToStringNumber(b) == LOWER_LIMIT) {
                return true;
            }
            if (Convert::QIntToStringNumber(a) == Convert::QIntToStringNumber(res / b)) {
                return false;
            }

            return true;

            break;
        }
        case '/': { // Div
            if (Convert::QIntToStringNumber(a) == LOWER_LIMIT && Convert::QIntToStringNumber(b) == "-1") {
                return true;
            }

            return false;

            break;
        }
    }
}

int main(int argc, char* argv[]) {


    ifstream inFile;
    ofstream outFile;

    if (argc < 3) {
        cout << "The format must be correct" << endl;
        cout << "Format : <name>.exe <input>.txt <output>.txt" << endl;
        return 0;
    }
    else {
        inFile.open(argv[1]);
        outFile.open(argv[2]);
    }

    string line = ""; // Moi lan doc 1 dong cua file
    int lenLine = 0; // length of line
    vector<string> items; // Luu cac substr khi cat line voi delim " "

    // Luu yeu tinh toan tren he co so may va tra ve he co so may
    int formatSrc;
    int formatDes;
    string res = ""; // De luu ket qua cuoi cung khi thuc hien cac phep tinh va ghi xuong file

    while (getline(inFile, line)) {

        if (line.length() > 0) {

            lenLine = line.length(); // get length

            // Cat chuoi thanh 1 array cac string voi delim = " "
            int pos = 0; // Luu vi tri phat hien  " "
            for (int i = 0; i < lenLine; i++) {
                if (line[i] == ' ') {
                    items.push_back(line.substr(pos, i - pos));
                    pos = i + 1;
                }
            }
            items.push_back(line.substr(pos));

            // Xet cac truong hop:
            switch (items.size()) {
            case 3: { // Neu arr co 3 phan tu thi string line co 2 space.

                // Voi 2 space ta co cac phep toan: chuyen co so, rol, ror, ~ bit
                if (items.at(1) == "rol") {
                    // Luu yeu cau dau vao dau ra.

                    formatSrc = getFormat(items.at(0));
                    formatDes = getFormat(items.at(0));

                    QInt dummy(items.at(2), formatSrc); // khoi tao QInt tu string he 10
                    dummy = dummy.rotateLeft();

                    {
                        writeToFile(outFile, formatDes, dummy);
                    }

                    break;
                }

                if (items.at(1) == "ror") {
                    // Luu yeu cau dau vao dau ra.

                    formatSrc = getFormat(items.at(0));
                    formatDes = getFormat(items.at(0));

                    QInt dummy(items.at(2), formatSrc); // khoi tao QInt tu string he 10
                    dummy.rotateRight();

                    res = Convert::QIntToStringNumber(dummy);

                    {
                        writeToFile(outFile, formatDes, dummy);
                    }

                    break;
                }

                if (items.at(1) == "~") {

                    // Luu yeu cau dau vao dau ra.

                    formatSrc = getFormat(items.at(0));
                    formatDes = getFormat(items.at(0));

                    QInt dummy(items.at(2), formatSrc); // khoi tao QInt tu string he 10
                    dummy = ~dummy;

                    {
                        writeToFile(outFile, formatDes, dummy);
                    }
                    
                    break;
                }
                // Mac dinh la chuyen co so:

                // Luu yeu cau nguon
                {
                    formatSrc = getFormat(items.at(0));
                }
                // Luu yeu cau dich
                {
                    formatDes = getFormat(items.at(1));

                }

                QInt dummy(items.at(2), formatSrc); // khoi tao QInt tu string he 10
                {
                    writeToFile(outFile, formatDes, dummy);
                }

                break;
            }
            case 4: { // Neu arr co 4 phan tu thi string line co 3 space.
                // Voi 3 space ta co cac phep toan: +, -, *, /, and, or, xor, <<, >>

                // Luu yeu cau dau vao dau ra.
                formatSrc = getFormat(items.at(0));
                formatDes = getFormat(items.at(0));

                if (items.at(2) != "<<" && items.at(2) != ">>") {
                    QInt operand1(items.at(1), formatSrc); // khoi tao QInt tu string he formatSrc
                    QInt operand2(items.at(3), formatSrc); // khoi tao QInt tu string he formatSrc

                    QInt res("0");
                    char currentOperator = ' ';

                    if (items.at(2) == "+") {
                        res = operand1 + operand2;
                        currentOperator = '+';
                    }
                    if (items.at(2) == "-") {
                        res = operand1 - operand2;
                        currentOperator = '-';
                    }
                    if (items.at(2) == "*") {
                        res = operand1 * operand2;
                        currentOperator = '*';
                    }
                    if (items.at(2) == "/") {
                        res = operand1 / operand2;
                        currentOperator = '/';
                    }
                    if (items.at(2) == "&") {
                        res = operand1 & operand2;
                    }
                    if (items.at(2) == "^") {
                        res = operand1 ^ operand2;
                    }
                    if (items.at(2) == "|") {
                        res = operand1 | operand2;
                    }

                    // Ghi xuong file
                    {
                        if(currentOperator=='+' || currentOperator == '-' || currentOperator == '*' || currentOperator == '/'){
                            if (isDeadthZone(operand1, operand2, res, currentOperator)) {
                                outFile << "0" << endl;
                                break;
                            }
                        }
                        writeToFile(outFile, formatDes, res);
                    }

                    break;
                }
                else {
                    QInt operand(items.at(1), formatSrc); // khoi tao QInt tu string he formatSrc
                    int step = atoi(items.at(3).c_str());
                    if (items.at(2) == "<<") {
                        operand = operand << step;
                    }
                    if (items.at(2) == ">>") {
                        operand = operand >> step;
                    }

                    // Ghi xuong file
                    {
                        writeToFile(outFile, formatDes, operand);
                    }

                    break;
                }

                break;
            }
            }
        }

        // free
        formatSrc = formatDes = 0;
        items.clear();
    }

    inFile.close();
    outFile.close();

}
