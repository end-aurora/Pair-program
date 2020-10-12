#include "Expression.h"
#include "Calculator.h"
Expression::Expression()
{
    //ctor
}

bool Expression::input(vector<char>& opArray, vector<Elem>& dArray)
{
    int i = 0, j = 0;
    //第一个符号是左括号
    if (opArray[i] == '(')
    {
        opStack.push(opArray[i++]);
    }
    //将运算符和数据的容器都读到空为止
    while(i != opArray.size() || j != dArray.size())
    {
        //读取一个数据
        dStack.push(dArray[j++]);
        //读取运算符
        if (!inputOp(opArray, i))
            return false;
    }
    return true;
}

bool Expression::inputOp(vector<char>& opArray, int& i)
{
    // i 已经是最大值了, 代表符号已经读取完了
    if (i >= opArray.size())
        return true;
    //用于保存运算的两个数据
    Elem ldata, rdata;
    //遇到右括号
    while (opArray[i] == ')')
    {
        i++;

        while (opStack.top() != '(')
        {
            //取出左右数据出栈后, 再将计算结果入栈
            rdata = dStack.top();
            dStack.pop();
            ldata = dStack.top();
            dStack.pop();
            Elem result = opCal(ldata, rdata, opStack.top());
            //中间运算结果出现负数
            if (result.up < 0)
                return false;
            dStack.push(result);
            opStack.pop();
        }
        //'('出栈
        opStack.pop();
    }
    //将已有的运算符与即将加入的运算符进行优先级的比较
    while(!opStack.empty() && opStack.top() != '(' && opPriority(opStack.top(), opArray[i]))
    {
        rdata = dStack.top();
        dStack.pop();
        ldata = dStack.top();
        dStack.pop();
        Elem result = opCal(ldata, rdata, opStack.top());
        if (result.up < 0)
            return false;
        dStack.push(result);
        opStack.pop();
    }
    //检查运算是否已经结束
    if (i == opArray.size())
        return true;

    //第二个运算符是左括号(, 需要两次压入运算符
    while (i + 1 < opArray.size() && opArray[i + 1] == '(')
    {
        opStack.push(opArray[i++]);
    }
    opStack.push(opArray[i++]);
    return true;
}
