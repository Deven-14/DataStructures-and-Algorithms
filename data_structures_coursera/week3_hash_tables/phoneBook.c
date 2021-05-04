#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct query
{
	char *type;
	int number;
	char *name;
};
typedef struct query Query;

void input_queries(int n,Query *queries)
{
	for(int i=0;i<n;i++)
	{
		queries[i].type=(char*)malloc(5*sizeof(char));
		scanf("%s",queries[i].type);
		if(strcmp(queries[i].type,"add")==0)
		{
			queries[i].name=(char*)malloc(16*sizeof(char));
			scanf("%d %s",&queries[i].number,queries[i].name);
		}
		else
			scanf("%d",&queries[i].number);
	}
}

void free_Names(char **Name)
{
	for(int i=0;i<10000000;++i)
		if(Name[i]!=NULL)
			free(Name[i]);
}

char** processQueries(int n,Query *queries,int *result_size)
{
	char **Name;
	Name=(char**)malloc(10000000*sizeof(char*));
	for(int i=0;i<10000000;++i)
		Name[i]=NULL;
	int size=0;
	int capacity=1;
	char **result=(char**)malloc(capacity*sizeof(char*));
	for(int i=0;i<n;++i)
	{
		if(strcmp(queries[i].type,"add")==0)
		{
			char *temp=Name[queries[i].number];
			if(temp!=NULL)
				free(temp);//so that we don't need to free in queries
			Name[queries[i].number]=queries[i].name;
		}
		else if(strcmp(queries[i].type,"del")==0)
		{
			if(Name[queries[i].number]!=NULL)
			{
				free(Name[queries[i].number]);
				Name[queries[i].number]=NULL;
				queries[i].name=NULL;
			}
		}
		else
		{
			char *temp=Name[queries[i].number];
			if(temp!=NULL)
			{
				result[size]=(char*)malloc((strlen(temp)+1)*sizeof(char));
				strcpy(result[size++],temp);
			}
			else
			{
				result[size]=(char*)malloc(10*sizeof(char));
				strcpy(result[size++],"not found");
			}
			if(size==capacity)
			{
				capacity=2*size;
				result=(char**)realloc(result,capacity*sizeof(char*));
			}
		}
		free(queries[i].type);//************
	}
	free_Names(Name);
	free(Name);
	*result_size=size;
	return result;
}

void output_and_free(int n,char **result)
{
	for(int i=0;i<n;i++)
	{
		printf("%s\n",result[i]);
		free(result[i]);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	Query *queries;
	queries=(Query*)malloc(n*sizeof(Query));
	input_queries(n,queries);
	int result_size;
	char **result;
	result=processQueries(n,queries,&result_size);
	output_and_free(result_size,result);
	free(result);
	free(queries);
	return 0;
}