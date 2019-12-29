#include <iostream>
#include <ctime>
using namespace std;
#define data_type int
#define MAXSIZE 100
struct DATA_BASE
{
	data_type data;
	int cur;
};
class S_list
{
private:
	DATA_BASE data[MAXSIZE];

public:
	S_list();
	bool list_insert(int n, data_type Input);
	bool list_delete(int n, int *a);
	int malloc_S();
	int list_getlen();
	int list_getcur(int n);
	int list_findmid();
	void list_show();
};
int S_list::list_findmid()//使用快慢指针来寻找中间值
{
	int faster, lower;
	faster = lower = data[MAXSIZE - 1].cur;
	if (list_getlen()%2!=0)//为奇数时faster退1
	faster=MAXSIZE-1;
	while (faster = data[data[faster].cur].cur)
	{
		lower = data[lower].cur;
	}
	return data[lower].data;
}
S_list::S_list()
{
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		data[i].cur = i + 1;
	}
	data[MAXSIZE - 1].cur = 0;
}
bool S_list::list_insert(int n, data_type Input)
{
	if (n > list_getlen() + 1 || n <= 0)
		return false;
	else
	{
		int cur_temp;
		int k = list_getcur(n - 1);
		int temp = data[k].cur;//存储上一位的cur
		if (!(cur_temp=malloc_S()))//判断链表是否已满
		{
			cout<<"数组内存已满！！！"<<endl;
			return false;
		}
		data[k].cur = cur_temp;//将分配的cur赋给上一位的cur
		data[data[k].cur].data = Input;//给新分配的分量赋值
		data[data[k].cur].cur = temp;//将插入位原先的下一位cur赋给新分配的分量
		return true;
	}
}
int S_list::malloc_S()
{
	if (list_getlen()==MAXSIZE-2)//当内存已满时不分配
	return 0;
	int result = data[0].cur;
	data[0].cur = data[result].cur;
	return result;
}
void S_list::list_show()
{
	int k = MAXSIZE - 1;
	if (k = data[k].cur)
	{
		int i = 1;
		do
		{
			//printf("第%d个数据是:", i);
			cout << data[k].data << " ";
			i++;
		} while (k = data[k].cur);
		cout << endl;
	}
	else
		cout << "没有数据！" << endl;
}
int S_list::list_getlen()//获取链表长度
{
	int k = MAXSIZE - 1, i = 0;
	while (k = data[k].cur)
		i++;
	return i;
}
int S_list::list_getcur(int n)//得到某一位的cur
{
	int k = MAXSIZE - 1;
	for (int i = 0; i < n; i++)
	{
		k = data[k].cur;
	}
	return k;
}
bool S_list::list_delete(int n, int *a)//删除某一位的值，并用a返回
{
	if (n > list_getlen() || n <= 0)
		return false;
	else
	{
		int k = list_getcur(n - 1);
		int temp = data[k].cur;
		data[k].cur = data[temp].cur; //将要删除分量的上一个分量的cur指向要删除分量的cur
		data[temp].cur = data[0].cur; //将删除分量的cur指向空闲分量
		data[0].cur = temp;			  //将删除的分量并入空闲分量
		*a = data[temp].data;
		return true;
	}
}
int main()
{
	int IN = 10;
	S_list a;
	while (1)
	{
		if (IN == 0)
			break;
		switch (IN)
		{
		case 1:
			srand((unsigned int)time(NULL));
			for (int i = 0; i < 20; i++)
			{
				if(!a.list_insert(1, rand() % 100 + 1))
				{
					cout<<"本次已经插入"<<i<<"个数据"<<endl;
					break;
				}
			}
			break;
		case 2:
			a.list_show();
			break;
		case 3:
		if(a.list_getlen()==MAXSIZE-2)
		{
			cout<<"无法插入，因为数组内存已满"<<endl;
			goto
			end;
		}
			int n, data;
			cout<<"插入位置:";
			cin >> n ;
			cout<<"插入内容:";
			cin>>data;
			end:
			a.list_insert(n, data);
			break;
		case 4:
			int data_return;
			cout<<"删除的位置:";
			cin >> n;
			if(a.list_delete(n, &data_return))
			printf("已经删除内容为%d的分量\n", data_return);
			else
			{
				cout<<"删除失败"<<endl;
			}
			
			break;
		case 5:
			cout << a.list_findmid()<<endl;
			break;
		default:
			printf("************************************************************\n");
			printf("*************************测试程序**************************\n");
			printf("************************************************************\n");
			printf("1-随机创建20个数据\n");
			printf("2-输出现有数据\n");
			printf("3-插入数据\n");
			printf("4-删除分量\n");
			printf("5-输出中间值\n");
			printf("0-退出程序\n");
		}
		cout << "请选择你的操作:";
		cin >> IN;
	}
	return 0;
}