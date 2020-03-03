#include <iostream>
#include <cstring>
using namespace std;
//将接收到的棋盘复制给临时棋盘
#define chb_cpy for (int i=0;i<8;i++){for (int j=0;j<8;i++){chb_t[i][j]=chb[i][j];}}

int count=0;
//判断在棋盘chb下，位置(x,y)是否安全
bool safe(int x,int y,bool (*chb)[8])
{
    //检索同一行
    for (int i=0;i<8;i++)
    {
        if (chb[x][i])
        {
            return false;
        }
    }
    //检索同一列
    for (int i=0;i<8;i++)
    {
        if (chb[i][y])
        {
            return false;
        }
    }
    //检索左上角
    for (int i=x,j=y;i>=0&&j>=0;i--,j--)
    {
        if (chb[i][j])
        {
            return false;
        }
    }
    //检索左下角
    for (int i=x,j=y;i<8&&j>=0;i++,j--)
    {
        if (chb[i][j])
        {
            return false;
        }
    }
    //检索右上角
    for (int i=x,j=y;i>=0&&j<8;i--,j++)
    {
        if (chb[i][j])
        {
            return false;
        }
    }
    //检索右下角
    for (int i=x,j=y;i<8&&j<8;i++,j++)
    {
        if (chb[i][j])
        {
            return false;
        }
    }
    //能执行到这一步代表所在位置安全
    return true;
}
void Eight_Queen(int x,bool (*chb)[8])//x为横坐标，y为纵坐标，chb为上次已经保存的棋盘
{
    //cht_t为临时棋盘
    static bool (*chb_t)[8]=new bool[8][8];
    //第一次初始化临时棋盘
    if (x==0)
    memset (chb_t,0,64);
    if (x==7)
    {
        for (int i=0;i<8;i++)
        {
            //如果穷举到的位置可行则输出组合
            if (safe(x,i,chb_t))
            {
                //打印已经存在的组合
                chb_t[x][i]=true;
                cout<<"第"<<(++count)<<"种组合"<<endl;
                for (int j=0;j<8;j++)
                {
                    for (int k=0;k<8;k++)
                    {
                        //打印皇后的位置
                        if (*(*(chb_t+j)+k))
                        {
                            cout<<"Q ";
                        }
                        else
                        //打印空位置
                        {
                            cout<<"X ";
                        }
                    }
                    //打印完一行后换行
                    cout<<endl;
                }
            }
            //使用完后复原
            chb_t[x][i]=false;
        }
    }
    //非最后一行时继续穷举
    else
    {
        for (int i=0;i<8;i++)
        {
            //如果当前穷举的位置安全则进行下一行的递归
            if (safe(x,i,chb_t))
            {
                chb_t[x][i]=true;
                Eight_Queen(x+1,chb_t);
                //递归完后复原
                chb_t[x][i]=false;
            }
        }
    }
}

int main()
{
    Eight_Queen(0,NULL);
    return 0;
}