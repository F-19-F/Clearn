#include<iostream>
#include<string>
using namespace std;
int Str_times (char* Search,char*Source)
{
	int t=0;//记录次数
	for (char* temp=Search;*Source!='\0';Source++)//temp用来记录比较的字符的地址
	{
		if (*temp==*Source)
		{
			temp++;//向后位移动
		}
		else 
		{
			temp=Search;
		}
		if (*temp=='\0')
		{
			t++;
			temp=Search;
		}//符合条件则增加次数
	}
	return t;
}
int main ()
{
	string a_source,b_source;
	cout<<"输入的字符串以回车结束"<<endl;
	getline(cin,a_source);//利用string来输入字符串可以减少内存占用
	getline(cin,b_source);
	char*a=(char*)a_source.c_str();//将string转化成char*类型，避免了char类型的大小问题
	char*b=(char*)b_source.c_str();
	cout<<"出现次数为"<<Str_times(a,b)<<endl;//利用已char*类型为形式参的函数来计算字母出现次数
	return 0;
}