#include <iostream>
using namespace std;
int get_num_length(int n)
{
    int i=1;
    while ((n/=10)>0)
    {
        i++;
    }
    return i;
}
char* int_char(int Source)//将int类型的数据转换成char
{
    char *Temp,*as_return=new char [get_num_length(Source)+1];
    Temp=as_return;
    int n_ev;
    while (Source>0)
    {
        n_ev=Source%10;
        *Temp='0'+n_ev; 
        Temp++;
        Source/=10;
    }
    *Temp='\0';//使最后一位为'\0'
    return as_return;
}
int length(char *Source)
{
    int i=0;
    while (*Source!='\0')
    {
        i++;
        Source++;
    }
    return i;
}
char Move_Word(char Source,int n)//移动正整数n位
{
    if ((Source>'A'&&Source<'Z')||(Source>'a'&&Source<'z'))
    {
        if (n>26)
        {
            n%=26;
        }
        Source+=n;
    }
    return Source;
}
bool Make_Passwd(char* Source)//加密函数
{
    FILE *Key=fopen("./key","w");
    // fopen()
    srand((unsigned int)time(NULL));
    for (int i=0;i<length(Source);i++)
    {
        fputs("srand()%100+1",Key);
    }
}
int main()
{
    // Make_Passwd("Ha");
    cout<<int_char(10)<<endl;
    return 0;
}
