/*洛谷P21442-珠心算测验*/
/*https://www.luogu.org/problem/P2141*/
#include <iostream>
using namespace std;
bool isok(int a,int *b,int n,int m)//因为函数定义时不允许int a[n],所以用指针代替了数组
{
    int i,p;
    for (i=0;i<n;i++)
    {
        if (i==m)
        {
            continue;
        }
        for (p=0;p<n;p++)
        {
            if (p==i||p==m)
            {
                continue;
            }
            if (a==b[i]+b[p])
            return 1;
        }
    }
    return 0;
}
int main()
{
    int n,i,r=0;
    cin>>n;
    int a[n];
    for (i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for (i=0;i<n;i++)
    {
        if(isok(a[i],a,n,i))
        {
            r++;
        }
    }
    cout<<r;
    return 0;
}