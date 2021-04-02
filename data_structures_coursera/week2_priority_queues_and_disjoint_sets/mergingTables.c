#include <stdio.h>
#include <stdlib.h>

struct disjointSet
{
	int n_rows;
	int parent;
};
typedef struct disjointSet DisjointSet;

DisjointSet* create_disjointSets(int n,int *r)
{
	DisjointSet *tables=(DisjointSet*)malloc(n*sizeof(DisjointSet));
	for(int i=0;i<n;i++)
	{
		tables[i].n_rows=r[i];
		tables[i].parent=-1;
	}
	return tables;
}

int collapsingFind(DisjointSet *tables,int i)
{
	if(tables[i].parent<0)
		return i;
	tables[i].parent=collapsingFind(tables,tables[i].parent);
	return tables[i].parent;
}

int weitghtedUnion(DisjointSet *tables,int destination,int source)
{
	int realDestination=collapsingFind(tables,destination);
	int realSource=collapsingFind(tables,source);
	if(realDestination==realSource)
		return -1;
	int total=tables[realDestination].parent+tables[realSource].parent;
	if(tables[realDestination].parent>tables[realSource].parent)
	{
		tables[realDestination].parent=realSource;
		tables[realSource].parent=total;
		tables[realSource].n_rows+=tables[realDestination].n_rows;
		tables[realDestination].n_rows=0;
		return tables[realSource].n_rows;
	}
	else
	{
		tables[realSource].parent=realDestination;
		tables[realDestination].parent=total;
		tables[realDestination].n_rows+=tables[realSource].n_rows;
		tables[realSource].n_rows=0;
		return tables[realDestination].n_rows;
	}
}

int max(int n,int *r)
{
	int max=r[0];
	for(int i=1;i<n;i++)
		if(r[i]>max)
			max=r[i];
	return max;
}

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	int r[n];
	for(int i=0;i<n;i++)
		scanf("%d",&r[i]);
	DisjointSet *tables;
	tables=create_disjointSets(n,r);
	int max_table_size=max(n,r);
	int destination,source,new_table_size;
	for(int i=0;i<m;i++)
	{
		scanf("%d %d",&destination,&source);
		--destination;
		--source;
		new_table_size=weitghtedUnion(tables,destination,source);
		max_table_size=(max_table_size>new_table_size)?max_table_size:new_table_size;
		printf("%d\n",max_table_size);
	}
	free(tables);
	return 0;
}