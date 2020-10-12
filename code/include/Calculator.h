#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Expression.h"
#include "Elem.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>


//主计算
bool mainCal(Expression& exp, Elem& res);

//符号运算
const Elem opCal(const Elem& l, const Elem& r, char op);

//运算符优先级
bool opPriority(const char& op1, const char& op2);

//生成函数
bool generateExp(const int& num, const int& range);

//将式子拼接成字符串
const string expToString(vector<char> opArray, vector<Elem> dArray);

//将数据转换字符串
const string elemToString(Elem& dArray);

//将int转化为string
const string intToString(int x);

//检查整个文件的答案
void checkAnswer(const string& exercPath, const string& ansPath);

//检查该题是否正确
bool check(string& formula, string& answer);

//字符串转换成数据
const Elem stringToElem(const string& data);

//将表达式分割
vector<string> splitWithExp(string exp, const string tag);

#endif // CALCULATOR_H
