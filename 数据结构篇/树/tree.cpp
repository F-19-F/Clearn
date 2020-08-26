#include <iostream>
#define Data_Type int
using namespace std;
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
    Tree_Child_Rela *Head, *Tail;

public:
    Tree_Base *next;
    Tree_Base(int num, int parent, int data);
    bool Add_Child(int child_num);
    int Del_Child(int child_num);
    Data_Type Get_Data();
    Tree_Child_Rela *Get_Child_Rela();
    ~Tree_Base();
};
Tree_Base::Tree_Base(int num, int parent, int data)
{
    this->data = data;
    this->num = num;
    this->parent = parent;
    Head = NULL;
    Tail = NULL;
}
bool Tree_Base::Add_Child(int child_num)
{
    //第一次添加孩子时初始化
    if (Head == NULL)
    {
        //生成头结点
        Head = new Tree_Child_Rela;
        Head->num = -2;
        //生成正常结点
        Head->next = new Tree_Child_Rela;
        Head->next->num = child_num;
        Head->next->next = NULL;
        Tail = Head->next;
        return true;
    }
    //正常情况下的添加
    Tree_Child_Rela *temp = new Tree_Child_Rela;
    temp->num = child_num;
    temp->next = NULL;
    Tail->next = temp;
    Tail = temp;
    return true;
}
//没有初始化就返回或者已经删空就返回1，没有对应孩子就返回2，正常返回0
int Tree_Base::Del_Child(int child_num)
{
    //没有初始化或者初始化后已删完就返回错误
    if (Head == NULL || Tail == NULL)
    {
        return 1;
    }
    //开始遍历链表
    Tree_Child_Rela *temp, *last_temp;
    temp = Head->next;
    while (temp)
    {
        //如果找到了对应孩子
        if (temp->num == child_num)
        {
            last_temp->next = temp->next;
            //如果是最后一个结点，则更新Tail指针
            if (temp == Tail)
            {
                Tail = last_temp;
            }
            delete temp;
            return 0;
        }
        //保存上一个结点地址
        last_temp = temp;
        temp = temp->next;
    };
    //执行到这里代表没有找到对应结点
    return 2;
}
Data_Type Tree_Base::Get_Data()
{
    return data;
}
Tree_Child_Rela *Tree_Base::Get_Child_Rela()
{
    //如果没有初始化也返回空
    if (!Head)
    {
        return NULL;
    }
    return Head->next;
}
Tree_Base::~Tree_Base()
{
    Tree_Child_Rela *temp = Head;
    Tree_Child_Rela *temp_next_bak;
    while (temp)
    {
        temp_next_bak = temp->next;
        delete temp;
        temp = temp_next_bak;
    }
}
class tree
{
private:
    Tree_Base *base, *tail;
    int Num_Point;

public:
    tree(Data_Type First_Data);
    bool Add_Node(int Parent, Data_Type data);
    int Tree_Print();
    int Recu_Print(int level, Tree_Base *target, bool Paren_Print);
    int Child_Print(int level, Tree_Child_Rela *target);
    Tree_Base *GetBPoint(int num);
};
tree::tree(Data_Type First_Data)
{
    //初始化链表
    Num_Point = 0;
    base = new Tree_Base(Num_Point++, -1, First_Data);
    base->next = NULL;
    tail = base;
}
bool tree::Add_Node(int Parent, Data_Type data)
{
    Tree_Base *temp = new Tree_Base(Num_Point++, Parent, data);
    (GetBPoint(Parent)->Add_Child(Num_Point-1));
    temp->next = NULL;
    tail->next = temp;
    tail = temp;
    return true;
}
//通过下标寻找结点
Tree_Base *tree::GetBPoint(int num)
{
    //如果数字大于指针则返回错误值0
    if (num >= Num_Point)
    {
        return NULL;
    }
    Tree_Base *temp;
    temp = base;
    while (num--)
    {
        temp = temp->next;
    }
    return temp;
}
int tree::Tree_Print()
{
    return Recu_Print(0,base,false);
}
int tree::Recu_Print(int level, Tree_Base *target, bool Paren_Print)
{
    int R_used = 0;
    Tree_Child_Rela *temp = target->Get_Child_Rela();
    Tree_Base *Btemp;
    //如果是递归过程中，则不打印结点本身的内容，因为已经在上一层递归中打印，即只有根结点会执行下面的代码
    if (!Paren_Print)
    {
        //再打印偏移量
        for (int i = 0; i < level; i++)
        {
            cout << " ";
        }
        //再打印结点本身的数据
        cout << target->Get_Data();
        R_used++;
    }
    //如果没有孩子，之后什么都不打印
    if (!temp)
    {
        return R_used;
    }
    //有孩子的情况下，打印孩子结点
    while (temp)
    {
        //获取Tree_Base指针
        Btemp = GetBPoint(temp->num);
        //开始打印
        //先换行
        cout << endl;
        //打印在原来基础上+1的偏移量
        for (int i = 0; i < level + 1; i++)
        {
            cout << " ";
        }
        //再打印孩子的数据
        cout << (GetBPoint(temp->num))->Get_Data();
        R_used++;
        //如果当前孩子结点也有孩子结点,则开始递归打印其孩子结点
        if (!Btemp->Get_Child_Rela())
        {
            R_used += Recu_Print(level + 2, Btemp ,true);
        }
        temp = temp->next;
    }
    return R_used;
}

int main()
{
    tree a(1);
    a.Add_Node(0,2);
    a.Add_Node(0,3);
    a.Tree_Print();
    return 0;
}