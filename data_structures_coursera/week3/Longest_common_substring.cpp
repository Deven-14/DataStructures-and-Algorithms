#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

struct hashset
{
	long long *h1;
	long long *h2;
	int n;
};
typedef struct hashset HashSet;

HashSet precompute_hashvalues( char *str, int prime1,int prime2, int x )
{
	int len=strlen(str);
	HashSet h;
	long long *h1=(long long*)malloc((len+1)*sizeof(long long));
	long long *h2=(long long*)malloc((len+1)*sizeof(long long));
	h1[0]=0;
	h2[0]=0;
	for(int i=1;i<=len;++i){
		h1[i] = ( x * h1[i-1] + str[i-1] ) % prime1;
		h2[i] = ( x * h2[i-1] + str[i-1] ) % prime2;
	}
	h.h1=h1;
	h.h2=h2;
	h.n=len+1;
	return h;
}

long long* Power(int prime,int x,int len)
{
	long long *p=(long long*)malloc((len+1)*sizeof(long long));
	p[0]=1;
	for(int i=1;i<=len;++i)
		p[i]=x*p[i-1]%prime;
	return p;
}

struct result
{
	int i,j,len;
};
typedef struct result Result;

Result common_substring_of_length_mid(HashSet hs,HashSet ht,int lenSubstr,int p1,int p2)
{
	Result r={0,0,0};
	std::map<int,int> m;
	int prime1=1000000007,prime2=1000000009;
	int nSubstrh_s=hs.n-lenSubstr;
	for(int i=0;i<nSubstrh_s;++i){
		m.insert({((hs.h1[i+lenSubstr]-p1*hs.h1[i])%prime1+prime1)%prime1,i});
	}
	int nSubstrh_t=ht.n-lenSubstr;
	long long substrhash_t;
	for(int i=0;i<nSubstrh_t;++i)
	{
		substrhash_t=((ht.h1[i+lenSubstr]-p1*ht.h1[i])%prime1+prime1)%prime1;
		auto itr=m.find(substrhash_t);
		if(itr==m.end())
			continue;
		long long substrhash_s2,substrhash_t2;
		int j=itr->second;
		substrhash_s2=((hs.h2[j+lenSubstr]-p2*hs.h2[j])%prime2+prime2)%prime2;
		substrhash_t2=((ht.h2[i+lenSubstr]-p2*ht.h2[i])%prime2+prime2)%prime2;
		if(substrhash_s2!=substrhash_t2)
			continue;
		r.i=j;
		r.j=i;
		r.len=lenSubstr;
		return r;
	}
	return r;
}

Result longest_common_substring( char *s, char *t)
{
	Result r={0,0,0},r1={0,0,0};
	int slen=strlen(s);
	int tlen=strlen(t);
	int len_smallerstr=(slen<tlen)?slen:tlen;
	int prime1=1000000007;
	int prime2=1000000009;
	int x=263;//better use rand() func
	HashSet hs,ht;
	hs=precompute_hashvalues(s,prime1,prime2,x);
	ht=precompute_hashvalues(t,prime1,prime2,x);
	int first=0,last=len_smallerstr,mid;
	long long *pow1=Power(prime1,x,len_smallerstr);
	long long *pow2=Power(prime2,x,len_smallerstr);
	while(first<=last)
	{
		mid=(first+last)/2;
		r1=common_substring_of_length_mid(hs,ht,mid,pow1[mid],pow2[mid]);
		if(r1.len==mid)
		{
			r=r1;
			first=mid+1;
		}
		else
			last=mid-1;
	}
	free(hs.h1);
	free(hs.h2);
	free(ht.h1);
	free(ht.h2);
	free(pow1);
	free(pow2);
	return r;
}

int main()
{
	char *s,*t;
	s=(char*)malloc(100000*sizeof(char));
	t=(char*)malloc(100000*sizeof(char));
	while(scanf("%s%s",s,t)!=EOF)
	{
		Result r;
		r=longest_common_substring(s,t);
		printf("%d %d %d\n",r.i,r.j,r.len);
	}
	free(s);
	free(t);
	return 0;
}
