#include<iostream>
using namespace std;
void Move(char *a,int n)
{
    int i;
    for (i=1;i<=n;i++)
    {
        if (*a=='z')
        *a=96;
        (*a)++;
    }
}
int main()
{
    int i,n;
    char a[50],*b;
    cin>>n;
    cin>>a;
    for (i=0;a[i]!='\0';i++)
    {
        b=&a[i];
        Move(b,n);
    }
    cout<<a;
    return 0;
}