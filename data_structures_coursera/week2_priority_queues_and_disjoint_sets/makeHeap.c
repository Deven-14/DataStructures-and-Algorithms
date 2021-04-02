#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int** BuildHeap(int n,int *a,int *no_of_swaps)
{
	int **swaps=(int**)malloc(4*n*sizeof(int*));
	for(int i=0;i<4*n;i++)
		*(swaps+i)=(int*)malloc(2*sizeof(int));
	int l,r,p,min_ind;
	*no_of_swaps=0;
	for(int i=n/2-1;i>=0;--i)
	{
		p=i;
		l=2*p+1;
		r=l+1;//2*i+2;
		while(l<n)
		{
			min_ind=l;
			if(r<n && a[r]<a[min_ind])
				min_ind=r;
			if(a[p]<a[min_ind])
				break;
			**(swaps+*no_of_swaps)=p;
			*(*(swaps+*no_of_swaps)+1)=min_ind;
			(*no_of_swaps)++;
			swap(&a[p],&a[min_ind]);
			p=min_ind;
			l=2*p+1;
			r=l+1;
		}
	}
	for(int i=*no_of_swaps;i<4*n;i++)
		free(*(swaps+i));
	swaps=(int**)realloc(swaps,(*no_of_swaps)*sizeof(int*));
	return swaps;
}

void output(int n,int **swaps)
{
	printf("%d\n",n);
	for(int i=0;i<n;++i)
		printf("%d %d\n",swaps[i][0],swaps[i][1]);
}

int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int no_of_swaps;
	int **swaps;
	swaps=BuildHeap(n,a,&no_of_swaps);
	output(no_of_swaps,swaps);
	for(int i=0;i<no_of_swaps;i++)
		free(*(swaps+i));
	free(swaps);
	return 0;
}