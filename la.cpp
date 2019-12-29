#include <iostream>
using namespace std;
int main()
{
    char a;
    while ((a=getchar())!='\n')
    {
        if (a>='A'&&a<='Z')
        {
            a+=32;
        }
        cout<<a;
    }
    return 0;
}