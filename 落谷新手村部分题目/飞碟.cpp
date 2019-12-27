#include <iostream>
using namespace std;
int main()
{
    char a[7],b[7];
    int i=0,r=1,s=1;
    cin>>a;
    cin>>b;
    while (a[i]!='\0')
    {
        a[i]-=64;
        r*=a[i];
        i++;
    }
    r=r%47;
    i=0;
    while (b[i]!='\0')
    {
        b[i]-=64;
        s*=b[i];
        i++;
    }
    s=s%47;
    if (s==r)
    {
        cout<<"GO";
    }
    else 
    {
        cout<<"STAY";
    }
    return 0;
}