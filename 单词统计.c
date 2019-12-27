#include <stdio.h>
#include <string.h>
int times=0,point;
void Small(char*a,char*b)
{
    for (;*a!='\0';a++)
    {
      if (*a>='A'&&*a<='Z')//问题还真出在这，>=写成了>
        *a+=32;
    }
  for (;*b!='\0';b++)
    {
      if (*b>='A'&&*b<='Z')
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
            else
            {
                r=0;
                a=c;
                goto end;
            }
            if ((r==strlen(c)&&(*(d+j-r)==' '||j-strlen(c)==-1))&&(*(d+j+1)==' '||*(d+j+1)=='\0'))//判断是否符合条件，单词在首位过，过滤单词后面还有字母的情况
            {
                times++;
                if (times==1)
                {
                    point=j-strlen(c)+1;
                }
                r=0;
                a=c;
                goto end;
            }
            a++;
            end :
            b++;
            j++;
        }
}
int main()
{
    char a[20],b[1000001];
    scanf ("%s",a);
    while (getchar()!='\n');
    scanf ("%[^\n]",b);
    Small(a,b);
    Is (a,b);
    if (times==0)
    {
    times=-1;
    }
    printf("%d ",times);
    if(times>0)
    {
    printf ("%d",point);
    }
    return 0;
}