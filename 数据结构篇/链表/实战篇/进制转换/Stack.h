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