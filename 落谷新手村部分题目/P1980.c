#include <stdio.h>
/*洛谷新手村 P1980 */
/*https://www.luogu.org/problem/P1980*/
int Powern (int a,int n)
{
	int i,b=1;
	if (n==0)
		b=1;
	for (i=0;i<n;i++)
		b=b*a;
	return b;
}
int Chai (int i,int x)
{
	int m=10,n,r,c,p;
	for (c=0,p=0;;m*=10,p++)
	{
		n=m/10;
		r=(i%m)/n;
		if (r==0&&i<Powern(10,p))
		{
			break;
		}
		if(r==x)
		{
			c++;
		}
	}
	return c;
}
int main()
{
	int n,x,i,t;
	scanf ("%d%d",&n,&x);
	if (n<10)
	{
		if (n>=x)
			t=1;
	}
	for (i=1,t=0;i<=n;i++)
	{
			t+=Chai(i,x);
	}
	printf ("%d",t);
	return 0;
}