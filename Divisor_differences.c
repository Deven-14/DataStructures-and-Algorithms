//2017 problem 1
#include<stdio.h>
typedef struct div_diff
{
	int m;
	int k;
	int n;
	int diff[50][2];
}Div_diff;
int input_n()
{
	int n;
	scanf("%d",&n);
	return n;
}
void input_all_m_k(int n,Div_diff d[])
{
	int i;
	for(i=0;i<n;i++)
		scanf("%d%d",&d[i].m,&d[i].k);
}
int divisors_of_m(int m,int div[])
{
	int i,j=0;
	for(i=1;i<=m;i++)
	{
		if(m%i==0)
		{
			div[j]=i;
			j++;
		}
	}
	return j;
}
Div_diff divisor_differences_of_m(Div_diff d)
{
	int div[d.m],i,j,n;
	n=divisors_of_m(d.m,div);
	d.n=0;
	for(i=0;i<n-1;i++)
	{
		j=i+1;
		while(div[j]-div[i]<d.k)//<d.k imp it can be != also but this is better as we don't want after >
			j++;
		if(div[j]-div[i]==d.k)
		{
			d.diff[d.n][0]=div[i];
			d.diff[d.n][1]=div[j];
			d.n++;
		}
	}
	return d;
}
void divisor_differences_of_all_num(int n,Div_diff d[])
{
	int i;
	for(i=0;i<n;i++)
	{
		d[i]=divisor_differences_of_m(d[i]);
	}
}
void output(int n,Div_diff d[])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		printf("%d,%d: ",d[i].m,d[i].k);
		for(j=0;j<d[i].n;j++)
			printf("(%d,%d) ",d[i].diff[j][0],d[i].diff[j][1]);
		printf("\n");
	}
}
int main()
{
	int n;
	n=input_n();
	Div_diff d[n];
	input_all_m_k(n,d);
	divisor_differences_of_all_num(n,d);
	output(n,d);
	return 0;
}