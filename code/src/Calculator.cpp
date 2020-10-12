#include "Calculator.h"

using namespace std;

bool mainCal(Expression& exp, Elem& res)
{
    Elem ldata, rdata;
    while (!exp.opStack.empty())
    {
        //ȡ���������ݳ�ջ��, �ٽ���������ջ
        rdata = exp.dStack.top();
        exp.dStack.pop();
        ldata = exp.dStack.top();
        exp.dStack.pop();
        Elem result(opCal(ldata, rdata, exp.opStack.top()));
        //��������Ƿ��������
        if (result.up < 0 || result.down < 0)
            return false;
        exp.dStack.push(result);
        exp.opStack.pop();
    }
    res.up = exp.dStack.top().up;
    res.down = exp.dStack.top().down;
    return true;
}

const Elem opCal(const Elem& l, const Elem& r, char op)
{
    switch(op)
    {
    case '+':
        return l + r;
    case '-':
        return l - r;
    case '*':
        return l * r;
    case '/':
        return l / r;
    }
}

bool opPriority(const char& op1, const char& op2)
{
    return op1 != '+' && op1 != '-' && op2 != '*' && op2 != '/';
}

bool generateExp(const int& n, const int& range)
{
    srand((int)time(NULL));
    char oper[] = {'+', '-', '*', '/'};
    vector<Elem> dArray;
    vector<char> opArray;
    vector<Elem> resArray;
    Elem res;
    ofstream exerc, ans;
    exerc.open(".\\Exercise.txt");
    ans.open(".\\Answer.txt");
    int opNum = 0, opId = 0;
    int up = 0, down = 0;

    for (int i = 0; i < n; i++)
    {
        //�����������
        dArray.clear();
        opArray.clear();
        //��������������
        opNum = rand() % 3 + 1;
        for (int j = 0; j < opNum; j++)
        {
            //����opNum�����ź�����
            opId = rand() % 4;
            opArray.push_back(oper[opId]);
            down = rand() % (range - 1) + 1;
            up = rand() % (down * range - 1) + 1;
            dArray.push_back(Elem (up, down));
        }
        down = rand() % (range - 1) + 1;
        up = rand() % (down * range - 1) + 1;
        dArray.push_back(Elem (up, down));

        //��������
        if (opId < 2 && opNum > 1)
        {
            int pos = rand() % (opNum - 1);
            opArray.insert(opArray.begin() + pos, '(');
            opArray.insert(opArray.begin() + pos + 2, ')');
        }

        Expression exp;
        //�ñ��ʽ���ϸ�
        //1.�м���������ָ���
        //2.�������������ظ�
        if (!exp.input(opArray, dArray) || !mainCal(exp, res) ||
                (find(resArray.begin(), resArray.end(), res) != resArray.end()))
        {
            i--;
            continue;
        }
        else
        {
            //������д���ļ�, �𰸴�������
            exerc << i + 1 << ". " << expToString(opArray, dArray) << endl;
            resArray.push_back(res);
            ans << i + 1 << ". " << elemToString(res) << endl;
        }

    }
    ans.close();
    exerc.close();
    return true;
}

const string expToString(vector<char> opArray, vector<Elem> dArray)
{
    int i = 0, j = 0;
    string ret = "";
    if (opArray[i] == '(')
    {
        ret += opArray[i++];
    }
    while (i < opArray.size() || j < dArray.size())
    {
        if (j < dArray.size())
        {
            //ƴ������
            ret += elemToString(dArray[j++]);
        }
        //ƴ���ַ���
        if (i < opArray.size())
        {
            if (opArray[i] == ')')
            {
                ret += opArray[i++];
                if (i < opArray.size())
                    ret = ret + " " + opArray[i++] + " ";
            }
            else if (opArray[i + 1] == '(')
            {
                ret = ret + " " + opArray[i++] + " ";
                if (i < opArray.size())
                    ret += opArray[i++];
            }
            else
            {
                ret = ret + " " + opArray[i++] + " ";
            }
        }

    }
    ret += " = ";
    return ret;
}

const string elemToString(Elem& data)
{
    string ret = "";
    //1.�ٷ���ת��Ϊ������
    if (data.up > data.down && data.up % data.down != 0)
    {
        ret = ret + intToString(data.up / data.down) + "'";
        data.up %= data.down;
        ret = ret + intToString(data.up) + "/" + intToString(data.down);
    }
    //����
    else if (data.up % data.down == 0)
    {
        ret = ret + intToString(data.up / data.down);
    }
    else
    {
        ret = ret + intToString(data.up) + "/" + intToString(data.down);
    }
    return ret;
}

const string intToString(int x)
{
    string ret = "";
    char t;
    while (x)
    {
        t = x % 10 + '0';
        ret = t + ret;
        x /= 10;
    }
    return ret;
}

void checkAnswer(const string& exercPath, const string& ansPath)
{
    //�����ļ����Ĵ�
    ifstream exerc, ans;
    ofstream grade;
    exerc.open(exercPath);
    ans.open(ansPath);
    grade.open(".\\Grade.txt");
    string formula, answer;
    //��¼���
    int no = 1;
    //������ȷ�ʹ�������
    vector<int> correct, wrong;
    //�ж� ÿ�������ȷ�����
    while (getline(exerc, formula) && getline(ans, answer))
    {
        if (check(formula, answer))
        {
            correct.push_back(no++);
        }
        else
        {
            wrong.push_back(no++);
        }
    }
    //�����д���ļ�Grade.txt��
    grade << "Correct: " << correct.size();
    if (correct.size() > 0)
    {
        grade << " (";
        for (auto it = correct.begin(); it != correct.end() - 1; it++)
        {
            grade << *it << ", ";
        }
        grade << correct[correct.size() - 1] << ")" << endl;
    }
    grade << "Wrong: " << wrong.size();
    if (wrong.size() > 0)
    {
        grade << " (";
        for (auto it = wrong.begin(); it != wrong.end() - 1; it++)
        {
            grade << *it << ", ";
        }
        grade << wrong[wrong.size() - 1] << ")" << endl;
    }
    exerc.close();
    ans.close();
    grade.close();
}

bool check(string& formula, string& answer)
{
    //ɾ����Ŀ���
    int t = find(formula.begin(), formula.end(), '.') - formula.begin();
    formula.erase(0, t + 2);
    answer.erase(0, t + 2);

    //����Ŀ�ָ���м���
    vector<char> opArray;
    vector<Elem> dArray;
    vector<string> partVec = splitWithExp(formula, " ");
    int i = 0;
    while (i < partVec.size() - 1)
    {
        //��������
        if (i % 2 == 0)
        {
            //���Ƿ�����������
            auto lPos = partVec[i].find("(");
            auto rPos = partVec[i].find(")");
            if (lPos != string::npos)
            {
                opArray.push_back('(');
                partVec[i].erase(partVec[i].begin() + lPos);
            }
            else if (rPos != string::npos)
            {
                opArray.push_back(')');
                partVec[i].erase(partVec[i].begin() + rPos);
            }
            //���Ҵ������ķ�����ֺ�
            auto mixedPos = partVec[i].find("'");
            auto fracPos = partVec[i].find("/");
            auto dSize = partVec[i].size();
            int up, down;
            //������
            if (mixedPos != string::npos)
            {

                int intNum = atoi(partVec[i].substr(0, mixedPos).c_str());
                int upNum = atoi(partVec[i].substr(mixedPos + 1, fracPos).c_str());
                down = atoi(partVec[i].substr(fracPos + 1, dSize).c_str());
                up = intNum * down + upNum;
            }
            //�����
            else if (fracPos != string::npos)
            {
                up = atoi(partVec[i].substr(0, fracPos).c_str());
                down = atoi(partVec[i].substr(fracPos + 1, dSize).c_str());
            }
            //����
            else
            {
                up = atoi(partVec[i].c_str());
                down = 1;
            }
            dArray.push_back(Elem(up, down));
        }
        //�������
        if (i % 2 == 1)
        {
            opArray.push_back(partVec[i][0]);
        }
        i++;
    }
    //�����
    Expression exp;
    Elem res;
    exp.input(opArray, dArray);
    mainCal(exp, res);
    string s = elemToString(res);
    if (answer.compare(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


vector<string> splitWithExp(string exp, const string tag)
{
    vector<string> resVec;
    auto pos = exp.find(tag);
    auto expSize = exp.size();
    while (pos != string::npos)
    {
        string part = exp.substr(0, pos);
        resVec.push_back(part);
        exp = exp.substr(pos + 1, expSize);
        pos = exp.find(tag);
    }
    return resVec;
}
