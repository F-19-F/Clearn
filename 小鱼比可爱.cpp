#include <iostream>
using namespace std;
int main()
{
    int n,i,m;
    cin>>n;
    int a[n],b[n];
    for (i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for (i=0;i<n;i++)
    {
        b[i]=0;
    }
    for (i=1;i<n;i++)
    {
        for (m=i;m>=0;m--)
        {
            if (a[m]<a[i])
            (b[i])++;
        }
    }
    for (i=0;i<n;i++)
    {
        cout<<b[i]<<" ";
    }
    return 0;
}