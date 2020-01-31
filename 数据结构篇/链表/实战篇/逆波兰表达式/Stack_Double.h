#define Stack_default_Length 20
#define IncreaseNum 5
#define Data_Type double
//This is a simply realized Stack head file from Stack_R.h
class Stack_R
{
private:
    Data_Type *top;
    Data_Type *base;
    int Stack_Length;
public:
    Stack_R();
    int Getlen();
    Data_Type Get_Top();
    bool Push(Data_Type *In);
    bool Pop(Data_Type *A_return);
};
Stack_R::Stack_R() : Stack_Length(Stack_default_Length)
{
    top = base = new Data_Type[Stack_default_Length];
}
int Stack_R::Getlen()
{
    return top-base;
}
Data_Type Stack_R::Get_Top()
{
    if (top!=base)
    return *(top-1);
    else
    {
        return 0;
    }
    
}
bool Stack_R::Push(Data_Type *In)
{
    if (top - base >= Stack_Length)
    {
        base = (Data_Type *)realloc(base, (Stack_Length + IncreaseNum)*sizeof(Data_Type));
        if (!base)
        {
            return false;
        }
        top = base + Stack_Length;
        Stack_Length+=IncreaseNum;
    }
    *(top++)=*In;
    return true;
}
bool Stack_R::Pop(Data_Type *A_return)
{
    if (top==base)
    {
        return false;
    }
    *A_return=*(--top);
    return true;
}