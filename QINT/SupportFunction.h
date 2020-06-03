#pragma once
#include<iostream>
#include<string>
using namespace std;

/*------------ Các Fuc hỗ trợ xử lý chuỗi---------------*/

string plusString(string a, string b);	// Cộng 2 string
string MultiStringTo2(string str);		// Nhân string với 2
string Power2String(int exp);			
string Div2String(string num, bool& bit);
string delete0(string str);
int compareTwoStringLikeNumber(string a, string b);