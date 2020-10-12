#include "Expression.h"
#include "Calculator.h"
Expression::Expression()
{
    //ctor
}

bool Expression::input(vector<char>& opArray, vector<Elem>& dArray)
{
    int i = 0, j = 0;
    //��һ��������������
    if (opArray[i] == '(')
    {
        opStack.push(opArray[i++]);
    }
    //������������ݵ�������������Ϊֹ
    while(i != opArray.size() || j != dArray.size())
    {
        //��ȡһ������
        dStack.push(dArray[j++]);
        //��ȡ�����
        if (!inputOp(opArray, i))
            return false;
    }
    return true;
}

bool Expression::inputOp(vector<char>& opArray, int& i)
{
    // i �Ѿ������ֵ��, ��������Ѿ���ȡ����
    if (i >= opArray.size())
        return true;
    //���ڱ����������������
    Elem ldata, rdata;
    //����������
    while (opArray[i] == ')')
    {
        i++;

        while (opStack.top() != '(')
        {
            //ȡ���������ݳ�ջ��, �ٽ���������ջ
            rdata = dStack.top();
            dStack.pop();
            ldata = dStack.top();
            dStack.pop();
            Elem result = opCal(ldata, rdata, opStack.top());
            //�м����������ָ���
            if (result.up < 0)
                return false;
            dStack.push(result);
            opStack.pop();
        }
        //'('��ջ
        opStack.pop();
    }
    //�����е�������뼴�������������������ȼ��ıȽ�
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
    //��������Ƿ��Ѿ�����
    if (i == opArray.size())
        return true;

    //�ڶ����������������(, ��Ҫ����ѹ�������
    while (i + 1 < opArray.size() && opArray[i + 1] == '(')
    {
        opStack.push(opArray[i++]);
    }
    opStack.push(opArray[i++]);
    return true;
}
