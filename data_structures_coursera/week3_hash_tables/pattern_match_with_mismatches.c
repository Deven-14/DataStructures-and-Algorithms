#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashSet
{
	int prime1;
	long long *h1;
	int prime2;
	long long *h2;
	int nh;
};
typedef struct hashSet HashSet;

HashSet precomute_hashvalues(char *s,int prime1,int prime2,int x)//for substrings prime1,prime2, but if we want to check if found the same strings then we should first do hash_func for two string then check by naive method if they are equal, coz we subtract for substrings the probability becomes very less and hence we can use two primes instead of naviely checking
{
	HashSet h;
	long long *h1,*h2;
	int len=strlen(s);
	h1=(long long*)malloc((len+1)*sizeof(long long));
	h2=(long long*)malloc((len+1)*sizeof(long long));
	h1[0]=h2[0]=0;
	for(int i=1;i<=len;++i)
	{
		h1[i]=(h1[i-1]*x+s[i-1])%prime1;
		h2[i]=(h2[i-1]*x+s[i-1])%prime2;
	}
	h.h1=h1;
	h.h2=h2;
	h.nh=len+1;
	h.prime1=prime1;
	h.prime2=prime2;
	return h;
}

struct result
{
	int size;
	int capacity;
	int *arr;
};
typedef struct result Result;

Result find_mismatches(int k,HashSet Ht,HashSet Hp,int x)
{
	Result r;
	r.size=0;
	r.capacity=1;
	r.arr=(int*)malloc(r.capacity*sizeof(int));
	int nSubstr_t=Ht.nh-Hp.nh+1;//len(t)+1-(len(p)+1)+1;//no of substr of t with size len_p
	int len_p=Hp.nh-1;
	int lo,hi,mid,count,index;
	long long substrHash_t1,substrHash_p1,substrHash_t2,substrHash_p2;
	long long *p1,*p2;
	p1=malloc((len_p+1)*sizeof(long long));
	p2=malloc((len_p+1)*sizeof(long long));
	p1[0]=p2[0]=1;
	for(int i=1;i<=len_p;++i)
	{
	    p1[i]=p1[i-1]*x%Ht.prime1;
	    p2[i]=p2[i-1]*x%Ht.prime2;
	}
	for(int i=0;i<nSubstr_t;++i)
	{
		int j=i;
		count=0;
		while(j<=i+len_p-1)//each substr in t, eg: if t=abcde, p=abd,k=2; then first substr=abc, 2nd=bcd, so in first sub str, we get mid=b, and then ab=ab, then lo=mid+1 and it'll fail for c,it gets out and j=index+1,i.e we check from c again,and then count++ and we are out of both loops, instead of checking each char, using binary search we check if substrings are equal, if it was substr=cde then after one inner loop, lo++, so then substr=de and then binary search is applied on this
		{
		    lo=0;//starting index of substr of p or a substr of t, is p=abc, it might be abc, or bc here, lo=0 i.e b and hi=1 i.e c or c, itself
		    hi=len_p+i-j-1;//ending index of that of the above substr, +i-j coz j might increment and we have to decrement the len of the substr
			index=-1;
			while(lo<=hi)
			{
				mid=((lo+hi)/2);//index of mid term of the substr, mid+1 will be the len from lo to mid index
				substrHash_t1=( ( Ht.h1[j+mid+1] - p1[mid+1] * Ht.h1[j] ) % Ht.prime1 + Ht.prime1 ) % Ht.prime1;//*********j not i, coz, j can be incremented, i.e initially it might be j=0,of t=abcde,p=def,k=2, initi, j=0,i.e the inner loop fails once, j=1 and it'll be j=b,and end will be still c,coz k=2,we have to check twice,then after this after one for loop, j=1 again but end will be d this time, then itll go inside and j might become 2/3 and end will be d itlsef untill the next for loop
				substrHash_p1=( ( Hp.h1[j-i+mid+1] - p1[mid+1] * Hp.h1[j-i] ) % Hp.prime1 + Hp.prime1 ) % Hp.prime1;//mid+1 coz lo and high are index and not length of the substr
				substrHash_t2=( ( Ht.h2[j+mid+1] - p2[mid+1] * Ht.h2[j] ) % Ht.prime2 + Ht.prime2 ) % Ht.prime2;
				substrHash_p2=( ( Hp.h2[j-i+mid+1] - p2[mid+1] * Hp.h2[j-i] ) % Hp.prime2 + Hp.prime2 ) % Hp.prime2;//j-i coz in the while(j<=i_len-1) j might increment in the same while loop and the len of the substr might decrease, from the second for loop, j and i will increase from 1 to len of t, but p should start over from 0 index, so in a for loop if j is incremented due to while(j<=i+len_p-1) then j=2, but it shouldn't be j=2 in p, it should increment only once, so j-i,i.e 2-1=1,so it is incremented once
				if(substrHash_t1==substrHash_p1 && substrHash_t2==substrHash_p2)
				{
					lo=mid+1;//next index after the substr is equal
					index=mid;//index of substr
				}
				else
					hi=mid-1;
			}
			if(index==-1)
			{
				j++;
				count++;
			}
			else
				j=j+index+1;//j+=index+1, coz,'index' it is index of substr after the last equal substr, then we add this to index of t
			if(count>k)
				break;
		}
		if(count<=k)
			r.arr[r.size++]=i;
		if(r.size==r.capacity)
		{
			r.capacity=r.size*2;
			r.arr=realloc(r.arr,r.capacity*sizeof(int));
		}
	}
	free(p1);
	free(p2);
	return r;
}

Result solvequery(int k,char *t,char *p)
{
	HashSet Ht,Hp;
	int prime1=1000000007,prime2=1000000009;
	int x=rand()%(prime1-1)+1;//+1,so that it is greater than 1 and prime-1,so that if it rand()%prime=prime-1, so x=prime-1+1=prime, which should not be the case, it should be less than prime, and greater than 0
	Ht=precomute_hashvalues(t,prime1,prime2,x);
	Hp=precomute_hashvalues(p,prime1,prime2,x);
	Result r=find_mismatches(k,Ht,Hp,x);
	free(Ht.h1);
	free(Ht.h2);
	free(Hp.h1);
	free(Hp.h2);
	return r;
}

int main()
{
	char *t,*p;
	t=(char*)malloc(200000*sizeof(char));
	p=(char*)malloc(100000*sizeof(char));
	int k;
	while(scanf("%d%s%s",&k,t,p)!=EOF)
	{
		Result r=solvequery(k,t,p);
		printf("%d ",r.size);
		for(int i=0;i<r.size;++i)
			printf("%d ",r.arr[i]);
		printf("\n");
		free(r.arr);
	}
	return 0;
}