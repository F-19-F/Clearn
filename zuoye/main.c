#include <stdio.h>
#include <stdlib.h>
#define kinds 3
#define name_1 语文
#define name_2 数学
#define name_3 英语
#define basic_input                           \
    printf("\n输入'#'结束输入\n请输入姓名:"); \
    scanf("%s", *name);                       \
    for (int i = 0; i < kinds; i++)           \
    {                                         \
        printf("\n请输入第%d项成绩:", i);     \
        scanf("%d", score++);                 \
    }
//定义存储结构
typedef struct data_base
{
    char name[30];
    int score[kinds];
    int sum_score;
    data_base *next;
} data_base;
//定义输入函数
//way代表输入方式 0-新建 1-从文件导入
void data_output(data_base* target)
{
    //跳过头结点
    target=target->next;
    while(target)
    {
        printf("| %-15s       |%d        |%d      |%d        |\n",&target->name,target->score[0],target->score[1],target->score[2]);
        target=target->next;
    }
}
int data_input(int way, data_base *target)
{
    
    //定义临时输入变量
    //用于存储上一个结点，方便处理末尾结点
    data_base* last_base;
    //从文件导入
    if (way == 1)
    {
        ;
    }
    else
    {
        //while ()
        //basic_input;
        //用于存储上一个结点，方便处理末尾结点
        int *score =target->score;
        while (1)
        {
            //存储分配新内存前的地址
            last_base=target;
            target->next=(data_base*)malloc(sizeof(data_base));
            target=target->next;
            printf("姓名输入'#'结束输入\n请输入姓名:");
            scanf("%s", &target->name);
            //处理输入中断
            if (target->name[0] == '#')
            {
                //释放刚创建的结点
                free(last_base->next);
                //添加尾结点标志
                last_base->next=NULL;
                break;
            }
            for (int i = 0; i < kinds; i++)
            {
                printf("\n请输入第%d项成绩:", i);
                scanf("%d", &target->score[i]);
            }
        }
    }
}
data_base *Init()
{
    //添加头结点
    data_base *as_return;
    as_return = (data_base *)malloc(sizeof(data_base));
    as_return->next=NULL;
    return as_return;
}
int main()
{
    data_base *a = Init();
    data_input(0, a);
    data_output(a);
    return 0;
}