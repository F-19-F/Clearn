#include <iostream>
using namespace std;
#define Stack_default_Length 1
#define Data_Type int
#define IncreaseNum 5
class Stack //顺序存储的栈
{
private:
    Data_Type *top;
    Data_Type *base;
    int Stack_Length;

public:
    Stack();
    bool Push(Data_Type *In);
    bool Pop(Data_Type *A_return);
};
Stack::Stack() : Stack_Length(Stack_default_Length)
{
    top = base = new Data_Type[Stack_default_Length];
    Stack_Length = Stack_default_Length;
}
bool Stack::Push(Data_Type *In)
{
    //当长度大于最大存储容量时扩大内存
    if (top - base >= Stack_Length)
    {
        base = (Data_Type *)realloc(base, Stack_Length + IncreaseNum);
        if (!base)
        {
            return false;
        }
        //因为只是复制，所以top不能不变
        top = base + Stack_Length;
        Stack_Length+=IncreaseNum;
    }
    // *(top++)=*In;//为方便调试注释掉
    *top=*In;
    top++;
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
int main()
{
    int Which=1;
    Stack Test;
    while (Which)
    {
        cout<<"******************************"<<endl;
        cout<<"*********栈测试程序**********"<<endl;
        cout<<"******************************"<<endl;
        cout<<"1.向栈中随机写入10组整数"<<endl;
        cout<<"2.全部出栈"<<endl;
        cout<<"3.手动压栈"<<endl;
        cout<<"4.手动出栈"<<endl;
        cout<<"0.退出程序"<<endl;
        cout<<"输入选项:";
        cin>>Which;
        Data_Type Temp;
        int Times;
        switch (Which)
        {
        case 1:
            srand((unsigned int)time(NULL));
            for(int i=0;i<10;i++)
            {
                Temp=rand()%100+1;
                Test.Push(&Temp);
            }
            break;
        case 2:
            Times=0;
            while(Test.Pop(&Temp))
            {
                cout<<Temp<<" ";
                Times++;
            }
            cout<<endl<<"出栈"<<Times<<"次"<<endl;
            break;
        case 3:
            cout<<"压栈数据:";
            cin>>Temp;
            Test.Pop(&Temp);
            break;
        case 4:
            if(Test.Pop(&Temp))
            cout<<Temp;
            else
            {
                cout<<"现在已经是空栈";
            }
            break;
        }
    }
    return 0;
}