#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key;
	int ele;
	struct node *next;
};
typedef struct node Node;

Node* newNode(int key,int ele)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->key=key;
	n->ele=ele;
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

struct map
{
	int prime;
	long long a,b;//orelse int overflow, it'll not multily properly
	int m;
	int n;
	float lF;//load factor
	List **elements;
};
typedef struct map Map;

Map* newMap(int m)
{
	Map *mp=(Map*)malloc(sizeof(Map));
	mp->prime=1000000007;
	mp->a=rand()%(mp->prime-1)+1;//it has to be less than prime and greater than 0
	mp->b=rand()%mp->prime;
	mp->m=m;
	mp->n=0;
	mp->lF=(float)mp->n/mp->m;
	mp->elements=(List**)malloc(m*sizeof(List*));
	for(int i=0;i<m;++i)
		mp->elements[i]=newList();
	return mp;
}

extern inline long long hash_func(Map *mp,int key);
inline long long hash_func(Map *mp,int key)
{
	long long hash;
	hash=(mp->a*key+mp->b)%mp->prime;
	return hash%mp->m;
}

Node* find(Map *mp,int key)
{
	long long hash=hash_func(mp,key);
	List *l=mp->elements[hash];
	Node *n=l->head;
	while(n!=NULL && n->key!=key)
		n=n->next;
	return n;//if NULL it'll return null, or else itll return pointer to node
}

//Map* reHash(Map *mp)
void reHash(Map *mp)
{
	int old_m=mp->m;
	int new_m=old_m*2;
	Map *newM=newMap(new_m);
	List *lOld,*lNew;
	Node *n,*temp;
	long long hash;
	for(int i=0;i<old_m;++i)
	{
		lOld=mp->elements[i];
		n=lOld->head;
		while(n!=NULL)
		{
			temp=n;
			n=n->next;
			lOld->head=n;
			hash=hash_func(newM,temp->key);
			lNew=newM->elements[hash];
			temp->next=lNew->head;//insead of using newNode, i'm using the same node
			lNew->head=temp;
		}
		free(lOld);
	}
	free(mp->elements);
	//free(mp);
	//return newM;
	*mp=*newM;//struct values can be equated*********************that's y we don't need to return newM coz, we have passed mp as pointer
	free(newM);
}

//Map* insert(Map *mp,int key,int ele)
void insert(Map *mp,int key,int ele)
{
	long long hash=hash_func(mp,key);
	List *l=mp->elements[hash];
	Node *n=l->head;
	while(n!=NULL && n->key!=key)
		n=n->next;
	if(n)
		return;//return mp;
	n=newNode(key,ele);
	n->next=l->head;
	l->head=n;
	mp->lF=(float)mp->n/mp->m;
	if(mp->lF>0.75)
		reHash(mp);
		//mp=reHash(mp);
	//return mp;
}

void pop(Map *mp,int key)
{
	long long hash=hash_func(mp,key);
	List *l=mp->elements[hash];
	Node *n=l->head,*prev=NULL;
	while(n!=NULL && n->key!=key)
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

void free_map(Map *mp)
{
	List *l;
	Node *n,*temp;
	for(int i=0;i<mp->m;++i)
	{
		l=mp->elements[i];
		n=l->head;
		while(n!=NULL)
		{
			temp=n;
			n=n->next;
			free(temp);
		}
		free(l);
	}
	free(mp->elements);
}

int main()
{
	Map *mp=newMap(2);//change inline fucntions to #define
	int a[4]={1,25,100,226};
	/*mp=insert(mp,1,1);
	mp=insert(mp,25,25);
	mp=insert(mp,100,100);
	mp=insert(mp,226,226);*/
	insert(mp,1,1);
	insert(mp,25,25);
	insert(mp,100,100);
	insert(mp,226,226);
	Node* n;
	pop(mp,1);
	for(int i=0;i<4;++i)
		if((n=find(mp,a[i]))!=NULL)
			printf("%d %d\n",n->key,n->ele);
	free_map(mp);
	free(mp);
	return 0;
}