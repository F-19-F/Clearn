#include <iostream>
#define data_type int
using namespace std;
//*****************************此链表第一位没有数据*******************************************//
struct DATA_Base
{
    data_type data;
    DATA_Base *Next;
};
class list
{
protected:
    int length;                    //length为链表当前长度
    DATA_Base *Head = NULL, *Last; //Head用来存储头结点的地址，Last用来存储链表的尾部
public:
    list()
    {
        Initlist();
    }
    ~list() //析构同时把分配的内存释放
    {
        Clearlist();
    }
    bool Initlist()
    {
        if (Head) //不允许已经存在Head时调用Initlist
            return NULL;
        if ((Head = (DATA_Base *)malloc(sizeof(DATA_Base))))
        {
            Head->Next = NULL;
            Last = Head;
            length = 0;
        }
        else
            return NULL;
        return 1;
    }
    bool Insertlist(data_type data, int n) //插入数据
    {
        DATA_Base *Temp = Head;
        int i = 0; //i指向为位次指示器
        while (Temp != NULL)
        {
            if (i + 1 == n)
            {
                DATA_Base *T; //存储前一个结点的尾部
                T = Temp->Next;
                Temp->Next = (DATA_Base *)malloc(sizeof(DATA_Base)); //分配内存
                Temp = Temp->Next;                                   //使用新分配的内存
                Temp->Next = T;                                      //将插入的下一位结点地址赋给插入到的结点
                Temp->data = data;                                   //给插入的结点赋值
                length++;
                return true;
            }
            Temp = Temp->Next;
            i++;
        }
        return false;
    }
    bool Deletelist(int n) //删除某个结点
    {
        if (n <= length && n > 0)
        {
            DATA_Base *Temp = Head;
            for (int i = 0; i < n - 1; i++) //寻找要删除结点前一位结点地址
            {
                Temp = Temp->Next;
            }
            DATA_Base *Temp_t = Temp->Next->Next; //Temp_t用来存储删除结点的Next
            free(Temp->Next);                     //释放内存
            Temp->Next = Temp_t;                  //将后面的结点连接上去
            length--;
            return true;
        }
        else
        {
            return false;
        }
    }
    void Showlist() //直接展示数据
    {
        DATA_Base *temp;
        temp = Head->Next;
        while (temp != NULL)
        {
            cout << "data:" << temp->data << endl;
            temp = temp->Next;
        }
    }
    void Createlist() //构建一个完整链表
    {
        int i = length + 1;
        int times = i;
        DATA_Base *temp = Last;
        int data_temp;
        cout << "**********data小于0时将结束输入***********" << endl;
        cout << "请输入第" << i << "组数据" << endl;
        cout << "data:";
        cin >> data_temp;
        while (data_temp > 0)
        {
            if (i == times)
            {
                temp = Last->Next = (DATA_Base *)malloc(sizeof(DATA_Base));
                temp->data = data_temp;
                Last = temp;
                Last->Next = NULL;
                i++;
                length++;
                continue;
            }
            cout << "请输入第" << i << "组数据" << endl;
            cout << "data:";
            cin >> data_temp;
            if (data_temp <= 0)
            {
                cout << "创建结束" << endl;
                break;
            }
            temp = Last->Next = (DATA_Base *)malloc(sizeof(DATA_Base));
            temp->data = data_temp;
            Last->Next = temp;
            Last = temp;
            Last->Next = NULL;
            i++;
            length++;
        }
    }
    void Clearlist()
    {
        DATA_Base *temp = Head;
        DATA_Base *temp_Next;
        while (temp)
        {
            temp_Next = temp->Next;
            free(temp);
            temp = temp_Next;
        }
        Head = Last = NULL;
    }
};
//以上是动态单链表
//下面开始循环链表类的定义
class Loop_list:public list
{
    public:
    Loop_list();//调用函数使得单链表转化成循环链表
    ~Loop_list();
    bool Make_Loop();
    bool Back_single();
    void Showlist(); //直接展示数据
    void Createlist();
    friend void Problem();
};
Loop_list::~Loop_list()
{
    Back_single();
}
bool Loop_list::Back_single()//将循环链表还原成单链表，以便解决析构问题
{
    Last->Next=NULL;
}
Loop_list::Loop_list()
{
    Make_Loop();
}
bool Loop_list::Make_Loop()
{
    if (Head==Last)
    {
        return true;
    }
    else
    {
        
        DATA_Base *Temp=Head->Next;
        free(Head);//删除空结点
        Head=Temp;
        Last->Next=Head;//使最后一个结点的指针域指向第一个
        return true;
    }
    
}
void Loop_list::Showlist() //直接展示数据
    {
        DATA_Base *temp;
        temp = Head;
        do
        {
            cout << "data:" << temp->data << endl;
            temp = temp->Next;
        }
        while (temp!=Head);
    }
     void Loop_list::Createlist()
     {
         list::Createlist();
         Make_Loop();
     }
int main()
{
    Loop_list a;
    a.Createlist();
    a.Showlist();
    return 0;
}