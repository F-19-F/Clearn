#include<iostream>
using namespace std;
unsigned long  long  X(int a,int n)//返回a的n次方
{
    if (n==0)
    return 1;
    int i,m=a;
    for (i=1;i<n;i++)
    {
        m*=a;
    }
    return m;
}
int Size (int a)//判断数字的位数（除0以外）
{
    int i,m=1;//m为除数
    for (i=1;a/(m*10)!=0;i++,m*=10);
    return i;
}
int Work(int a,int b)//b为原来的自然数
{
    int i=0,p,next,times=0;//p为每次要在左边加的数
    for (p=1;p<=(b/2);p++,i++)
    {
        next=a+p*X(10,Size(a)) ;
        times+=Work(next,p);
    }
    return i+times;
}
int main()
{
    int a;
    cin>>a;
    cout<<(Work(a,a)+1)<<endl;
    return 0;
}