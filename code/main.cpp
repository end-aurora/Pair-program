#include <iostream>
#include "Calculator.h"

using namespace std;

int main(int argc, char* argv[])
{
//    int argc = 5;
//    char argv[5][20] = {"Myapp.exe", "-n", "8000", "-r", "500"};
    if (argc == 5)
    {
        //���������Ŀ
        if (argv[1][1] == 'n' && argv[3][1] == 'r')
        {
            //���n �� range ����
            int i = 0;
            for (int k = 0; k < 2; k++)
            {
                while (argv[2 + 2 * k][i] != '\0')
                {
                    if (argv[2 + 2 * k][i] > '9' || argv[2 + 2 * k][i] < '0')
                    {
                        cerr << "-n ��Ĳ���Ӧ��������!" << endl;
                        return -1;
                    }
                    i++;
                }
            }
            int n = atoi(argv[2]);
            int range = atoi(argv[4]);
            if (n <= 0 || n > 10000)
            {
                cerr << "-n ��Ĳ���Ӧ���� 0 - 100000." << endl;
            }
            if (range <= 0 || range > 1000)
            {
                cerr << "-r ��Ĳ���Ӧ���� 0 - 10000." << endl;
            }
            else
            {
                generateExp(n, range);
                cout << "������Ŀ��𰸳ɹ�." << endl;
            }
            return 0;
        }
        //����ļ��𰸶Դ�
        else if (argv[1][1] == 'e' && argv[3][1] == 'a')
        {
            fstream exc, ans;
            if (!exc || !ans)
            {
                cerr << "�ļ�·������." << endl;
            }
            else
            {
                checkAnswer(argv[2], argv[4]);
                cout << "�ж����, �����ͳ�Ƶ��ļ�Grade.txt��." << endl;
            }
            return 0;
        }
    }
    cerr << "����Ĳ�������!\n" << "��ȷ�����뷽ʽ:\n"
         << "1.Myapp.exe -n 10 -r 100 \n\t�� \n"
         << "2.Myapp.exe -e <exercisefile>.txt -a <answerfile>.txt" << endl;
    return -1;
}
