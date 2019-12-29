#include <iostream>
#include<cstring>
using namespace std;
struct DATA 
{
	char name[20];
	int Mark;
	DATA *Next;
};
class list 
{
private :
	int length;
	DATA *Head=NULL,*Last;//Head用来存储头结点的地址，Last用来存储链表的尾部
public :
	list ()
	{
		printf ("create class list\n");
		Initlist();
	}
	~list()//析构同时把分配的内存释放
	{
		Clearlist();
	}
	bool Initlist ();//链表初始化
	bool Insertlist(int Mark,char*name,int n);//插入数据
	bool Deletelist(int n);//删除某个结点
	bool Addlist(int Mark,char*name);//添加新数据
	void Showlist();//展示数据
	void Createlist();//构建一个完整链表
	void Clearlist();
};
bool list::Initlist ()//初始化链表
{
	if (Head)//不允许已经存在Head时调用Initlist
		return NULL;
	if((Head=(DATA*)malloc (sizeof(DATA))))
	{	
		Head->Next=NULL;
		Last=Head;
		length=0;
	}
	else 
		return NULL;
	return 1;
}
bool list::Insertlist(int Mark,char* name,int n)
{
	DATA *Temp=Head;
	if (n==length)//方便插入节点在末尾时快速调整Last指针,可以加速插入末尾时的速度
		if(Addlist(Mark,name))
			return true;
		else
			return false;
	int i=0,j=0;//i指向为位次指示器
	while (Temp!=NULL)
	{
		if (i+1==n)
		{
			DATA *T;//存储前一个结点的尾部
			T=Temp->Next;
			Temp->Next=(DATA*)malloc(sizeof(DATA));//分配内存
			Temp=Temp->Next;//使用新分配的内存
			Temp->Next=T;//将插入的下一位结点地址赋给插入到的结点
			Temp->Mark=Mark;//下面是给插入的结点赋值
			while (1)
			{
				Temp->name[j]=*name;
				if (*name=='\0')
					break;
				name++;
				j++;
			}
			length++;
			return true;
		}
		Temp=Temp->Next;
		i++;
	}
	return false;
}
bool list::Addlist(int Mark,char *name)//在末尾添加一个结点
{
	DATA *Temp=Last;
	if(Temp->Next=(DATA*)malloc(sizeof (DATA)))
		Temp=Temp->Next;
	else return false;
	Temp->Mark=Mark;
	int j=0;
	while (1)
	{
		Temp->name[j]=*name;
		if (*name=='\0')
			break;
		name++;
		j++;
	}
	Temp->Next=NULL;
	Last=Temp;
	length++;
}
 bool list::Deletelist(int n) //删除某个结点
    {
        if (n <= length && n > 0)
        {
            DATA *Temp = Head;
            for (int i = 0; i < n - 1; i++) //寻找要删除结点前一位结点地址
            {
                Temp = Temp->Next;
            }
            DATA *Temp_t = Temp->Next->Next; //Temp_t用来存储删除结点的Next
            free(Temp->Next);                     //释放内存
            Temp->Next = Temp_t;                  //将后面的结点连接上去
            if (n == length)                      //删除最后一个结点时更新Last
            {
                Last = Temp;
            }
            length--;
            return true;
        }
        else
        {
            return false;
        }
    }
void list::Showlist()
{
	DATA *temp;
	temp=Head->Next;
	while (temp!=NULL)
	{
		cout<<"姓名"<<temp->name<<endl;
		cout<<"分数"<<temp->Mark<<endl;
		cout<<endl;
		temp=temp->Next;
	}
}
void list::Createlist()
{
	int i=length+1;
	int times=i;
	DATA *temp=Last;
	char Name[20];
	int Mark;
	cout<<"**********分数小于0时将结束输入***********"<<endl;
	cout<<"请输入第"<<i<<"组数据"<<endl;
	cout<<"分数:";
	cin>>Mark;
	while (Mark>0)
	{
		if (i==times)
		{
			temp=Last->Next=(DATA*)malloc(sizeof(DATA));
			cout<<"名字:";
			cin>>Name;
			temp->Mark=Mark;
			char *name=Name;
			int j=0;
			while (1)
			{
				temp->name[j]=*name;
				if (*name=='\0')
					break;
				name++;
				j++;
			}
			Last=temp;
			Last->Next=NULL;
			i++;
			continue;
		}
		cout<<"请输入第"<<i<<"组数据"<<endl;
		cout<<"分数:";
		cin>>Mark;
		if (Mark<=0)
			break;
		cout<<"姓名:";
		cin>>Name;
		temp=Last->Next=(DATA*)malloc(sizeof(DATA));
		temp->Mark=Mark;
		char *name=Name;
			int j=0;
			while (1)
			{
				temp->name[j]=*name;
				if (*name=='\0')
					break;
				name++;
				j++;
			}
		Last->Next=temp;
		Last=temp;
		Last->Next=NULL;
		i++;
	}

}
void list::Clearlist()//对每个结点调用free以清理链表
{
	DATA*temp=Head;
	DATA*temp_Next;
	while(temp)
	{
		temp_Next=temp->Next;
		free(temp);
		temp=temp_Next;
	}
	Head=Last=NULL;
}
int main()
{
	list a;
	char *b="shabi";
	a.Createlist();
	/*a.Addlist(12,b);
	a.Addlist(13,b);*/
	a.Insertlist(16,b,3);
	a.Showlist();
	return 0;
}