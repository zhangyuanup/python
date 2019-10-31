#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
int c[50][50];   //用c[i][j]记录X[i]与Y[j] 的LCS 的长度
int b[50][50];   //b[i][j]记录c[i][j]是通过哪一个子问题的值求得的，以决定搜索的方向
char f[50];
 
/*取c[i-1][j]和c[i][j-1]的最大值,并记录c[i][j]是通过哪一个子问题的值求得的，以决定搜索的方向*/
int Max(int m,int n,int i,int j)
{
	if(m > n)
	{
		b[i][j] = -1;
		return m;
	}
	else
	{
		b[i][j] = 1;
		return n;
	}
}
/*递归打印LCS的元素内容*/
void print(int i,int j,int s,char x[],char y[])
{
	if(b[i][j] == 0)
	{
		f[s-1] = x[i-1];
		i--;j--;s--;
		print(i,j,s,x,y);
	}
	else if(b[i][j] == -1)
	{
		i--;
		print(i,j,s,x,y);
	}
	else if(b[i][j] == 1)
	{
		j--;
		print(i,j,s,x,y);
	}
}
int LCS(char x[],char y[])
{
	int i,j;
	int x_len,y_len;
	x_len = strlen(x);
	y_len = strlen(y);
//	printf("   ");
/*	for(i = 0;i < y_len;i++)
	{
		//printf("%c  ",y[i]);
	}*/
	//printf("\n");
	for(i = 1;i <=x_len;i++)
	{
		//printf("%c  ",x[i-1]);
		for(j = 1;j <=y_len;j++)
		{
			if(x[i-1] == y[j-1])
			{
				c[i][j] = c[i-1][j-1] +1;
				b[i][j] = 0;
				//printf("%d  ",c[i][j]);
			}
			else
			{
				c[i][j] = Max(c[i-1][j],c[i][j-1],i,j);
				//printf("%d  ",c[i][j]);
			}
		}
	//	printf("\n");
}

	//打印X和Y的LCS
	printf("X和Y的LCS是:");
	print(x_len,y_len,c[x_len][y_len],x,y);
	printf("%s",f);
	printf("\n");
	return c[x_len][y_len];
}
 
void main()
{
	char X[51],Y[51],M[51],P[51],Q[51];
	char DNA[4]={'A','C','G','T'};
	int i,s1,s2;
	srand((unsigned)time(NULL));
	for(i=0;i<10;i++){
	//	j=rand()%4;
		X[i]=DNA[rand()%4];
		Y[i]=DNA[rand()%4];
		M[i]=DNA[rand()%4];
		P[i]=DNA[rand()%4];
		Q[i]=DNA[rand()%4];


	}
	X[i]='\0';
	Y[i]='\0';
	M[i]='\0';
	P[i]='\0';
	Q[i]='\0';
	printf("%s\n",X);
	printf("%s\n",Y);
	printf("%s\n",M);
	printf("%s\n",P);
	printf("%s\n",Q);
/*	for(i=0;i<50;i++){
		printf("%c",X[i]);
	}
	printf("\n");
	for(i=0;i<50;i++){	
		printf("%c",Y[i]);
	}*/
	s1 = LCS(X,Y);
	s2 = LCS(f,M);

	printf("X和Y的LCS: %d \n",s2);
}

