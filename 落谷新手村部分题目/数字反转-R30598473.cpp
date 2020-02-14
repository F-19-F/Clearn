#include <iostream>
#include <cstdio>

using namespace std;

//返回值为是否是连续0信号
bool Work()
{
    char a;
    if ((a = getchar()) != '\n')
    {
        //负号直接输出
        if (a == '-')
        {
            cout << a;
            Work();
            return false;
        }
        //非负号则进行数字判断
        else
        {
            //正常数直接输出
            if (!Work())
            {
                cout << a;
                return false;
            }
            else
            {
                //非正常0不输出
                if (a == '0')
                    return true;
                else
                {
                    //检测到第一个正常数则开始输出
                    cout << a;
                    return false;
                }
            }
        }
    }
    else
    {
        return true;
    }
}
int main()
{
    //全是0时则输出0
    if (Work())
    {
        cout << "0";
    }
    return 0;
}