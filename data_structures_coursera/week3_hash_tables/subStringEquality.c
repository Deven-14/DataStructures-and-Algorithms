#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long* precompute(int prime,int x,char *s)
{
	int n=strlen(s);
	long long *h=(long long*)malloc((n+1)*sizeof(long long));
	h[0]=0;//we require a base value to start, to not insert an if statement, we do this so that, we it is asked for the s[0] ele, the formula h[a+l]-xh[a] works
	for(int i=1;i<=n;++i)
		h[i]=(x*h[i-1]+s[i-1])%prime;
	return h;
}

void processQueries(char *t,int n,int **q)
{
	long long *h1,*h2;
	int prime1=1000000007,prime2=1000000009;
	int x=rand()%(prime1-8)+1;//should be greater than 1//if u take random x then it might be big, so 'y' will be big, so the substringhash might be negative, so add prime to that, even if the x is small say 15, 15^7 will be 9 digits, so we have to add and %prime
	h1=precompute(prime1,x,t);
	h2=precompute(prime2,x,t);
	//char **result=malloc(n*sizeof(char*));
	int len=strlen(t);
	long long *p1,*p2;
	p1=malloc((len+1)*sizeof(long long));//power1
	p2=malloc((len+1)*sizeof(long long));
	p1[0]=1;
	p2[0]=1;//x^0=1
	for(int i=1;i<=len;++i)//so that the power can be obtained in O(1) and not O(l'length of substr')************
	{//THIS WAS THE MAIN REASON FOR EXCEDING TIME LIMIT ****************************
		p1[i]=p1[i-1]*x%prime1;
		p2[i]=p2[i-1]*x%prime2;
	}
	for(int i=0;i<n;++i)
	{
		//result[i]=malloc(4*sizeof(char));
		int a=q[i][0];
		int b=q[i][1];
		int l=q[i][2];
		//long long substr1Hash=(h1[a+l]+prime1-y*h1[a])%prime1;//might be negative, it might be very less than prime, so doing in while loop
		long long substr1Hash;
		long long substr2Hash;
		/*long long y=1;
		for(int i=1;i<=l;++i)
			y=y*x%prime1;*///this power function is taking uncessary time, use a map of store it in an array;
		substr1Hash=((h1[a+l]-p1[l]*h1[a])%prime1+prime1)%prime1;//coz it can be negative
		substr2Hash=((h1[b+l]-p1[l]*h1[b])%prime1+prime1)%prime1;
		if(substr1Hash!=substr2Hash)
		{
		    //strcpy(result[i],"No");
			printf("No\n");
		    continue;
		}
		/*y=1;
		for(int i=1;i<=l;++i)
			y=y*x%prime2;*/
		substr1Hash=((h2[a+l]-p2[l]*h2[a])%prime2+prime2)%prime2;
		substr2Hash=((h2[b+l]-p2[l]*h2[b])%prime2+prime2)%prime2;
		if(substr1Hash==substr2Hash)
			printf("Yes\n");//strcpy(result[i],"Yes");
		else
			printf("No\n");//strcpy(result[i],"No");
		free(q[i]);//******************time limit excedding
	}
	free(h1);
	free(h2);
	//return result;
}

/*void output(int n,char **result)
{
	for(int i=0;i<n;++i)
		printf("%s\n",result[i]);
}*///crossing time limit********************

int main()
{
	char *t=malloc(500001*sizeof(char));
	scanf("%s",t);
	t=realloc(t,(strlen(t)+1)*sizeof(char));
	int n;
	scanf("%d",&n);
	int **q=malloc(n*sizeof(int*));
	for(int i=0;i<n;++i)
	{
		*(q+i)=malloc(3*sizeof(int));
	    scanf("%d%d%d",&q[i][0],&q[i][1],&q[i][2]);
	}
	//char **result;
	//result=processQueries(t,n,q);
	processQueries(t,n,q);
	//output(n,result);
	/*for(int i=0;i<n;++i)
	{
		free(q[i]);//free query in the processQueries function itself*******************
		//free(result[i]);
	}*/
	free(q);
	//free(result);
	return 0;
}