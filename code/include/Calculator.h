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


//������
bool mainCal(Expression& exp, Elem& res);

//��������
const Elem opCal(const Elem& l, const Elem& r, char op);

//��������ȼ�
bool opPriority(const char& op1, const char& op2);

//���ɺ���
bool generateExp(const int& num, const int& range);

//��ʽ��ƴ�ӳ��ַ���
const string expToString(vector<char> opArray, vector<Elem> dArray);

//������ת���ַ���
const string elemToString(Elem& dArray);

//��intת��Ϊstring
const string intToString(int x);

//��������ļ��Ĵ�
void checkAnswer(const string& exercPath, const string& ansPath);

//�������Ƿ���ȷ
bool check(string& formula, string& answer);

//�ַ���ת��������
const Elem stringToElem(const string& data);

//�����ʽ�ָ�
vector<string> splitWithExp(string exp, const string tag);

#endif // CALCULATOR_H
