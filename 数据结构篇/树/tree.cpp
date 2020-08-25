#include <iostream>
#define Data_Type int
//定义同层孩子链表存储结构
struct Tree_Child_Rela
{
    int num;
    Tree_Child_Rela *next;
};
class Tree_Base
{
private:
    int parent;
    int num;
    Data_Type data;
    Tree_Child_Rela *Head,*Tail;
public:
    Tree_Base *next;
    Tree_Base(int num,int parent,int data);
    bool Add_Child(int child_num);
    int Del_Child(int child_num);
    Tree_Child_Rela* Get_Child_Rela();
    ~Tree_Base();
};
Tree_Base::Tree_Base(int num,int parent,int data)
{
    this->data=data;
    this->num=num;
    this->parent=parent;
    Head=NULL;
    Tail=NULL;
}
bool Tree_Base::Add_Child(int child_num)
{
    //第一次添加孩子时初始化
    if (Head==NULL)
    {
        //生成头结点
        Head=new Tree_Child_Rela;
        Head->num=-2;
        //生成正常结点
        Head->next=new Tree_Child_Rela;
        Head->next->num=child_num;
        Head->next->next=NULL;
        Tail=Head->next;
        return true;
    }
    //正常情况下的添加
    Tree_Child_Rela *temp=new Tree_Child_Rela;
    temp->num=child_num;
    temp->next=NULL;
    Tail->next=temp;
    Tail=temp;
    return true;
}
//没有初始化就返回或者已经删空就返回1，没有对应孩子就返回2，正常返回0
int Tree_Base::Del_Child(int child_num)
{
    //没有初始化或者初始化后已删完就返回错误
    if (Head==NULL||Tail==NULL)
    {
        return 1;
    }
    //开始遍历链表
    Tree_Child_Rela *temp,*last_temp;
    temp=Head->next;
    while (temp)
    {
        //如果找到了对应孩子
        if (temp->num==child_num)
        {
            last_temp->next=temp->next;
            //如果是最后一个结点，则更新Tail指针
            if (temp==Tail)
            {
                Tail=last_temp;
            }
            delete temp;
            return 0;
        }
        //保存上一个结点地址
        last_temp=temp;
        temp=temp->next;
    };
    //执行到这里代表没有找到对应结点
    return 2;
}
Tree_Child_Rela* Tree_Base::Get_Child_Rela()
{
    return Head->next;
}
Tree_Base::~Tree_Base()
{
    Tree_Child_Rela *temp=Head;
    Tree_Child_Rela *temp_next_bak;
    while (temp)
    {
        temp_next_bak=temp->next;
        delete temp;
        temp=temp_next_bak;
    }
}
class tree
{
private:
    Tree_Base *base,*tail;
    int Num_Point;
public:
    tree(Data_Type First_Data);
    bool Add_Node(int Parent,Data_Type data);
    void Print_Tree();
};
tree::tree(Data_Type First_Data)
{
    //初始化链表
    Num_Point=0;
    base=new Tree_Base(Num_Point++,-1,First_Data);
    base->next=NULL;
    tail=base;
}
bool tree::Add_Node(int Parent,Data_Type data)
{
    Tree_Base *temp=new Tree_Base(Num_Point++,Parent,data);
    tail->next=temp;
    tail=temp;
    return true;
}
void tree::Print_Tree()
{
    
}
int main()
{

    return 0;
}