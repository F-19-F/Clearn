#include <stdio.h>
#include <stdlib.h>
#define max_score 100
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
    int ave_score;
    data_base *next;
} data_base;
//交换链表中的两个相邻结点
int getlength(data_base *target)
{
    int i = 0;
    target = target->next;
    while (target)
    {
        i++;
        target=target->next;
    }
    return i;
}
int changer(data_base *first, data_base *second)
{
    data_base temp;
    //备份第一个结点的尾指针
    data_base *next_temp;
    next_temp = first->next;
    temp = *first;
    //复制第二个结点的尾指针给temp
    temp.next = second->next;
    //将第二个结点的内容赋给第一个结点
    *first = *second;
    //将复制后结点的尾指针换成第一个结点原来的地址
    first->next = next_temp;
    //此时temp可以直接赋给second
    *second = temp;
}
//使用冒泡排序对总成绩排序
//不同模式对应通过不同成绩进行排名
//-1对应总成绩，自然数对应不同科目
int sort(data_base *target_s, int mode)
{
    data_base *target = target_s->next;
    int length = getlength(target_s);
    if (mode < -1)
    {
        return 0;
    }
    if (mode == -1)
    {
        for (int i = 0; i < length-1; i++)
        {
            for (int j = 0; j < length - i-1; j++)
            {
                if (target->sum_score < target->next->sum_score)
                {
                    changer(target, target->next);
                }
                target=target->next;
            }
            target = target_s->next;
            //获取下次开始遍历的地址
            for (int k = 0; k < i +1; k++)
            {
                target = target->next;
            }
        }
    }
    else
    {
        for (int i = 0; i < length-1; i++)
        {
            for (int j = 0; j < length - i-1; j++)
            {
                if (target->score[mode] < target->next->score[mode])
                {
                    changer(target, target->next);
                }
                target=target->next;
            }
            target = target_s->next;
            //获取下次开始遍历的地址
            for (int k = 0; k < i +1; k++)
            {
                target = target->next;
            }
        }
    }
}
//定义输入函数
//way代表输入方式 0-新建 1-从文件导入
void data_output(data_base *target)
{
    //获取头指针
    target = target->next;
    while (target)
    {
        printf("| %-15s       |%d        |%d      |%d        |\n", &target->name, target->score[0], target->score[1], target->score[2]);
        target = target->next;
    }
}
int data_input(int way, data_base *target)
{

    //定义临时输入变量
    //用于存储上一个结点，方便处理末尾结点
    data_base *last_base;
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
        int *score = target->score;
        while (1)
        {
            //存储分配新内存前的地址
            last_base = target;
            target->next = (data_base *)malloc(sizeof(data_base));
            target = target->next;
            printf("姓名输入'#'结束输入\n请输入姓名:");
            scanf("%s", &target->name);
            //处理输入中断
            if (target->name[0] == '#')
            {
                //释放刚创建的结点
                free(last_base->next);
                //添加尾结点标志
                last_base->next = NULL;
                break;
            }
            for (int i = 0; i < kinds; i++)
            {
            again:
                printf("请输入第%d项成绩:", i);
                scanf("%d", &target->score[i]);
                //判断分数输入是否错误
                if ((target->score[i]) < 0 || (target->score[i]) > max_score)
                {
                    printf("分数输入错误！请重新输入\n");
                    goto again;
                }
            }
            //计算总成绩
            for (int i = 0; i < kinds; i++)
            {
                target->sum_score += target->score[i];
            }
            //计算平均成绩
            target->ave_score = target->sum_score / kinds;
        }
    }
}
data_base *Init()
{
    //添加头结点
    data_base *as_return;
    as_return = (data_base *)malloc(sizeof(data_base));
    as_return->next = NULL;
    return as_return;
}
int main()
{
    data_base *a = Init();
    data_input(0, a);
    //sort-ok---
    sort(a,-1);
    //changer -ok
    //changer(a->next->next,a->next->next->next);
    data_output(a);
    //getlength-ok
    //printf("%d",getlength(a));
    return 0;
}