#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define M1 7
#define N1 8
#define T1 27
#define M2 7
#define N2 8
#define T2 23
 

void prinFile(FILE *fp,int m,int n,int t)
{
	int i,j,v,k;
	int c[m][n]={};
	for(int count=0,i=0,j=0;count<t;count++)
	{
		srand((unsigned)time(NULL));
		k=rand()%n+1;
		j+=k;
		while(j>=n||c[i][j]!=0||i>=m)
		{
			if(j>=n)
			{
				i++;
				j-=n;
				if(i>=m)
				i=0;
			}
			if(c[i][j]!=0)
			j++;
		}
		c[i][j]=1;
	}
	fprintf(fp,"%d %d %d\n",m,n,t);
	//for(int count=0;count<T1;count++)
	int count=0;
	{
		for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		if(c[i][j]!=0){
		fprintf(fp,"%d %d %d\n",i+1,j+1,rand()%m+1);
		count++;
	}
	printf("count = %d\n",count);
	}
}

int main()
{
	FILE *fp=fopen("dict.txt","w");
	prinFile(fp,M1,N1,T1);
	prinFile(fp,M2,N2,T2);
	fclose(fp);
	return 0;
}
