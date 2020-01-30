#include <iostream>
#include<cstdio>
#include"Stack.h"

#define Data_Type int

using namespace std;

void Bin2Oct(char *Source)
{
    Stack Bin,Oct;
    int Temp;
    int Time_Temp=0;
    int Bin_base=1;
    int Oct_Temp=0;
    while (*Source!='\0')//二进制数入栈
    {
        Temp=(int)*Source-48;
        Bin.Push(&Temp);
        Source++;
    }
    //每3个二进制为一组输入到Oct栈
    while (Bin.Pop(&Temp))
    {
       Oct_Temp+=Temp*Bin_base;
       Bin_base*=2;
       Time_Temp++;
       if (Time_Temp==3)
       {
           Oct.Push(&Oct_Temp);
           Oct_Temp=0;
           Time_Temp=0;
           Bin_base=1;
       }
    }
    //将不足3位的二进制组合入栈
    if (Time_Temp>0)
    Oct.Push(&Oct_Temp);
    while (Oct.Pop(&Temp))
    {
        cout<<Temp;
    }
    cout<<endl;
}

int main()
{
    char Bin[99];
    cin>>Bin;
    Bin2Oct(Bin);
    return 0;
}