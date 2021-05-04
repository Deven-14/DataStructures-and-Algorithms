#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long polyHash(char *s,unsigned int prime,unsigned int multi)
{
	int len=strlen(s);
	unsigned long long hash=0;
	for(int i=len-1;i>=0;--i)
		hash=(hash*multi+s[i])%prime;
	return hash;
}

unsigned long long* precompute(char *t,int len_p,unsigned int prime,unsigned int multi)
{
	int len_t=strlen(t);
	unsigned long long *hashvalues=(unsigned long long*)malloc((len_t-len_p+1)*sizeof(unsigned long long));
	hashvalues[len_t-len_p]=polyHash(t+len_t-len_p,prime,multi);
	long long y=1;
	for(int i=1;i<=len_p;++i)//just to keep the value bw 0 and p-1, or else u can use power function also
		y=y*multi%prime;
	long long tempHash;// it shouldn't be unsigned*************coz see down
	for(int i=len_t-len_p-1;i>=0;--i){
		tempHash=(multi*hashvalues[i+1]+t[i]-y*t[i+len_p]);//this can be negative, so don't %prime here, first add p, then 
		while(tempHash<0)
			tempHash+=prime;
		hashvalues[i]=tempHash%prime;
	}
	return hashvalues;
}

struct result
{
	int *indices;
	int size;
	int capacity;
};
typedef struct result Result;

int AreEqual(char *t,char *p)
{
	int len=strlen(p);
	for(int i=0;i<len;i++)
		if(t[i]!=p[i])
			return 0;
	return 1;
}

Result rabinKrap_method(char *t,char *p)
{
	unsigned int prime=1000000007;
	unsigned int multi=rand()%prime;
	int len_t=strlen(t);
	int len_p=strlen(p);
	unsigned long long *hashvalues=precompute(t,len_p,prime,multi);
	Result r;
	r.size=0;
	r.capacity=1;
	r.indices=(int*)malloc(r.capacity*sizeof(int));
	unsigned long long hash_p=polyHash(p,prime,multi);
	int hashvalues_size=len_t-len_p+1;
	for(int i=0;i<hashvalues_size;i++)
	{
		if(hash_p!=hashvalues[i])
			continue;
		if(AreEqual(t+i,p))
			r.indices[r.size++]=i;
		if(r.size==r.capacity)
		{
			r.capacity=2*r.size;
			r.indices=(int*)realloc(r.indices,r.capacity*sizeof(int));
		}
	}
	free(hashvalues);
	return r;
}

void output(Result r)
{
	int size=r.size;
	for(int i=0;i<size;i++)
		printf("%d ",r.indices[i]);
}

int main()
{
	char *p=malloc(500000*sizeof(char));
	scanf("%s",p);
	p=realloc(p,(strlen(p)+1)*sizeof(char));
	char *t=malloc(500000*sizeof(char));
	scanf("%s",t);
	t=realloc(t,(strlen(t)+1)*sizeof(char));
	Result r;
	r=rabinKrap_method(t,p);
	output(r);
	free(r.indices);
	free(p);
	free(t);
	return 0;
}