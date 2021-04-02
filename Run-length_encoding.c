// 2017 problem 3
#include<stdio.h>
typedef struct encode
{
	int m;
	int s[100];
	int n;
	int t[100];
}Encode;// can make this 2d array, by doing int m; int s[100]; then e[n][2]; one for input and another for output
int input_n()
{
	int a;
	scanf("%d",&a);
	return a;
}
void input_all_sequence(int n,Encode e[n])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		e[i].m=input_n();
		for(j=0;j<e[i].m;j++)
			scanf("%d",&e[i].s[j]);
	}
}
Encode en_code_between_limits(int i,int j,Encode e)
{
	int n;
	if((n=j-i+1)>3)//(j-i+1) because 2-0 =2 but there are 3 elements s[0],s[1],s[2]
	{
		e.t[e.n++]=0;
		e.t[e.n++]=n;
		e.t[e.n++]=e.s[i];
		return e;
	}
	else if(e.s[i]!=0)
	{
		while(i<=j)
		{
			e.t[e.n++]=e.s[i];
			i++;
		}
		return e;
	}
	else if((n=j-i+1)>1)//for s[i]=0
	{
		e.t[e.n++]=0;
		e.t[e.n++]=n;
		e.t[e.n++]=e.s[i];
		return e;
	}
	else// for only one 0
	{
		e.t[e.n++]=0;
		e.t[e.n++]=0;
		return e;
	}
}
Encode en_code_a_sequence(Encode e)
{
	e.n=0;// imp because it en_code_bw_lim should start from e.n=0
	int i=0,j;
	while(i!=e.m)
	{
		j=i;
		while(e.s[j]==e.s[i])
			j++;
		e=en_code_between_limits(i,j-1,e);
		i=j;
	}
	return e;
}
void en_code_all_sequence(int n,Encode e[n])
{
	int i;
	for(i=0;i<n;i++)
		e[i]=en_code_a_sequence(e[i]);
}
void output(int n,Encode e[n])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<e[i].m;j++)
			printf("%d ",e[i].s[j]);
		printf("\n");
		for(j=0;j<e[i].n;j++)
			printf("%d ",e[i].t[j]);
		printf("\n\n");
	}
}
int main()
{
	int n;
	n=input_n();
	Encode e[n];
	input_all_sequence(n,e);
	en_code_all_sequence(n,e);
	output(n,e);
	return 0;
}