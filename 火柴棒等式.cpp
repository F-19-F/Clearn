#include <iostream>
using namespace std;
int Size (int a)//判断数字的位数（0认为是0位）
{
    if (a==0)
    return 0;
    int i,m=1;//m为除数
    for (i=1;a/(m*10)!=0;i++,m*=10);
    return i;
}
int how (int n)//输出n所需要的火柴数
{
    int m,sum=0,p=10;
    m=Size (n);
    if (m>1)
      {
        for (int t=0;t<m;t++,p*=10)
        {
            sum+=how ((n%p)/(p/10));
        }
        return sum;
       }
    else
      switch (n)
        {
            case 1:
            return 2;
            break;
            case 7:
            return 3;
            break;
            case 4:
            return 4;
            break;
            case 2:
            case 3:
            case 5:
            return 5;
            break;
            case 0:
            case 9:
            case 6:
            return 6;
            break;
            case 8:
            return 7;
            break;
        }
        return 0;
}
int work(int a)
{
    int t=0,s=0;
    for (int i=0;i<1000;i++)
    {
        for(int j=0;j<1000;j++)
        if ((how(i)+how(j)+how(i+j))==a)
        {
            if (j==i)
            {
                s++;
            }
             t++;
        }
    }
    return t-s/2;
}
int main ()
{
    int a;
    cin>>a;
    cout<<work (a-4);
    return 0;
}