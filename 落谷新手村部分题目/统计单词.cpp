#include <iostream>
#include <string.h>
using namespace std;
int times=0,point;
void Small(char*a,char*b)//测试
{
    for (;*a!='\0';a++)
    {
      if (*a>'A'&&*a<'Z')
        *a+=32;
    }
  for (;*b!='\0';b++)
    {
      if (*b>'A'&&*b<'Z')
        *b+=32;
    }
}
void Is (char *c,char *d)
{
    int j=0,r=0;
    char *a,*b;
    a=c;
    b=d;
    while (*b!='\0')
        {
            if (*a==*b)
            {
                r++;
            }
            if ((*b!=*a)||(*a=' '))
            {
                r=0;
                a=c;
                continue;
            }
            if (r==strlen(c))
            {
                times++;
                if (times==1)
                {
                    point=j-strlen(c);
                }
                r=0;
                a=c;
                continue;
            }
            j++;
            a++;
            b++;
        }
}
int main()
{
    int i=0;
    char a[20],b[100];
    cin>>a;
    cin.get();
    while (1)
    {
        b[i]=cin.get();
        if (b[i]=='\n')
        {
            b[i]='\0';
             break;
        }    
    }
    Small (a,b);
    Is(a,b);
    cout<<times<<" ";
    cout<<point;
    return 0;
}