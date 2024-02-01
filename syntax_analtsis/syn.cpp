#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

//代码文件中字符的数目
int length;  

//存放文件取出的字符 
string letter[1000];

struct Token
{
    int id;
    string content;
    int next;
    Token()
    {

    }
    Token(int d)
    {
        id = d;
    }
    Token(int d, string s)
    {
        id = d;
        content = s;
    }
    Token(int d, int n)
    {
        id = d;
        next = n;
    }
    Token(int d, string s, int n)
    {
        id = d;
        content = s;
        next = n;
    }
    bool operator == (Token& t) //重载比较两个Token结构体是否相等
    {
        return(id == t.id);
    }
}w;

//输入代码文件的单词表or词法分析的输出
Token tokens[1000];

Token programs(1, "program");
Token begins(2, "begin");
Token endd(3, "end.");
Token vars(4, "var");
Token ifs(5, "if");
Token thens(6, "then");
Token elses(7, "else");
Token whiles(8, "while");
Token breaks(9, "break");
Token trues(10, "true");
Token falses(11, "false");
Token s12(12, "(");//(
Token s13(13, ")");//)
Token s14(14, ";");//;
Token s15(15, "+");//+
Token s16(16, "-");//-
Token s17(17, "*");//*
Token s18(18, "/");///
Token s19(19, "%");//%
Token s20(20, "=");//=
Token s21(21, "&&");//&&
Token s22(22, "||");//||
Token s23(23, "!");//!
Token s24(24, "==");//==
Token s25(25, "!=");//!=
Token s26(26, ">");//>
Token s27(27, "<");//<
Token s28(28, ">=");//>=
Token s29(29, "<=");//<=
Token identifiers(30);
Token roundnum(31);
Token floatnum(32);

int num; //用来遍历letter数组，num作为全局变量可以被所用函数修改

void error(int x)
{
    switch (x)
    {
    case 0:
        cout << "程序定义错误。";
        exit(0);
        break;
    case 1:
        cout << "程序体定义错误。";
        exit(0);
        break;
    case 2:
        cout << "赋值语句错误。";
        exit(0);
        break;
    case 3:
        cout << "赋值语句右值不正确。";
        exit(0);
        break;
    case 4:
        cout << "算术表达式错误。";
        exit(0);
        break;
    case 5:
        cout << "逻辑表达式错误。";
        exit(0);
        break;
    case 6:
        cout << "if-then分支结构错误（if处）。";
        exit(0);
        break;
    case 7:
        cout << "if-then分支结构错误（else处）。";
        exit(0);
        break;
    case 8:
        cout << "while分支结构错误。";
        exit(0);
        break;
    case 9:
        cout << "break语句错误。";
        exit(0);
        break;
    default:
        break;
    }
}

void get_nexttoken(Token& ww)
{
    ww = tokens[ww.next];
}

Token nextwhat(Token xx)
{
    Token yy = tokens[xx.next];
    return yy;
}

//这些是语法分析的函数的函数原型
void PROGRAM();
void PROBODY();
void ASSIGNMENT();
void VALUE();
void COUNT();
void E();
void T();
void T_();
void F();
void LOGIC();
void H();
void G();
void G_();
void L();
void L_();
void C();
void C_();
void M();
void M_();
void N();
void N_();
void A();
void CONDITION();
void ELSE();
void LOOP();
void BREAK();

void PROGRAM() {
    if (w == programs)
    {
        get_nexttoken(w);
        if (w == identifiers)
        {
            get_nexttoken(w);
            if (w == s14)
            {
                get_nexttoken(w);
                if (w == begins)
                {
                    get_nexttoken(w);
                    PROBODY();
                    if (w == endd) {
                        cout << "该程序是正确的。";
                    }
                    else {
                        error(0);
                    }
                }
                else error(0);
            }
            else error(0);
        }
        else error(0);
    }
    else error(0);
}

void PROBODY() {
    if (w == vars || w == identifiers) {
        ASSIGNMENT();
        PROBODY();
    }
    else if (w == ifs) {
        CONDITION();
        PROBODY();
    }
    else if (w == whiles) {
        LOOP();
        PROBODY();
    }
    else if (w == breaks) {
        BREAK();
        PROBODY();
    }
    else if (w == endd){};//PROBODY为空
    //else error(1);
}

void ASSIGNMENT() {
    if (w == vars) {
        get_nexttoken(w);
        if (w == identifiers) {
            get_nexttoken(w);
            if (w == s14) {
                get_nexttoken(w);
            }
            else if (w == s20) {
                get_nexttoken(w);
                VALUE();
                if (w == s14)
                    get_nexttoken(w);
                else error(2);
            }
            else error(2);
        }
        else error(2);
    }
    else if (w == identifiers)
    {
        get_nexttoken(w);
        if (w == s14) {//;
            get_nexttoken(w);
        }
        else if (w == s20) {//=
            get_nexttoken(w);
            VALUE();
            if (w == s14)//;
            {
                get_nexttoken(w);
            }
            else error(2);
        }
        else error(2);
    }
    else error(2);
}

void VALUE() {
    if (w == roundnum)
    {
        if (nextwhat(w) == s14 || nextwhat(w) == s15 || nextwhat(w) == s16 || nextwhat(w) == s17 || nextwhat(w) == s18 || nextwhat(w) == s19)
        {
            COUNT();
        }
        else if (nextwhat(w) == s24 || nextwhat(w) == s25 || nextwhat(w) == s26 || nextwhat(w) == s27 || nextwhat(w) == s28 || nextwhat(w) == s29)
        {
            LOGIC();
        }
        else error(3);
    }
    else if (w == floatnum)
    {
        if (nextwhat(w) == s14 || nextwhat(w) == s15 || nextwhat(w) == s16 || nextwhat(w) == s17 || nextwhat(w) == s18 || nextwhat(w) == s19)
        {
            COUNT();
        }
        else if (nextwhat(w) == s24 || nextwhat(w) == s25 || nextwhat(w) == s26 || nextwhat(w) == s27 || nextwhat(w) == s28 || nextwhat(w) == s29)
        {
            LOGIC();
        }
        else error(3);
    }
    else if (w == trues) LOGIC();
    else if (w == falses) LOGIC();
    else if (w == identifiers && nextwhat(w) == s14) get_nexttoken(w);//标识符然后;
    else if ((w == identifiers && !(nextwhat(w) == s14)) || w == s12)
    {//标识符然后不是;或者(
        if (w == s12 && nextwhat(w) == identifiers) {//(算术表达式或者逻辑表达式，以变量打头)
            if (nextwhat(nextwhat(w)) == s15 || nextwhat(nextwhat(w)) == s16 || nextwhat(nextwhat(w)) == s17 || nextwhat(nextwhat(w)) == s18 || nextwhat(nextwhat(w)) == s19) {
                COUNT();
            }
            else if (nextwhat(nextwhat(w)) == s21 || nextwhat(nextwhat(w)) == s22 || nextwhat(nextwhat(w)) == s24 || nextwhat(nextwhat(w)) == s25) {
                LOGIC();
            }
            else error(3);
        }
        else if (w == s12 && (nextwhat(w) == roundnum || nextwhat(w) == floatnum)) {//(算术表达式或者逻辑表达式，以数字常量打头)
            if (nextwhat(nextwhat(w)) == s15 || nextwhat(nextwhat(w)) == s16 || nextwhat(nextwhat(w)) == s17 || nextwhat(nextwhat(w)) == s18 || nextwhat(nextwhat(w)) == s19) {
                COUNT();
            }
            else if (nextwhat(nextwhat(w)) == s24 || nextwhat(nextwhat(w)) == s25) {
                LOGIC();
            }
            else error(3);
        }
        else if (w == s12 && nextwhat(w) == s23) {//(逻辑表达式，以!打头)
            if (nextwhat(nextwhat(w)) == identifiers || nextwhat(nextwhat(w)) == s12)
            {
                LOGIC();
            }
            else error(3);
        }
        else if (w == s12 && (nextwhat(w) == trues || nextwhat(w) == falses)) {//(逻辑表达式，内是true或false)
            LOGIC();
        }
        else if (w == identifiers && (nextwhat(w) == s15 || nextwhat(w) == s16 || nextwhat(w) == s17 || nextwhat(w) == s18 || nextwhat(w) == s19)) {//算术表达式，以变量打头
            COUNT();
        }
        else if (w == identifiers && (nextwhat(w) == s21 || nextwhat(w) == s22 || nextwhat(w) == s24 || nextwhat(w) == s25 || nextwhat(w) == s26 || nextwhat(w) == s27 || nextwhat(w) == s28 || nextwhat(w) == s29)) {//逻辑表达式，以变量打头
            LOGIC();
        }
        else error(3);
    }
    else if (w == s23)//逻辑表达式，以！打头
    {
        if (nextwhat(w) == identifiers || nextwhat(w) == s12)
        {
            LOGIC();
        }
        else error(3);
    }
    else error(3);
}

void COUNT() {
    T();
    E();
}

void E() {
    if (w == s15 || w == s16) {//E -> +TE | -TE
        get_nexttoken(w);
        T();
        E();
    }
    //E ->ε
}

void T() {
    F();
    T_();
}

void T_() {
    if (w == s17 || w == s18 || w == s19) {//T' -> *FT' | /FT' | %FT'
        get_nexttoken(w);
        F();
        T_();
    }
    //T' -> ε
}

void F() {
    if (w == s12) {//F -> (COUNT) 
        get_nexttoken(w);
        COUNT();
        if (w == s13) {
            get_nexttoken(w);
        }
        else error(4);
    }
    else if (w == roundnum || w == floatnum || w == identifiers) {//F -> roundnum | floatunm | id
        get_nexttoken(w);
    }
    else error(4);
}

void LOGIC() {
    G();
    H();
}

void H() {
    if (w == s22) {//H -> ||GH
        get_nexttoken(w);
        G();
        H();
    }
    //H -> ε
}

void G() {
    L();
    G_();
}

void G_() {
    if (w == s21)//G' -> &&LG'
    {
        get_nexttoken(w);
        L();
        G_();
    }
    //G' -> ε
}

void L() {
    C();
    L_();
}

void L_() {
    if (w == s24 || w == s25) {//L' -> !=CL' | ==CL'
        get_nexttoken(w);
        C();
        L_();
    }
    //L' -> ε
}

void C() {
    M();
    C_();
}

void C_() {
    if (w == s26 || w == s27 || w == s28 || w == s29) {//C' -> >MC' | <MC' | >=MC' | <=MC'
        get_nexttoken(w);
        M();
        C_();
    }
    //C' -> ε
}

void M() {
    N();
    M_();
}

void M_() {
    if (w == s15 || w == s16)//M' -> +NM' | -NM'
    {
        get_nexttoken(w);
        N();
        M_();
    }
    //M' -> ε
}

void N()
{
    A();
    N_();
}

void N_()
{
    if (w == s17 || w == s18 || w == s19)//N' -> *AN' | /AN' | %AN'
    {
        get_nexttoken(w);
        A();
        N_();
    }
    //N' -> ε
}

void A() {
    if (w == s12) {//(LOGIC)
        get_nexttoken(w);
        LOGIC();
        if (w == s13) {
            get_nexttoken(w);
        }
        else error(5);
    }
    else if (w == s23)//!
    {
        get_nexttoken(w);
        LOGIC();
    }
    else if (w == trues || w == falses || w == identifiers || w == roundnum || w == floatnum) {
        get_nexttoken(w);
    }
    else error(5);
}

void CONDITION() {
    if (w == ifs) {
        get_nexttoken(w);
        if (w == s12) {
            get_nexttoken(w);
            LOGIC();
            if (w == s13) {
                get_nexttoken(w);
                if (w == thens) {
                    get_nexttoken(w);
                    PROBODY();
                    ELSE();
                }
                else error(6);
            }
            else error(6);
        }
        else error(6);
    }
    else error(6);
}

void ELSE() {
    if (w == elses) {//ELSE -> else then PROBODY
        get_nexttoken(w);
        if (w == thens) {
            get_nexttoken(w);
            PROBODY();
        }
        else {
            error(7);
        }
    }
    //ELSE -> ε
}

void LOOP() {
    if (w == whiles) {//LOOP -> while (LOGIC) PROBODY
        get_nexttoken(w);
        if (w == s12)
        {
            get_nexttoken(w);
            LOGIC();
            if (w == s13)
            {
                get_nexttoken(w);
                PROBODY();
            }
            else error(8);
        }
        else error(8);
    }
    else error(8);
}

void BREAK() {
    if (w == breaks && (nextwhat(w) == s14)) {
        get_nexttoken(w);
        get_nexttoken(w);
    }
    else {
        error(9);
    }
}

string symbol[18] = { "(",")",";","+","-","*","/","%","=","&&","||","!","==","!=",">","<",">=","<=" };

int isSymbol(string s) { //判断是不是符号，返回在单词编码表里符号的编码
    int i;
    for (i = 0; i < 18; i++) {
        if (s == symbol[i])
            return (i + 12);
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
    if ((s >= "a" && s <= "z") || (s >= "A" && s <= "Z"))
        return true;
    return false;
}

string keyword[11] = { "program","begin","end.","var","if","then","else","while","break","true","false" };

//判断是否为关键字,是，返回在单词编码表里关键字的编码 
int isKeyWord(string s) {
    int i;
    for (i = 0; i < 11; i++) {
        if (s == keyword[i])
            return (i + 1);
    }
    return 0;
}

//判断是字母、数字、符号还是其他
int typeword(string str) {
    if ((str >= "a" && str <= "z") || (str >= "A" && str <= "Z"))   //	字母 
        return 1;

    if (str >= "0" && str <= "9")   //数字 
        return 2;

    if (str == ">" || str == "=" || str == "<" || str == "!" || str == ";" || str == "(" || str == ")" || str == "+" || str == "-" || str == "*" || str == "/" || str == "%" || str == "&" || str == "|")   //判断符号 
        return 3;

    else
        return 4;
}

//标识符的连接
string identifier(string s, int n) {
    int j = n + 1;
    int flag = 1;

    while (flag) {
        if (isNum(letter[j]) || isLetter(letter[j]) || letter[j] == "." || letter[j] == "_") {
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

//符号的连接
string symbolStr(string s, int n) {
    int j = n + 1;
    string str = letter[j];
    if (s == ">" || s == "<" || s == "=" || s == "!")//首字符 >= <= == !=
    {
        if (str == "=")//第二个字符 >= <= == !=
        {
            s = (s + letter[j]).c_str();
            j++;
        }
    }
    else if (s == "&")//首字符 &&
    {
        if (str == "&")//第二个字符 &&
        {
            s = (s + letter[j]).c_str();
            j++;
        }
    }
    else if (s == "|")//首字符 ||
    {
        if (str == "|")//第二个字符 ||
        {
            s = (s + letter[j]).c_str();
            j++;
        }
    }
    /*
    if (str == ">" || str == "=" || str == "<" || str == "!" || str == "&" || str == "|") {//双目的
        s = (s + letter[j]).c_str();
        j++;
    }
    */
    num = j;
    return s;
}

//数字的连接
string Number(string s, int n) {
    int j = n + 1;
    int flag = 1;

    while (flag) {
        if (isNum(letter[j]) || (letter[j] == ".")) {
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

void getToken() {
    int k;
    int numoftoken = 0;
    for (num = 0; num < length;) {
        string str1, str;
        str = letter[num];
        k = typeword(str);
        switch (k) {
        case 1://字母
        {
            str1 = identifier(str, num);
            int iKW = isKeyWord(str1);
            if (iKW != 0)//关键字
            {
                Token temp1(iKW, numoftoken + 1);
                tokens[numoftoken] = temp1;
                numoftoken++;
                cout << "<" << iKW << "," << str1 << "," << numoftoken << ">" << endl;
            }
            else//变量
            {
                Token temp2(30, str1, numoftoken + 1);
                tokens[numoftoken] = temp2;
                numoftoken++;
                cout << "<" << 30 << "," << str1 << "," << numoftoken << ">" << endl;
            }
            break;
        }

        case 2://数字
        {
            str1 = Number(str, num);
            string::size_type idx = str1.find(".");

            if (idx != string::npos)//number含有.  是floatnum
            {
                Token temp1(32, str1, numoftoken + 1);
                tokens[numoftoken] = temp1;
                numoftoken++;
                cout << "<" << 32 << "," << str1 << "," << numoftoken << ">" << endl;
            }
            else//number不含.  是roundnum
            {
                Token temp2(31, str1, numoftoken + 1);
                tokens[numoftoken] = temp2;
                numoftoken++;
                cout << "<" << 31 << "," << str1 << "," << numoftoken << ">" << endl;
            }
            break;
        }

        case 3://符号
        {
            str1 = symbolStr(str, num);
            Token temp1(isSymbol(str1), str1, numoftoken + 1);
            tokens[numoftoken] = temp1;
            numoftoken++;
            cout << "<" << isSymbol(str1) << "," << str1 << "," << numoftoken << ">" << endl;
            break;
        }

        case 4:
        {
            cout << "词法分析时遇到非法字符——";
            string error = "error";
            cout << "<" << error << "," << str << ">";
            cout << "该程序是错误的。";
            exit(0);
            break;
        }
        }
    }
}

int main() {
    freopen("input2.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);

    length = 0; //初始化文件的字符数
    char ch;
    while (cin >> ch) {
        if (ch != ' ') {
            letter[length] = ch;
            length++;
        }
    }

    getToken(); //取单词，即词法分析
    w = tokens[0]; //w指向第一个单词
    
    PROGRAM();
    fclose(stdin);//关闭文件 
    fclose(stdout);//关闭文件 

    return 0;
}