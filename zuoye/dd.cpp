#include <iostream>
using namespace std;
int main()
{
    int n=0;
    char temp;
    int last;//记录上次输入的数据
    int *base;
    int min_temp[2];
    cin>>n;
    base =new int [n];//分配数组
    while(getchar()!='\n');//吸收空格
    for (int i=0;i<n;i++)
    {
        while((temp=getchar())!='\n')
        {
            if (temp>'0'&&temp<'10')//为数字时计数
            {
                last=(int)(temp-48);
                base[i]+=last;
            }
            else if (temp=='D')
            {
                //last=last*2;
                base[i]+=last*2;
            }
            else
            {
                cout<<"第"<<i+1<<"名同学输入错误!\n";
            }
        }
        last=0;
    }
    min_temp[1]=base[0];
    min_temp[0]=0;
    for(int i=1;i<n;i++)//比较大小
    {
        if (base[i]<=min_temp[1])
        {
            min_temp[1]=base[i];
            min_temp[0]=i;
        }
    }
    cout<<"min="<<min_temp[1]<<" , no="<<min_temp[0]+1;
    return 0;
}