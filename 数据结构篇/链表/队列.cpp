#define DATA_Type int

#include <iostream>

using namespace std;

struct DATA_Base
{
    DATA_Type data;
    DATA_Base *Next;
};
class Queue
{
private:
    //储存头结点和尾结点
    DATA_Base *Front;
    DATA_Base *Rear;

public:
    Queue();
    bool In(DATA_Type *IN);
    bool Out(DATA_Type *Result);

};
//队列初始化
Queue::Queue()
{
    Rear=Front=(DATA_Base*)new DATA_Base;
    Front->Next=NULL;
}
bool Queue::In(DATA_Type *IN)
{
    DATA_Base *temp;
    //分配空间
    temp=(DATA_Base*)new DATA_Base;
    if(!temp)
    {
        cout<<"内存分配错误"<<endl;
        return false;
    }
    //录入数据
    temp->data=*IN;
    //在末尾添加NULL
    temp->Next=NULL;
    //更新尾指针
    Rear->Next=temp;
    Rear=temp;
    return true;
}
bool Queue::Out(DATA_Type *Result)
{
    //都指向头结点时代表队列为空
    if (Front==Rear)
    {
        //空队列时返回错误
        return false;
    }
    DATA_Base *Temp=Front->Next;
    *Result=Temp->data;
    //将头结点的Next指向下一位
    if (Front->Next==Rear)
    {
        //如果只有一个结点，就将尾指针和头指针指向头结点
        Rear=Front;
    }
    else
    {
        Front->Next=Temp->Next;
    }
    //释放内存
    delete []Temp;
    return true;
}
int main()
{
    Queue a;
    int Opt=1;
    int temp;
    while(Opt)
    {
        cout<<"****************************************"<<endl;
        cout<<"*************队列测试程序***************"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"1.手动入队"<<endl<<"2.手动出队"<<endl<<"3.全部出队"<<endl<<"0.退出程序"<<endl;
        cin>>Opt;
        switch(Opt)
        {
        case 1:
            cout<<"输入入队内容"<<endl;
            cin>>temp;
            if (a.In(&temp))
            {
                cout<<"入队成功"<<endl;
            }
            else
            {
                cout<<"入队失败"<<endl;
            }
            break;
        case 2:
            if (a.Out(&temp))
            {
                cout<<temp<<endl;
            }
            else
            {
                cout<<"队列为空！"<<endl;
            }
            break;
        case 3:
            while (a.Out(&temp))
            {
                cout<<temp<<endl;
            }
        }

    }
    return 0;
}
