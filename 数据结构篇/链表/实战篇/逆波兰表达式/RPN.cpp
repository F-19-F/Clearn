#define Data_Type double

#include <cstdlib>
#include "Stack.h"
#include <iostream>

using namespace std;

double RPN(char *Expression)
{
    int Num_i = 0; //用来判断下面Num_Temp数组的下标
    char Num_Temp[99];
    Stack Exp_Temp;
    bool Opt_Signal = false; //指示上一次检索是否有操作符，避免两个连续的运算符导致多次入栈
    double Temp;             //万能临时变量
    double Num_Tp;
    double Opt_Num[2];
    while (*Expression != '\0')
    {
        //将表达式中的数字型字符存储在数字缓冲区中
        if ((*Expression >= '0' && *Expression <= '9') || *Expression == '.')
        {
            Num_Temp[Num_i++] = *Expression;
            if (Num_i>=99)
            {
                cout<<"超出单个数字的最大容量"<<endl;
                return -1;
            }
            Num_Temp[Num_i] = '\0';
            Opt_Signal = false;
        }
        //接收到非数字相关字符时将数字缓冲区中的数据转化成double并入栈
        if ((*Expression > '9' || *Expression < '0') && (!Opt_Signal && *Expression != '.'))
        {
            Num_Tp = atof(Num_Temp);
            Exp_Temp.Push(&Num_Tp);
            Num_i = 0;
            Opt_Signal=true;
        }
        //当扫描到运算符时进行判断计算
        if (*Expression == '+' || *Expression == '-' || *Expression == '*' || *Expression == '/')
        {
            for (int i = 0; i < 2; i++)
            {
                if(Exp_Temp.Pop(&Temp))
                Opt_Num[i] = Temp;
                else//没有两个数字在数字栈中则表达式有误
                {
                     cout<<"表达式错误!操作数不足!"<<endl;
                     return -2;
                }
                
            }
            Opt_Signal = true;
            switch (*Expression)
            {
            case '+':
                Temp = Opt_Num[1] + Opt_Num[0];
                Exp_Temp.Push(&Temp);
                break;
            case '-':
                Temp = Opt_Num[1] - Opt_Num[0];
                Exp_Temp.Push(&Temp);
                break;
            case '*':
                Temp = Opt_Num[1] * Opt_Num[0];
                Exp_Temp.Push(&Temp);
                break;
            case '/':
                if (Opt_Num[0] == 0)
                {
                    cout << "除数不能为0" << endl;
                    return -3;
                }
                Temp = Opt_Num[1] / Opt_Num[0];
                Exp_Temp.Push(&Temp);
                break;
            }
        }
        Expression++;
    }
    Exp_Temp.Pop(&Temp);
    if (Exp_Temp.Getlen() == 0)
        return Temp;
    else
    {
        cout << "表达式错误!" << endl;
        return -4;
    }
}
int main()
{
    char Exp[100];
    cin.get(Exp, 100);
    cout << RPN(Exp);
    return 0;
}