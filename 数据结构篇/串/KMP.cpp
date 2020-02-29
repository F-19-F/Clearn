#include <iostream>
#include <cstring>
using namespace std;

int KMP (char* source,char* target)
{
    int len=strlen(target);
    int i,j;
    int* next;
    next = new int [len];
    next[0]=-1;
    //计算nexr数组
    i=0;
    j=-1;
    while (i<len)
    {
        if (j==-1||target[i]==target[j])
        {
            next[++i]=++j;
        }
        else
        {
            j=next[j];
        }
    }
    //*****************debug*********************//
    //***************print next*******************//
    for (int k=0;k<len;k++)
    {
        cout<<"next["<<k<<"]="<<next[k]<<endl;
    }
    //开始遍历源数组
    //i为target指针
    i=0;
    //j为计数器
    j=0;
    while (*source!='\0')
    {
        if (*source==target[i])
        {
            i++;
            //到达target末尾表示完全符合，计数器+1,并重置target指针
            if (i==len)
            {
                j++;
                i=0;
            }
        }
        //不相等时调用next数组
        else
        {
            i=next[i];
            if (i==-1)
            {
                i=0;
            }
            if (i==0&&*source!=target[i])
            {
                source++;
            }
            continue;
        }
        source++;
    }
    return j;
}
int main()
{
    cout<<KMP("AcAq","AcAd");
    return 0;
}
