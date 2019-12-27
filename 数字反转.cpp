#include<iostream>
using namespace std;
int s=0 ,j;
bool Zero(char*a,int j)//判断a[j]右边是否全为0
{
	if ((*(a+j)=='\0'||*(a+j)=='.')||(*(a+j)=='/'||*(a+j)=='%'))//判断异常异常情况
		return 1;
	if(*(a+j)=='0'&&Zero(a,j+1))
		return 1;
	return 0;
}
bool Zero1(char*a,int j,int k)//判断a[j]左边到a[k]是否全为0
{
	if ((*(a+j)=='\0'||*(a+j)=='.')||((*(a+j)=='/')||j==k-1))//判断异常情况
		return 1;
	if(*(a+j)=='0'&&Zero1(a,j-1,k))
		return 1;
	return 0;
}
void Zhen (char*a,int from,int to)//整数逆序输出函数
{
	int i;
	if (Zero(a,from))//如果全是0，就输出一个0
	{
		cout<<0;
	}
	else
	{
		for (i=to;i>=from;i--)
		{
			if (Zero(a,i))
			{
				continue;
			}
			cout<<*(a+i);
		}	
	}
}
void Zhen1 (char*a,int from,int to)//整数逆序输出函数（小数分数后位专用）
{
	int i;
	if (Zero(a,from))//如果全是0，就输出一个0
	{
		cout<<0;
	}
	else
	{
		for (i=to;i>=from;i--)
		{
			if (Zero(a,i)||Zero1(a,i,from))//如果左边全是零，则不输出
			{
				continue;
			}
			cout<<*(a+i);
		}	
	}
}
int Which(char*a)
{
	int i,way=0;
	for (i=0;*(a+i)!='\0';i++)
	{
		if (*(a+i)=='.')
		{
			j=i;
			way=1;
		}
		if (*(a+i)=='/')
		{
			j=i;
			way=2;
		}
		if (*(a+i)=='%')
		{
			j=i;
			way=3;
		}
		s++;
	}
	return way;
}
int main()
{
	char a[40];
	cin>>a;
	switch (Which(a))
	{
	case 0://整数
		Zhen(a,0,s-1);
		break;
	case 1://小数
	case 2://分数
		Zhen(a,0,j-1);
		cout<<a[j];
		Zhen1(a,j+1,s-1);
		break;
	case 3://百分数
		Zhen(a,0,j-1);
		cout<<a[j];
		break;
	}
	return 0;
}