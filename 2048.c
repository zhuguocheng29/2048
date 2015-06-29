#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

int x[4][4],y[4][4],z=0,o=0;

typedef int row[4];

row *p=x, *q=y;

void show()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(p[i][j]==0)
			{
				printf("-     ");
			}
			else
			{
				printf("%-4d  ",p[i][j]);
			}
		}
		printf("\n\n");
	}
	printf("\n\n");
}
void over()
{
	int i,j;
	row *r;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			q[i][3-j]=p[i][j];
		}
	r=p,p=q,q=r;
}
void left()
{
	int i,j;
	row *r;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			q[3-j][i]=p[i][j];
		}
	r=p,p=q,q=r;
}
void right()
{
	int i,j;
	row *r;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			q[j][3-i]=p[i][j];
		}
	r=p,p=q,q=r;
}
void inc()
{
	int i,j,k;
	for(;;)
	{
		k=rand()%16,i=k/4,j=k%4;
		if(p[i][j]==0)break;
	}
	if(rand()%2)
	{
		p[i][j]=4;
	}
	else
	{
		p[i][j]=2;
	}
	z++;
}
void merge(char c)
{
	int i,j,k,t;
	switch(c)
	{
		case 'H':
			right();
		break;
		case 'K':
			over();
		break;
		case 'P':
			left();
		break;
	}
	for(i=0;i<4;i++)
	{
		for(j=k=3;j>=0 && p[i][j]==0;j--);
		if(j<0)continue;
		t=p[i][j],p[i][j]=0,p[i][k]=t;
		for(j--;j>=0;j--)
		{
			t=p[i][j];
			if(t!=0)
			{
				p[i][j]=0;
				if(p[i][k]==t)
				{
					z--,p[i][k]+=t;
					o=(t==512);
				}
				else
				{
					k--,p[i][k]=t;
				}
			}
		}
	}
	switch(c)
	{
		case 'H':
			left();
		break;
		case 'K':
			over();
		break;
		case 'P':
			right();
		break;
	}
	inc();
}
int main()
{
	char a,b;
	srand(time(NULL));
	inc();
	inc();
	show();
	while(z<16 && !o)
	{
		a=getch();
		if(a==-32)
		{
			b=getch();
			if(b==72||b==75||b==77||b==80)
			{
				merge(b);
				show();
			}
		}
	}
	if(o)
	{
		printf("congratulations!");
	}
	else
	{
		printf("sorry, you failed!");
	}
	getch();
	return 0;
}