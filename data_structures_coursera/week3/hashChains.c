#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
	char *s;
	struct node *next;
};
typedef struct node Node;

Node* newNode(char *s)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->s=s;
	n->next=NULL;
	return n;
}

struct list
{
	Node *head;
};
typedef struct list List;

List* newList()
{
	List *l=(List*)malloc(sizeof(List));
	l->head=NULL;
	return l;
}

bool find(List *l,char *s)
{
	Node *n=l->head;
	while(n!=NULL && strcmp(n->s,s)!=0)
		n=n->next;
	if(n==NULL)
		return false;
	return true;
}

void add(List *l,char *s)
{
	if(find(l,s))
		return;
	Node *n=newNode(s);
	n->next=l->head;
	l->head=n;
}

void pop(List *l,char *s)
{
	Node *n=l->head,*prev=NULL;
	while(n!=NULL && strcmp(n->s,s)!=0)
	{
	    prev=n;
	    n=n->next;
	}
	if(n==NULL)
	    return;
	if(n==l->head)
	    l->head=l->head->next;
	else
        prev->next=n->next;
	free(n);
}

struct query
{
	char *type;
	char *s;
	int index;
};
typedef struct query Query;

void input_queries(int n,Query *queries)
{
	for(int i=0;i<n;++i)
	{
		queries[i].type=(char*)malloc(6*sizeof(char));
		scanf("%s",queries[i].type);
		if(strcmp(queries[i].type,"check")!=0)
		{
			queries[i].s=(char*)malloc(16*sizeof(char));
			scanf("%s",queries[i].s);
		}
		else
			scanf("%d",&queries[i].index);
	}
}

size_t hash_func(int bucket_count,char *s)
{
	unsigned int prime=1000000007;
	unsigned int multiplier=263;
	int len=strlen(s);
	unsigned long long hash=0;
	for(int i=len-1;i>=0;--i)
		hash=(hash*multiplier+s[i])%prime;
	hash=hash%bucket_count;
	return hash;
}

void free_elements(int m,List **elements)
{
	for(int i=0;i<m;i++)
	{
		Node *n=elements[i]->head;
		while(n!=NULL)
		{
			Node *temp=n;
			n=n->next;
			free(temp);
		}
		free(elements[i]);
	}
}

char** processQueries(int m,int n,Query *queries,int *result_size)
{
	List **elements=NULL;
	elements=(List**)malloc(m*sizeof(List*));
	for(int i=0;i<m;i++)
		elements[i]=newList();
	char **result;
	int size=0;
	int capacity=1;
	result=(char**)malloc(capacity*sizeof(char*));
	unsigned long long hash;
	for(int i=0;i<n;i++)
	{
		if(strcmp(queries[i].type,"add")==0)
		{
		    hash=hash_func(m,queries[i].s);
			add(elements[hash],queries[i].s);//maybe create a empty list for all the elements
		}
		else if(strcmp(queries[i].type,"del")==0)
		{
		    hash=hash_func(m,queries[i].s);
			pop(elements[hash],queries[i].s);
		}
		else if(strcmp(queries[i].type,"find")==0)
		{
		    hash=hash_func(m,queries[i].s);
			result[size]=malloc(4*sizeof(char));
			if(find(elements[hash],queries[i].s))
				strcpy(result[size++],"yes");
			else
				strcpy(result[size++],"no");
			if(size==capacity)
			{
				capacity=2*size;
				result=(char**)realloc(result,capacity*sizeof(char*));
			}
		}
		else
		{
			if(elements[queries[i].index]->head)
			{
				Node *n=elements[queries[i].index]->head;
				int len=0;
				len=strlen(n->s);
				len++;//**********************
				result[size]=(char*)malloc(len*sizeof(char));//don't do len+1, coz next we are doing len+=strlen(s), so in the before line do len++
				strcpy(result[size],n->s);//we can't use str cat directly
				n=n->next;
				while(n!=NULL)
				{
					len+=strlen(n->s);
					len++;//********************for all the next words this +1 should be there
					result[size]=(char*)realloc(result[size],len*sizeof(char));//len+1 coz and not len+2,\0 is already there
					strcat(result[size]," ");
					strcat(result[size],n->s);
					n=n->next;
				}
				size++;
				if(size==capacity)
				{
					capacity=2*size;
					result=(char**)realloc(result,capacity*sizeof(char*));
				}
			}
			else
			{
				result[size]=(char*)malloc(sizeof(char));
				result[size++][0]='\0';
				if(size==capacity)
				{
					capacity=2*size;
					result=(char**)realloc(result,capacity*sizeof(char*));
				}
			}
		}
	}
	free_elements(m,elements);
	free(elements);
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

void free_queries(int n,Query *queries)
{
	for(int i=0;i<n;i++)
	{
		if(strcmp(queries[i].type,"check")!=0)
			free(queries[i].s);
		free(queries[i].type);
	}
}

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	Query *queries;
	queries=(Query*)malloc(n*sizeof(Query));
	input_queries(n,queries);
	int result_size;
	char **result;
	result=processQueries(m,n,queries,&result_size);
	output_and_free(result_size,result);
	free_queries(n,queries);
	free(queries);
	free(result);
	return 0;
}