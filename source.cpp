#include <stdio.h>
void Chai (int a,int b[3][3],int i)//拆数函数
{
	int c,m,j;
	c=1000;
	for (j=0;j<=2;j++)
	{
		m=c/10;
		b[i][j]=(a%c)/(m);
		c/=10;
	}
}
int Choose(int a[3][3])//判断函数，用来判断每位数是否符合条件
{
	int i,j,m,n;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			for (m=0;m<3;m++)
				for (n=0;n<3;n++)
					{
						if (i==m&&j==n)
							continue;
						if (a[i][j]==a[m][n]||a[m][n]==0)
						return 0;
					}
	return 1;
}
int main()
{
	int m[3],a[3][3],i;
	for (m[0]=123;m[0]<=329;m[0]++)
	{
		m[1]=2*m[0];
		m[2]=3*m[0];
		for (i=0;i<3;i++)
		{
			Chai(m[i],a,i);
		}
		if (Choose (a))
			printf ("%d %d %d\n",m[0],m[1],m[2]);
	}
	getchar();
}