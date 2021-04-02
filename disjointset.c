#include <stdio.h>
#include <stdlib.h>
struct disjointset
{
	int n;
	int *parent;
};
typedef struct disjointset DisjointSet;
/*typedef struct set
{
	int parent;
	int rank;
}Set;*///better to use this i.e Set[n];***********************************************************************
/*void makeset(DisjointSet *d,int i)//if making for singal ele, with rank
{
	d->parent[i]=i;
	d->rank[i]=0;
}*/
void makeAllSets(DisjointSet d)//without rank(without union of rank) instead weighted union and collapsing find is used
{
	for(int i=0;i<d.n;i++)
	{
		d.parent[i]=-1;//parent of each ele is itself
	}
}
/*int find(DisjointSet d,int i)//for only weightedUnion without path compression
{
	while(parent[i]>0)
		i=parent[i];
	return i;
}*/
int collapsingFind(DisjointSet d,int i)
{
	if(d.parent[i]<0)
		return i;
	d.parent[i]=collapsingFind(d,d.parent[i]);
	return d.parent[i];
	/*
	int i_id=i;
	while(d.parent[i_id]>0)//can use a stack if no of elements get too many***************
		i_id=d.parent[i_id];
	while(i!=i_id)
	{
		int next=d.parent[i];
		d.parent[i]=i_id;
		i=next;
	}
	*/
}
/*
void union(DisjointSet d,int i,int j)//with rank(with union of rank and not weightedunion)
{
	int i_id=collapsingFind(d,i);
	int j_id=collapsingFind(d,j);
	if(i_id==j_id)
		return;
	if(d.rank[i_id]>d.rank[j_id])
		parent[j_id]=i_id;
	else{
		parent[i_id]=j_id;
		if(d.rank[i_id]==d.rank[j_id])
			d.rank[j_id]+=1;
	}
}*/
void weightedUnion(DisjointSet d,int i,int j)//in weighted union we don't need rank, coz we store the no of nodes in the id/root with a negative sign
{
	int i_id=collapsingFind(d,i);
	int j_id=collapsingFind(d,j);
	if(i_id==j_id)
		return;
	int temp=d.parent[i_id]+d.parent[j_id];//both negative, indicating no of nodes
	if(d.parent[i_id]>d.parent[j_id]){
		d.parent[i_id]=j_id;//coz parent[i/j_id] is negative
		d.parent[j_id]=temp;
	}
	else{
		d.parent[j_id]=i_id;
		d.parent[i_id]=temp;
	}
}
int main()
{
	DisjointSet d;
	d.n=5;
	d.parent=(int*)malloc(d.n*sizeof(int));
	makeAllSets(d);
	weightedUnion(d,0,1);
	weightedUnion(d,1,2);
	weightedUnion(d,3,4);
	for(int i=0;i<5;i++)
		printf("%d,",d.parent[i]);
	free(d.parent);
	return 0;
}