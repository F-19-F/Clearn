#include <iostream>
using namespace std;
bool Is (int a)//判断是否为素数
{
    int i=2;
    while ((a%i)!=0&&i<=a/2)
    i++;
    if (i==a/2+1)
    return 1;
    return 0;
}
bool In (int a)
{
    int n[8],i,j;
    for (i=0;a!=0;i++,a/=10)
    {
        n[i]=a%10;
    }
    j=i;
    for (i=0;i+1<=j/2;i++)
    {
        if (n[i]!=n[j-1-i])
        return 0;
    }
    return 1;
}
int main ()
{
    int a,b;
    cin>>a>>b;
    for (int i=a;i<=b;i++)
    {
        if (Is (i)&&In(i))
        cout<<i<<endl;;
    }
    return 0;
}