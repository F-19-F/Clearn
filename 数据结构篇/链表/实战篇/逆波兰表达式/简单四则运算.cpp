#define Data_Type char


#include <cstdlib>
#include<iostream>
#include "Stack.h"
#include "Stack_Double.h"

using namespace std;
//判断输入的字符的优先级
int Get_Pot(char source)
{
    switch (source)
    {
    //'('不能参与比较，故将其优先级降至最低
    // case '(':
    case ')':
        return 3;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '+':
    case '-':
        return 1;
        break;
        default:
        return 0;
        break;
    }
}
char *Mid2Rpn(char *Source)
{
    Stack Opt_Temp;
    bool Last_Num = false;//记录输出最后一位是不是数字
    char *result = new char[100];
    char *As_Return = result;
    char Temp;
    while (*Source != '\0')
    {
        //判断是否属于操作数的内容
        if (isdigit(*Source) || *Source == '.')
        {
            *(result++) = *Source;
            Last_Num = true;
        }
        //是运算符时进行处理
        else
        {
            //运算符前一位是数字时加空格
            if (Last_Num)
            {
                *(result++) = ' ';
                Last_Num=false;
            }
            //优先级高于栈顶运算符的运算符入栈
            if (Get_Pot(*Source) > Get_Pot(Opt_Temp.Get_Top()))
            {
                //检索到右括号时寻找'('，并将中间的运算符输出
                if (*Source == ')')
                {
                    Opt_Temp.Pop(&Temp);
                    while (Temp != '(')
                    {
                        *(result++) = Temp;
                        *(result++)=' ';
                        //到空栈时还没找到左括号则返回错误
                        if (Opt_Temp.Getlen() == 0)
                        {
                            cout << "输入错误！缺少左边的括号" << endl;
                            return NULL;
                        }
                        //向后检索
                        Opt_Temp.Pop(&Temp);
                    }
                    if (*(Source+1)=='\0')
                    {
                        Last_Num=false;
                    }
                }
                //正常运算符入栈
                else
                {
                    Opt_Temp.Push(Source);
                }
            }
            //低优先运算符的入栈
            else
            {
                //请左括号直接入栈，解决某些左括号带来的误差
                if (*Source=='(')
                {
                    Opt_Temp.Push(Source);
                    Source++;
                    continue;
                }
                //请运算符栈中优先级大于或等于*Source优先级的运算符出栈
                while ((Get_Pot(Opt_Temp.Get_Top()) >= Get_Pot(*Source)) && (Opt_Temp.Getlen() != 0))
                {
                    Opt_Temp.Pop(&Temp);
                    *(result++) = Temp;
                    *(result++)=' ';
                }
                //请*Source入栈
                Opt_Temp.Push(Source);
            }
        }
        Source++;
    }
    //如果输出位最后一位是数字，则添加一个空格，保持格式
    if (Last_Num)
    *(result++)=' ';
    //检索完后将栈中的运算符输出
    while (Opt_Temp.Pop(&Temp))
    {
        *(result++) = Temp;
        *(result++)=' ';
        if (Temp=='(')
        {
            cout<<"缺少右括号!"<<endl;
            return NULL;
        }
    }
    *result = '\0';
    return As_Return;
}
double RPN(char *Expression)
{
    int Num_i = 0; //用来判断下面Num_Temp数组的下标
    char Num_Temp[99];
    Stack_R Exp_Temp;
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
    char Expression[100];
    cin>>Expression;
    cout<<"计算结果为:"<<RPN(Mid2Rpn(Expression))<<endl;
    return 0;
}