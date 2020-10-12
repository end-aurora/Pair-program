#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<iostream>
#include<stack>
#include <vector>
#include "Elem.h"

using namespace std;

class Expression
{
public:
    //运算符栈
    stack<char> opStack;
    //数据栈
    stack<Elem> dStack;

    Expression();

    bool input(vector<char>& opArray, vector<Elem>& dArray);

    bool inputOp(vector<char>& opArray, int& i);


protected:

private:
};

#endif // EXPRESSION_H
