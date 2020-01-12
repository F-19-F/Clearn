#include <iostream>

using namespace std;

typedef char data_type;

// #define data_type char

struct double_cur_base
{
    double_cur_base* pre;
    double_cur_base* next;
    data_type data;
};
class double_cur
{
private:
    double_cur_base* Head;
    int Length;
public:
    double_cur();
    ~double_cur();
    bool Insert(int n, data_type In);//插入一个结点
    bool Delete(int n, data_type* r);//删除对应结点
    void Print(bool Case);
    double_cur_base* Findcur(int n);//返回第n个结点的地址
    friend void Passwd(double_cur*,int n);
};
void Passwd(double_cur *a,int n)
{
    for (int i = 0; i < 26; i++)
    {
        a->Insert(1, 'Z' - i);
    }
    double_cur_base* Temp = a->Head;
    for (int i = 0; i < a->Length; i++)
    {
        Temp = Temp->next;//使Temp指向最后一个元素
    }
    //double_cur_base *Temp = a->Head->pre;//使Temp指向最后一个节点
    Temp->next = a->Head->next;//使其变成循环链表
    a->Head->next->pre = Temp;//使第一个节点的pre指向最后一个节点
    Temp = a->Head->next;
    delete a->Head;//释放头节点
    a->Head = Temp;
    if (n>0)
    {
        while (n--)
        {
            Temp = Temp->next;
        }
        a->Head = Temp;
    }
    else
    {
        while (n++)
        {
            Temp = Temp->pre;
        }
        a->Head = Temp;
   }
}
bool double_cur::Delete(int n, data_type* r)
{
    if (n > Length)
    {
        return false;
    }
    double_cur_base* Temp = Findcur(n - 1);
    double_cur_base* Temp_1 = Temp->next->next;//备份要删除结点的下一个结点
    *r = Temp->next->data;//输出删除结点的值
    delete Temp->next;//删除第n个结点
    Temp->next = Temp_1;//将后继结点连接上
    Temp_1->pre = Temp;//更新后继结点的pre
    Length--;
    return true;
}
double_cur::~double_cur()
{
    double_cur_base* Temp = Head;
    while (Temp != Head)
    {
        double_cur_base* Temp_1;
        Temp_1 = Temp->next;
        delete Temp;
        Temp = Temp_1;
    }
}
void double_cur::Print(bool Case)
{
    double_cur_base* Temp;
    if (Case)
    Temp = Head->next;
    else
    {
        Temp = Head;
    }
    do
    {
        cout << Temp->data << " ";
        Temp = Temp->next;
    }
    while (Temp != Head);
}
double_cur::double_cur() :Length(0)
{
    Head = new double_cur_base;
    Head->next = Head;
    Head->pre = Head;
}
double_cur_base* double_cur::Findcur(int n)
{
    if (n > Length + 1)
    {
        return NULL;
    }
    double_cur_base* Temp = Head;
    for (int i = 0; i < n; i++)
    {
        Temp = Temp->next;
    }
    return Temp;
}
bool double_cur::Insert(int n, data_type In)
{
    if (double_cur_base* Temp = Findcur(n - 1))
    {
        double_cur_base* Temp_1 = new double_cur_base;
        Temp_1->pre = Temp;//将新分配的结点的pre指向第n-1个结点
        Temp_1->next = Temp->next;//将新分配的结点的next指向原来的第n个结点
        Temp->next->pre = Temp_1;//将原来表中的第n个结点的pre指向新分配的结点
        Temp->next = Temp_1;//将第n-1个结点的next指向新分配的结点
        Temp_1->data = In;//给插入的结点赋值
        Length++;
        return true;
    }
    else
    {
        return NULL;
    }
}
int main()
{
    int n;
    double_cur a;
    //char re;
    //char* b = &re;
    cin >> n;
    Passwd(&a, n);
    a.Print(false);
   /* a.Insert(1, '2');
    a.Insert(1, '3');
    a.Insert(1, '4');
    a.Insert(4, '7');
    a.Delete(4, b);
    a.Print(true);*/
    /*cout << "删除的值为" << re << endl;*/
    return 0;
}