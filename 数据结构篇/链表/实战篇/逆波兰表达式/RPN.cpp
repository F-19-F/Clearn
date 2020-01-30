#define Data_Type int
#define char2int(Source) (int)(Source - 48)
#define Get_Opt                                 \
    for (int i = 0; i < 2; i++)                 \
    {                                           \
        Exp_Temp.Pop(&Temp), Opt_Num[i] = Temp; \
    }

#include <cstdlib>
#include "Stack.h"
#include <iostream>

using namespace std;

int RPN(char *Expression)
{
    Stack Num_Temp;
    Stack Exp_Temp;
    bool Opt_Signal=false;//为了避免两个连续的运算符导致多次入栈
    int Temp; //万能临时变量
    int Num_Tp;
    int Num_Base = 1;
    int Opt_Num[2];
    while (*Expression != '\0')
    {
        //将表达式中的数字型字符存储在数字缓冲栈中
        if (*Expression >= '0' && *Expression <= '9')
        {
            Temp = char2int(*Expression);
            Num_Temp.Push(&Temp);
            Opt_Signal=false;
        }
        //接收到非数字字符时将数字缓冲中的数据转化成int型
        if ((*Expression>'9'||*Expression<'0')&&!Opt_Signal)
        {
            Num_Tp = 0;
            //将在数字缓冲栈中的数据转化为int数据存放在Num_Tp中
            while (Num_Temp.Pop(&Temp))
            {
                Num_Tp += Num_Base * Temp;
                Num_Base *= 10;
            }
            //将Num_Tp中的数据压入表达式栈中并重置Num_Base
            Num_Base = 1;
            Exp_Temp.Push(&Num_Tp);
        }
        //当扫描到运算符时进行判断计算
        if (*Expression == '+')
        {
            Get_Opt; //解决栈的先进后处原则对运算顺序的干扰
            Temp = Opt_Num[1] + Opt_Num[0];
            Exp_Temp.Push(&Temp);
            Opt_Signal=true;
        }
        if (*Expression == '-')
        {
            Get_Opt; //解决栈的先进后处原则对运算顺序的干扰
            Temp = Opt_Num[1] - Opt_Num[0];
            Exp_Temp.Push(&Temp);
            Opt_Signal=true;
        }
        if (*Expression == '*')
        {
            Get_Opt; //解决栈的先进后处原则对运算顺序的干扰
            Temp = Opt_Num[1] * Opt_Num[0];
            Exp_Temp.Push(&Temp);
            Opt_Signal=true;
        }
        if (*Expression == '/')
        {
            Get_Opt; //解决栈的先进后处原则对运算顺序的干扰
            Temp = Opt_Num[1] / Opt_Num[0];
            Exp_Temp.Push(&Temp);
            Opt_Signal=true;
        }
        //将指针指向表达式的下一个字符
        Expression++;
    }
    Exp_Temp.Pop(&Temp);
    if (Exp_Temp.Getlen()==0)
    return Temp;
    else
    {
        cout<<"表达式错误,结果不可靠"<<endl;
        return 0;
    }
    
}
int main()
{
    char Exp[100];
    cin.get(Exp,100);
    cout<<RPN(Exp);
    return 0;
}