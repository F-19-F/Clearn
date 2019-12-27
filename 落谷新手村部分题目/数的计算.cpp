#include <iostream>
using namespace std;//这题目本身表述也是有问题的
int  main()
{
    int F[10001]={};
    int i,j,n;
    cin>>n;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=i/2;j++)
        {
            F[i]+=F[j];//不得不服，这个计算方法是真的强，n对应的首位结果等于1---(n-1)结果的累加再加一
        }
        F[i]++;
    }
    cout<<F[n];
    return 0;
}