#include <stdio.h>
int Is (int result [26],int i,int n)
{
    int j;
    for (j=i;j<26;j++)
    {
        if (result [j]>=n)
        return 1;
    }
    return 0;
}
void Print (int result[26])
{
    int i,m,j,n;
    m=result [0];
    for (i=1;i<26;i++)//找出字母出现最大次数
    {
        if (result [i]>=m)
        {
            m=result [i];
        }
    }
    n=m;
    for(i=1;i<=m;i++)//打出纵列
    {
        for (j=0;j<26;j++)//打出横列
        {
            if (result[j] >=n)//n对应当前打印出*的字母应最小出现的次数
            {
                printf ("*");
                if (Is(result,j,n)) //判断该字母后面是否还有要打印*的字母
                {
                    printf(" ");
                }
            }
            else 
            {
                if(Is(result,j,n))
                printf ("  ");
            }
        }
        n--;
        printf("\n");
    }
    for (i=0;i<26;i++)//打出横坐标
    {
        if (i==25)
        {
            printf ("%c",i+65);
            continue;
        }
        printf ("%c ",i+65);
    }
    // printf ("%c=%d \n",i+65,result [i]);
}
void How (char a[4][100],int result[26])
{
    int i,j;
    for (i=0;i<4;i++)
    {
        for (j=0;a[i][j]!='\0';j++)
        {
            if (a[i][j]<65||a[i][j]>90)
            continue;
            result [a[i][j]-65]+=1;
        }
    }
}
int main()
{
    char a[4][100],(*b)[100];
    int result [26]={},i;
    b=a;
    for (i=0;i<4;i++)
    {
      scanf ("%[^\n]s",*(b+i));
      getchar();
    }
    How(a,result);
    Print (result);
    return 0;
}