#include <iostream>
using namespace std;
int main()
{
    char a[14];
    int b[9],r=0,i;
    int *c;
    c=b;
    cin>>a;
    for (i=0;i<=11;i++)
    {
        if (a[i]!='-')
        {
            *c=(a[i]);
            *c-=48;
             c++;
        }
    }
    c=b;
    for (i=1;i<=9;i++)
    {
        r+=i*(*c);
        c++;
    }
    r=r%11;
    if (!(a[12]>=48||a[12]=='X'))//除去输入格式错误的ISBN误判，如字符'：'
    {
        goto error;
    }
    if (r==10&&a[12]=='X')
    {
        cout<<"Right";
        return 0;
    }
    if (r==(a[12]-48))//最特殊的一个情况，r=10而a[12]正好是ascii-58对应的字符':',会导致输出right后再输出正确的ISBN
    {
        cout<<"Right";
        return 0;
    }
    else 
    {
    error:
        if (r==10)
        {
            a[12]='X';
        }
        else 
        {
            a[12]=(char)(r+48);
        }
        cout<<a;
    }
    return 0;
}