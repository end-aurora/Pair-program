#include <iostream>
#include "Calculator.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 5)
    {
        //随机生成题目
        if (argv[1][1] == 'n' && argv[3][1] == 'r')
        {
            //检查n 和 range 参数
            int i = 0;
            for (int k = 0; k < 2; k++)
            {
                while (argv[2 + 2 * k][i] != '\0')
                {
                    if (argv[2 + 2 * k][i] > '9' || argv[2 + 2 * k][i] < '0')
                    {
                        cerr << "-n 后的参数应该是整数!" << endl;
                        return -1;
                    }
                    i++;
                }
            }
            int n = atoi(argv[2]);
            int range = atoi(argv[4]);
            if (n <= 0 || n > 10000)
            {
                cerr << "-n 后的参数应该在 0 - 100000." << endl;
            }
            if (range <= 0 || range > 1000)
            {
                cerr << "-r 后的参数应该在 0 - 10000." << endl;
            }
            else
            {
                generateExp(n, range);
                cout << "生成题目与答案成功." << endl;
            }
            return 0;
        }
        //检查文件答案对错
        else if (argv[1][1] == 'e' && argv[3][1] == 'a')
        {
            fstream exc, ans;
            if (!exc || !ans)
            {
                cerr << "文件路径错误." << endl;
            }
            else
            {
                checkAnswer(argv[2], argv[4]);
                cout << "判定完毕, 结果已统计到文件Grade.txt中." << endl;
            }
            return 0;
        }
    }
    cerr << "输入的参数有误!\n" << "正确的输入方式:\n"
         << "1.Myapp.exe -n 10 -r 100 \n\t或 \n"
         << "2.Myapp.exe -e <exercisefile>.txt -a <answerfile>.txt" << endl;
    return -1;
}
