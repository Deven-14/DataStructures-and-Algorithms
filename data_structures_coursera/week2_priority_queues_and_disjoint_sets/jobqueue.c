#include <stdio.h>
#include <stdlib.h>

struct worker
{
	int id;
	long long next_free_time;
};
typedef struct worker Worker;

struct assigned_work
{
	int worker_id;
	long long start_time;
};
typedef struct assigned_work Assigned_work;

int compare(Worker w1,Worker w2)
{
	if(w1.next_free_time<w2.next_free_time)
		return 1;
	else if(w1.next_free_time>w2.next_free_time)
		return 0;
	else
		return (w1.id<w2.id)?1:0;
}

void swap(Worker *a,Worker *b)
{
	Worker temp=*a;
	*a=*b;
	*b=temp;
}

void HeapifyDown(int no_of_workers,Worker *w)
{
	int parent=0;
	int lc=2*parent+1;
	int rc=2*parent+2;
	int smaller_child_index;
	while(lc<no_of_workers)
	{
		smaller_child_index=lc;
		if(rc<no_of_workers && compare(w[rc],w[lc]))
			smaller_child_index=rc;
		if(compare(w[parent],w[smaller_child_index]))//if parent is smaller than smaller child index, break
			break;
		swap(&w[parent],&w[smaller_child_index]);
		parent=smaller_child_index;
		lc=2*parent+1;
		rc=2*parent+2;
	}
}

void changePriority(int no_of_workers,Worker *w,long long new_duration)//changePriority of the top guy
{
	long long old_duration=w[0].next_free_time;
	w[0].next_free_time=new_duration;//it can only be greater
	if(new_duration>old_duration)
		HeapifyDown(no_of_workers,w);
}

Worker* initializing_workers(int no_of_workers)
{
	Worker *w;
	w=(Worker*)malloc(no_of_workers*sizeof(Worker));
	for(int i=0;i<no_of_workers;++i)
	{
		w[i].id=i;
		w[i].next_free_time=0;
	}
	return w;
}

Assigned_work* Assing_work(int no_of_workers,int m,int *jobs)
{
	Worker *w;
	w=initializing_workers(no_of_workers);
	Assigned_work *a=malloc(m*sizeof(Assigned_work));
	for(int i=0;i<m;++i)
	{
		a[i].worker_id=w[0].id;
		a[i].start_time=w[0].next_free_time;
		changePriority(no_of_workers,w,w[0].next_free_time+jobs[i]);
	}
	free(w);
	return a;
}

void output(int m,Assigned_work *a)
{
	for(int i=0;i<m;i++)
		printf("%d %lld\n",a[i].worker_id,a[i].start_time);
}

int main()
{
	int no_of_workers,m;
	scanf("%d %d",&no_of_workers,&m);
	int jobs[m];
	for(int i=0;i<m;++i)
		scanf("%d",&jobs[i]);
	Assigned_work *a;
	a=Assing_work(no_of_workers,m,jobs);
	output(m,a);
	free(a);
	return 0;
}