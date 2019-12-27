#include<iostream>
#include<cstring>
using namespace std;
class Person
{
private:
	char IdPerson[19];
	char Name[20];
	char Sex[7];
	char Birthday[11];
	char HomeAddress[100];
public:
	Person();
	void Infor_Input();
	void Infor_Show();
	Person(Person&S);
};
Person::Person():IdPerson("未知"),Name("未知"),Sex("未知"),Birthday("未知"),HomeAddress("未知"){}
void Person::Infor_Input()
{
	cout<<"输入姓名:";
	cin>>Name;
	cout<<endl<<"输入身份证号码:";
	cin>>IdPerson;
	cout<<endl<<"输入性别:";
	cin>>Sex;
	cout<<endl<<"输入生日:";
	cin>>Birthday;
	cout<<endl<<"输入家庭地址:";
	cin>>HomeAddress;
}
void Person::Infor_Show()
{
	cout<<"姓名:";
	cout<<Name;
	cout<<endl<<"身份证号码:";
	cout<<IdPerson;
	cout<<endl<<"性别:";
	cout<<Sex;
	cout<<endl<<"生日:";
	cout<<Birthday;
	cout<<endl<<"家庭地址:";
	cout<<HomeAddress<<endl;
}
Person::Person(Person&S)
{
	strcpy(Name,S.Name);
	strcpy(IdPerson,S.IdPerson);
	strcpy(Sex,S.Sex);
	strcpy(Birthday,S.Birthday);
	strcpy(HomeAddress,S.HomeAddress);
}
int main()
{
	Person S1;
	S1.Infor_Input();
	Person S2(S1);
	S2.Infor_Show();
	S1.Infor_Show();
	return 0;
}