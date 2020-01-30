#define Data_Type char

#include <iostream>
#include <cstdio>
#include "Stack.h"

#define int2char(Source) Source < 9 ? (char)(Source + 48) : (char)('A' + (Source - 10))

using namespace std;

void Bin2Hex(char *Source)
{
    Stack Bin, Hex;
    char Temp;
    int Time_Temp = 0;
    int Bin_base = 1;
    int Hex_Temp = 0;
    char Hex_Tp_Char;
    while (*Source != '\0') //二进制数入栈
    {
        Temp = *Source;
        Bin.Push(&Temp);
        Source++;
    }
    //每4个二进制为一组输入到Hex栈
    while (Bin.Pop(&Temp))
    {
        Hex_Temp += ((int)Temp - 48) * Bin_base; //临时将四位二进制转化成十进制
        Bin_base *= 2;
        Time_Temp++;
        if (Time_Temp == 4)
        {
            Hex_Tp_Char = int2char(Hex_Temp);
            Hex.Push(&Hex_Tp_Char);
            Hex_Temp = 0;
            Time_Temp = 0;
            Bin_base = 1;
        }
    }
    //将不足4位的二进制组合入栈
    if (Time_Temp > 0)
    {
        Hex_Tp_Char = int2char(Hex_Temp);
        Hex.Push(&Hex_Tp_Char);
    }
    while (Hex.Pop(&Temp))
    {
        cout << Temp;
    }
    cout << endl;
}

int main()
{
    char Source[99];
    cin >> Source;
    Bin2Hex(Source);
    return 0;
}