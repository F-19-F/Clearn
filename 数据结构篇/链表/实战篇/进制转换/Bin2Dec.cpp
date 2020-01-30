#define Data_Type int

#include <iostream>
#include<cstdio>
#include"Stack.h"

using namespace std;

int bin2dec(char* Source)
{
    Stack a;
    int Base_2=1;
    int Temp;
    int Result=0;
    while (*Source!='\0')
    {
        Temp=(int)(*Source)-48;
        a.Push(&Temp);
        Source++;
    }
    while(a.Pop(&Temp))
    {
        Result+=Base_2*Temp;
        Base_2*=2;
    }
    return Result;
}

int main()
{
    char a[99];
    cin>>a;
    cout<<bin2dec(a);
    return 0;
}