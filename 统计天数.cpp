/*洛谷P1567 统计天数*/
/*https://www.luogu.org/problem/P1567*/
#include <iostream>
using namespace std;
int T;//记录上次计算的位置
int Dy (int*a,int i,int N)
{
    int t=0;//记录连续天数
    if (a[i]>=0)
    {
        t=1;
    }
    if (N==1)//第一次未考虑N=1时的情况
    {
        T=i+1;//这一句十分重要，因为没有这一句的话，会进入死循环
        return t;
    }
    if ((a[i])<0)
    {
        T=i+1;
        return t;
    }
    for (;i<N;i++)
    {
        if (a[i]>a[i+1]||a[i]<0)
        {
            break;
        }
        t++;
    }
    T=i+1;
    return t;
}
int main()
{
    int N,i,r=0,t;
    cin>>N;
    int a[N];
    for (i=0;i<N;i++)
    {
        cin>>a[i];
    }
    for (i=0;i<N;i=T)
    {
        t=Dy(a,i,N);
        if (t>=r)
        {
            r=t;
        }
    }
    cout<<r;
    return 0;
}