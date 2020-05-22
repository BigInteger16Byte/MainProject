#include"QInt.h"
#include"Convert.h"

#include<fstream>
#include<string>
#include<vector>

using namespace std;

//hàm này để in ra dãy 128 bit để test
void testBit(QInt x) {
    for (int i = 0; i < 128; i++) {
        cout << x.GetBit(i);
        if ((i + 1) % 32 == 0)  cout << endl;
    }
    cout << endl;
}

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

string trimZeroHeader(string bin) {
    string res = bin;
    int i;
    for (i = 0; i < 128; i++) {
        if (res[i] == '1') {
            res = res.substr(i);
            break;
        }
    }
    if (i == 128) {
        res = "0";
    }

    return res;
}

void writeToFile(ofstream& out, int formatDes, QInt num) {
    string res = "";
    {
        if (formatDes == 0) { // Chuyen thanh he 10
            res = Convert::QIntToStringNumber(num);
            out << res << endl;
        }
        if (formatDes == 1) { // Chuyen thanh he 2
            res = Convert::DecToBin(num);

            // Trim 0 header
            res = trimZeroHeader(res);
            out << res << endl;
        }
        if (formatDes == 2) { // Chuyen thanh he 16
            res = Convert::DecToHex(num);
            out << res << endl;
        }
    }
}

// Kiểm tra tràn số đầu vào
// Chuổi Bin dài hơn 128 kí tự
// Chuổi Dec dài hơn 39 kí tự or bằng 38 và lớn hơn chuổi "170141183460469231731687303715884105727" (so sánh chuổi 2^127 - 1)
// Chuổi Hex dài hơn 32 kí tự or bằng 32 và lớn hơn chuổi "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"


int main() {

    ifstream inFile;
    ofstream outFile;

    inFile.open("input.txt");
    outFile.open("output.txt");

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
                    //dummy.rotateLeft();

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

                    res = Convert::QIntToStringNumber(dummy);

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

                    if (items.at(2) == "+") {
                        res = operand1 + operand2;
                    }
                    if (items.at(2) == "-") {
                        res = operand1 - operand2;
                    }
                    if (items.at(2) == "*") {
                        res = operand1 * operand2;
                    }
                    if (items.at(2) == "/") {
                        res = operand1 / operand2;
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
                        writeToFile(outFile, formatDes, res);
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