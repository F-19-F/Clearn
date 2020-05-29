#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char Names[6][16];
int Scores[6][8];
//i为选手编号
typedef struct student
{
    char Name[16];
    int Score[8];
    float last_score;
}student;
//结构体专用计算得分
void CalculateScore_struct(student *target)
{
    int max=target->Score[0],min=target->Score[0];
    int sum=0;
    for (int j=0;j<8;j++)
    {
        if (max<target->Score[j])
        {
            max=target->Score[j];
        }
        if (min>target->Score[j])
        {
            min=target->Score[j];
        }
        sum+=target->Score[j];
    }
    sum=sum-max-min;
    target->last_score=sum/6;
}
void InputName(char input[16],int player)
{
    strcpy(Names[player],input);
}
void InputScore(int input[8],int player)
{
    //检查输入的数据
    for(int i=0; i<8; i++)
    {
        again:
        if(input[i]<60||input[i]>100)
        {
            printf("%s的第%d组得分输入错误，请重新输入: ",Names[player],i+1);
            scanf("%d",&input[i]);
            goto again;
        }
    }
    for (int i=0; i<8; i++)
    {
        Scores[player][i]=input[i];
    }
}
float CalculateScore(int i)
{
    int max=Scores[i][0],min=Scores[i][0];
    int sum=0;
    for (int j=0;j<8;j++)
    {
        if (max<Scores[i][j])
        {
            max=Scores[i][j];
        }
        if (min>Scores[i][j])
        {
            min=Scores[i][j];
        }
        sum+=Scores[i][j];
    }
    sum=sum-max-min;
    return sum/6.0;
}
void InputNamesAndScores()
{
    char name[16];
    int score[8];
    for (int i=0;i<6;i++)
    {
        printf("输入第%d名选手的姓名: ",i+1);
        scanf("%s",name);
        //吸收回车
        getchar();
        InputName(name,i);
        for(int j=0;j<8;j++)
        {
            printf("请输入%s的第%d项得分: ",name,j+1);
            scanf("%d",&score[j]);
            //吸收回车
            getchar();
        }
        InputScore(score,i);
    }
}
float FindScore(char name[16])
{
    for (int i=0;i<6;i++)
    {
        if (!strcmp(Names[i],name))
        {
            return CalculateScore(i);
        }
    }
    printf("没有名字叫%s的选手",name);
}
int main()
{
    InputNamesAndScores();
    //排名
    int order[6];
    //存储最后得分
    //使用二维数组存储分数和对应序号
    int score_temp[6][2];
    for (int i=0;i<6;i++)
    {
        score_temp[i][1]=i;
        score_temp[i][0]=CalculateScore(i);
    }
    //使用冒泡排序进行排名
    for (int i=0;i<5;i++)
    {
        for (int j=0;j<5-i;j++)
        {
            if (score_temp[j][0]<score_temp[j+1][0])
            {
                int temp[2];
                temp[0]=score_temp[j][0];
                temp[1]=score_temp[j][1];
                score_temp[j][0]=score_temp[j+1][0];
                score_temp[j][1]=score_temp[j+1][1];
                score_temp[j+1][0]=temp[0];
                score_temp[j+1][1]=temp[1];
            }
        }
    }
    for(int i=0;i<6;i++)
    {
        order[i]=score_temp[i][1];
    }
    for (int  i = 0; i < 6; i++)
    {
        printf("%d:  %-15s  %-2f\n",i+1,Names[order[i]],CalculateScore(order[i]));
    }
    /*****************************以下是结构体的排序********************************/
    /********************************************************************************/
    /********************************************************************************/
    /********************************************************************************/
    //使用结构体进行排序
    /*
    student  a[6];
    student temp;
    //计算最后得分
    for (int i=0;i<6;i++)
    {
        CalculateScore_struct(&a[i]);
    }
    for(int i=0;i<5;i++)
    {
        for (int j=0;j<5-i;j++)
        {
            if(a[j].last_score<a[j].last_score)
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    for (int  i = 0; i < 6; i++)
    {
        printf("%d:  %-15s  %-2f\n",i+1,a[i].Name,a[i].last_score);
    }*/
    getchar();
    return 0;
}