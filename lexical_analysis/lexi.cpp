#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

//关键字 
string key[17] = {"main", "bool", "char", "int", "double", "float", "string", "if", "else", "for", "break", "continue", "void", "return", "true", "false", "default"};

//关键字的类别码
int keyNum[17] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
//运算符和界符 
string symbol[34] = { "<",">","!=",">=","<=","==",",",";","(",")","[","]","{","}","+","-","*","/","%","=","&","|","&&","||","++","--","<<",">>",".",":","!","#","\"","\'"};
//运算符和界符的类别码 
int symbolNum[34] = {18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
//存放文件取出的字符 
string letter[1000];
//将字符转换为单词
string  words[1000];
//标识符表
string identifiers[100];
int lenOfIdS = -1;
//常数表
string numbers[100];
int lenOfNumS = -1;

int length;  //保存程序中字符的数目 
int num;

int isSymbol(string s) { //判断运算符和界符 
	int i;
	for (i = 0; i < 34; i++) {
		if (s == symbol[i])
			return symbolNum[i];
	}
	return 0;
}

//判断是否为数字 
bool isNum(string s) {
	if (s >= "0" && s <= "9")
		return true;
	return false;
}

//判断是否为字母 
bool isLetter(string s)
{
	if ((s >= "a" && s <= "z")||(s >= "A" && s<= "Z"))
		return true;
	return false;
}

//判断是否为关键字,是，返回类别码 
int isKeyWord(string s) {
	int i;
	for (i = 0; i < 28; i++) {
		if (s == key[i])
			return keyNum[i];
	}
	return 0;
}

//返回单个字符的类型 
int typeword(string str) {
	if ((str >= "a" && str <= "z") || (str >= "A" && str <= "Z"))   //	字母 
		return 1;

	if (str >= "0" && str <= "9")   //数字 
		return 2;

	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" || str == "[" || str == "]" || str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/" || str == "%" || str == "&" || str == "|" || str == "." || str == ":" || str == "\"" || str == "\'")   //判断运算符和界符 
		return 3;
	else
		return 4;
}

string identifier(string s, int n) {
	int j = n + 1;
	int flag = 1;

	while (flag) {
		if (isNum(letter[j]) || isLetter(letter[j]) || letter[j]=="_" || letter[j]==" ") {
			s = (s + letter[j]).c_str();
			if (isKeyWord(s)) {
				j++;
				num = j;
				return s;
			}
			j++;
		}
		else {
			flag = 0;
		}
	}

	num = j;
	return s;
}

string symbolStr(string s, int n) {
	int j = n + 1;
	string str = letter[j];
	if (str == ">" || str == "=" || str == "<" || str == "!" || str=="+" || str=="-" || str=="&" || str=="|") {
		s = (s + letter[j]).c_str();
		j++;
	}
	num = j;
	return s;
}

//数字的连接
string Number(string s, int n) {
	int j = n + 1;
	int flag = 1;

	while (flag) {
		if (isNum(letter[j])||(letter[j]==".")) {
			s = (s + letter[j]).c_str();
			j++;
		}
		else {
			flag = 0;
		}
	}

	num = j;
	return s;
}

int getIDPoint(string s)
{
	for (int k = 0; k <= lenOfIdS; k++)
	{
		if (s == identifiers[k])
		{
			return k;
			break;
		}
	}
	lenOfIdS++;
	identifiers[lenOfIdS] = s;
	return lenOfIdS;
}

int getNumberPoint(string s)
{
	for (int k = 0; k <= lenOfNumS; k++)
	{
		if (s == numbers[k])
		{
			return k;
			break;
		}
	}
	lenOfNumS++;
	numbers[lenOfNumS] = s;
	return lenOfNumS;
}

void print(int s, int n) {
	cout << "<" << s << "," << n << ">" << endl;
}

void print(int s, string n) {
	cout << "<" << s << "," << n << ">" << endl;
}

void printId()
{
	cout << endl;
	cout << "标识符表";
	cout << "指针" << "  " << "标识符值" << endl;
	for (int i = 0; i <= lenOfIdS; i++)
	{
		cout << i << "                    " << identifiers[i] << endl;
	}
}

void printNumber()
{
	cout << endl;
	cout << "常数表";
	cout << "指针" << "  " << "常数值" << endl;
	for (int i = 0; i <= lenOfNumS; i++)
	{
		cout << i << "                    " << numbers[i] << endl;
	}
}

void TakeWord() {  //取单词 
	int k;

	for (num = 0; num < length;) {
		string str1, str;
		str = letter[num];
		k = typeword(str);
		switch (k) {
		case 1:
		{
			str1 = identifier(str, num);
			if (isKeyWord(str1))
				print(isKeyWord(str1), str1);//关键字
			else
			{
				print(63, getIDPoint(str1));//标识符
			}
			break;
		}

		case 2:
		{
			str1 = Number(str, num);
			print(64, getNumberPoint(str1));//常数
			break;
		}

		case 3:
		{
			str1 = symbolStr(str, num);
			print(isSymbol(str1), str1);//运算符和界限符
			break;
		}

		case 4:
		{
			string error = "error";
			cout << "<" << error << "," << str << ">" << endl;
			num++;
			break;
		}
		}
	}
}

int main() {
	char w;
	int i, j;

	//FILE** fpin=NULL;
	//FILE** fpout = NULL;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout); //从控制台输出，而不是文本输出

	length = 0;
	//"#"结束
	while (cin >> w && w!='#') {
		if (w != ' ') {
			letter[length] = w;
			length++;
		}   //去掉程序中的空格
	}

	TakeWord();
	printId();
	printNumber();

	fclose(stdin);//关闭文件 
	fclose(stdout);//关闭文件 
	return 0;
}