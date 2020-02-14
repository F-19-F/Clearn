#include <iostream>

using namespace std;

int Hannoi(int n,char x,char y,char z)
{
    if (n==1)
    {
        cout<<x<<"-->"<<z<<endl;
        return 1;
    }
    else
    {
        int i=0;
        i+=Hannoi(n-1,x,z,y);
        cout<<x<<"-->"<<z<<endl;
        i++;
        i+=Hannoi(n-1,y,x,z);
        return i;
    }
}
int main()
{
    int n,i;
    cin>>n;
    cout<<"最优步骤为:"<<endl;
    i=Hannoi(n,'x','y','z');
    cout<<"共"<<i<<"步"<<endl;
}