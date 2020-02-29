#include <iostream>
#include <cstring>
using namespace std;

int count=0;
void Eight_Queen(int x,int y,bool (*chb)[8])//x为横坐标，y为纵坐标，chb为上次已经保存的棋盘
{
    //cht_t为临时棋盘
    bool (*chb_t)[8]=new bool[8][8];
    //初始化临时棋盘
    memset (chb_t,0,64);
    if (x==8)
    {
        for (int i=0;i<8;i++)
        {
            //如果穷举到的位置可行则输出组合
            if (safe(x,i,chb))
            {
                //打印已经存在的组合
                cout<<"第"<<(++count)<<"种组合"<<endl;
                for (int j=0;j<8;j++)
                {
                    for (int k=0;k<8;k++)
                    {
                        if (*(*(chb+j)+k))
                        {
                            cout<<"Q ";
                        }
                        else
                        {
                            cout<<"X ";
                        }
                    }
                    cout<<endl;
                }
            }
        }
    }
    else
    {
        for (int i=0;i<8;i++)
        {
            if (safe(x,i,chb))
            {
                Eight_Queen(x+1,)
            }
        }
    }
    
}

int main()
{
    return 0;
}