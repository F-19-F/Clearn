#include <iostream>
using namespace std;
int main()
{
    int i=0,m,a[101];
    while (1)
    {
        cin>>a[i];
        if (a[i]==0)
        {
            i--;
            break;
        }
        i++;
    }
    for (;i>=0;i--)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}