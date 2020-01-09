#include <iostream>
//#include<cstdio>
using namespace std;

#define data_type int

struct double_cur_base
{
    double_cur_base* pre;
    double_cur_base* next;
    data_type data;
};
class double_cur
{
private:
    double_cur_base *Head;
    int Length;
public:
    double_cur();
    ~double_cur();
    bool Insert(int n,data_type In);//插入一个结点
    bool Delete(int n,data_type *r);//删除对应结点
    void Print();
    double_cur_base * Findcur(int n);//返回第n个结点的地址
};
bool double_cur::Delete(int n,data_type *r)
{
    if (n>Length)
    {
        return false;
    }
    double_cur_base *Temp=Findcur(n-1);
    double_cur_base *Temp_1=Temp->next->next;//备份要删除结点的下一个结点
    *r=Temp->next->data;//输出删除结点的值
    delete Temp->next;//删除第n个结点
    Temp->next=Temp_1;//将后继结点连接上
    Temp_1->pre=Temp;//更新后继结点的pre
    return true;
}
double_cur::~double_cur()
{
    double_cur_base *Temp=Head;
    while(Temp!=Head)
    {
        double_cur_base *Temp_1;
        Temp_1=Temp->next;
        delete Temp;
        Temp=Temp_1;
    }
}
void double_cur::Print()
{
    double_cur_base *Temp=Head->next;
    while(Temp!=Head)
    {
        cout<<Temp->data<<endl;
        Temp=Temp->next;
    }
}
double_cur::double_cur():Length(0)
{
    Head=new double_cur_base;
    Head->next=Head;
    Head->pre=Head;
}
double_cur_base* double_cur::Findcur(int n)
{
    if (n>Length+1)
    {
        return NULL;
    }
    double_cur_base* Temp=Head;
    for (int i=0;i<n;i++)
    {
        Temp=Temp->next;
    }
    return Temp;
}
bool double_cur::Insert(int n,data_type In)
{
    if (double_cur_base* Temp=Findcur(n-1))
    {
        double_cur_base *Temp_1=new double_cur_base;
        Temp_1->pre=Temp;//将新分配的结点的pre指向第n-1个结点
        Temp_1->next=Temp->next;//将新分配的结点的next指向原来的第n个结点
        Temp->next->pre=Temp_1;//将原来表中的第n个结点的pre指向新分配的结点
        Temp->next=Temp_1;//将第n-1个结点的next指向新分配的结点
        Temp_1->data=In;//给插入的结点赋值
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
    double_cur a;
    int re;
    int *b=&re;
    a.Insert(1,2);
    a.Insert(1,3);
    a.Insert(1,4);
    a.Insert(4,7);
    a.Delete(4,b);
    a.Print();
    cout<<"删除的值为"<<re<<endl;
    return 0;
}