#define Data_Type char

#include <cstdlib>
#include "Stack.h"
#include <iostream>

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
int main()
{
    char In[100];
    cin >> In;
    cout << Mid2Rpn(In);
    return 0;
}