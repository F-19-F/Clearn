#define Data_Type char
#define char2int(a) (int)(a - 48)
#include <iomanip>
#include <iostream>
#include <string.h>
#include<cstdlib>

#define Stack_default_Length 20
#define IncreaseNum 5
//需要在头文件前面定义数据类型
//Data_Type should be defined before this file being included
class Stack //顺序存储的栈
{
private:
    Data_Type *top;
    Data_Type *base;
    int Stack_Length;
public:
    Stack();
    int Getlen();
    Data_Type Get_Top();
    bool Push(Data_Type *In);
    bool Pop(Data_Type *A_return);
};
Stack::Stack() : Stack_Length(Stack_default_Length)
{
    top = base = new Data_Type[Stack_default_Length];
}
int Stack::Getlen()
{
    return top-base;
}
Data_Type Stack::Get_Top()
{
    if (top!=base)
    return *(top-1);
    else
    {
        return 0;
    }
    
}
bool Stack::Push(Data_Type *In)
{
    //当长度大于最大存储容量时扩大内存
    if (top - base >= Stack_Length)
    {
        base = (Data_Type *)realloc(base, (Stack_Length + IncreaseNum)*sizeof(Data_Type));
        if (!base)
        {
            return false;
        }
        //因为只是复制，所以top不能不变
        top = base + Stack_Length;
        Stack_Length+=IncreaseNum;
    }
    *(top++)=*In;
    return true;
}
bool Stack::Pop(Data_Type *A_return)
{
    //是空栈则不返回值
    if (top==base)
    {
        return false;
    }
    //返回栈顶的值
    *A_return=*(--top);
    return true;
}
using namespace std;

void equ2rpn(char *source)
{
    Stack a;
    float ans;
    int coe_s = 0;
    int ct_s = 0;
    //变量系数存储数字指针
    int i = 0;
    //常数存储单元数字指针
    int j = 0;
    //字符转整型时的临时权值
    int num_base;
    //未知量系数存储单元
    int coe[99];
    //常数存储单元
    int ct[99];
    bool Is_Left = false;
    //记忆变量的名称
    char Uq;
    //字符缓冲变量
    char Temp_S;
    char *temp = &Temp_S;
    memset(coe, 0, 99);
    memset(ct, 0, 99);
    //全部入栈
    while (*source != '\0')
    {
        a.Push(source);
        //记录变量的名称
        if (((*source > '9' || *source < '0') && (*source != '+' && *source != '-')) && *source != '=')
        {
            Uq = *source;
        }
        source++;
    }
    //全部出栈
    while (a.Pop(temp))
    {
        //检索到未知量时进行处理
        if (*temp == Uq)
        {
            //向前检索，直到下一项
            num_base = 1;
            do
            {
                if (*temp >= '0' && *temp <= '9')
                //将检索到的字符转化为整型数据
                {
                    coe[i] += (char2int(Temp_S)) * num_base;
                    num_base *= 10;
                }
            } while (a.Pop(temp) && (*temp != '+' && *temp != '-') && (*temp != '='));
            //无明显数字时初始化为1
            if (num_base==1)
            {
                coe[i]=1;
            }
            //检索完成后对符号进行处理
            if (a.Getlen() != 0)
            {
                //该项在右边时候对符号进行判断
                if ( (*temp != '-') && !Is_Left)
                {
                    coe[i] = 0 - coe[i];
                }
                //该项在左边时对符号进行判断
                if (( *temp != '+') && Is_Left)
                {
                    coe[i] = 0 - coe[i];
                }
            }
            else
            {
                //最左边是负号时对系数进行修改
                if (*temp=='-')
                {
                    coe[i] = 0 - coe[i];
                }
                i++;
                break;
            }
            
            //指向下一个变量系数存储单元
            i++;
        }
        //检索到数字时进行处理
        if (*temp >= '0' && *temp <= '9')
        {
            num_base = 1;
            do
            {
                if (*temp >= '0' && *temp <= '9')
                //将检索到的字符转化为整型数据
                {
                    ct[j] += (char2int(Temp_S)) * num_base;
                    num_base *= 10;
                }
            } while (a.Pop(temp) && (*temp != '+' && *temp != '-') && (*temp != '='));
            //检索完成后对符号进行处理
            if (a.Getlen() != 0)
            {
                //在右边时对符号进行判断
                //右边数字前面是负号时候则进行负号修改
                if ((*temp != '+'&&*temp!='=') && !Is_Left)
                {
                    ct[j] = 0 - ct[j];
                }
                //在左边时对符号进行判断
                if ( (*temp != '-') && Is_Left)
                {
                    ct[j] = 0 - ct[j];
                }
            }
            else
            {
                if (*temp!='-')
                ct[j] = 0 - ct[j];
                j++;
                break;
            }
            //指向下一个变量系数存储单元
            j++;
        }
        //等号左右边判断
        if (*temp == '=')
        {
            Is_Left = true;
        }
    }
    //求和
    for (int k = 0; k < i; k++)
    {
        coe_s += coe[k];
    }
    for (int k = 0; k < j; k++)
    {
        ct_s += ct[k];
    }
    //输出结果,为避免出现-0的情况，故采用以下表达式
    ans = ct_s==0?0:(float)ct_s / (float)coe_s;
    cout << Uq << "=" << fixed << setprecision(3) << ans << endl;
}
int main()
{
    char a[99];
    cin >> a;
    equ2rpn(a);
    return 0;
}