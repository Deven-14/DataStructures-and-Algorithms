#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *prev,*next;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->prev=NULL;
	n->next=NULL;
	return n;
}

struct deque
{
	Node *front;
	Node *rear;
	int count;
};
typedef struct deque Deque;

Deque* create_Deque()
{
	Deque *dq=(Deque*)malloc(sizeof(Deque));
	dq->count=0;
	dq->front=NULL;
	dq->rear=NULL;
	return dq;
}

int isEmpty(Deque *dq)
{
	if(dq->front==NULL)
		return 1;
	return 0;
}

int size(Deque *dq)
{
	return dq->count;
}

void insertFront(Deque *dq,int data)
{
	Node *new_node=newNode(data);
	if(dq->front==NULL)
		dq->front=dq->rear=new_node;
	else
	{
		new_node->next=dq->front;
		dq->front->prev=new_node;
		dq->front=new_node;
	}
	dq->count++;
}

void insertRear(Deque *dq,int data)
{
	Node *new_node=newNode(data);
	if(dq->front==NULL)
		dq->front=dq->rear=new_node;
	else
	{
		dq->rear->next=new_node;
		new_node->prev=dq->rear;
		dq->rear=new_node;
	}
	dq->count++;
}

void deleteFront(Deque *dq)
{
	if(dq->front==NULL)
		return;
	Node *temp=dq->front;
	dq->front=dq->front->next;
	if(dq->front==NULL)
		dq->rear=NULL;
	else
		dq->front->prev=NULL;
	free(temp);
	dq->count--;
}

void deleteRear(Deque *dq)
{
	if(dq->front==NULL)
		return;
	Node *temp=dq->rear;
	dq->rear=dq->rear->prev;
	if(dq->rear==NULL)
		dq->front=NULL;
	else
		dq->rear->next=NULL;
	free(temp);
	dq->count--;
}

int getFront(Deque *dq)
{
	if(dq->front==NULL)
		return -1;
	return dq->front->data;
}

int getRear(Deque *dq)
{
	if(dq->front==NULL)
		return -1;
	return dq->rear->data;
}

void free_Deque(Deque *dq)
{
	Node *n=dq->front,*temp;
	while(n!=NULL)
	{
		temp=n;
		n=n->next;
		free(temp);
	}
}

int* max_in_sliding_window(int n,int *a,int m)
{
	Deque *dq=create_Deque();
	int *max=(int*)malloc((n-m+1)*sizeof(int));
	int n_max=0;
	int i;
	for(i=0;i<m;++i)
	{
		while(!isEmpty(dq) && a[i]>=a[dq->rear->data])
			deleteRear(dq);
		insertRear(dq,i);
	}
	max[n_max++]=a[dq->front->data];
	for(i=m;i<n;++i)
	{
		if(i-m==dq->front->data)//removing i-m th ele if present
			deleteFront(dq);
		while(!isEmpty(dq) && a[i]>=a[dq->rear->data])
			deleteRear(dq);
		insertRear(dq,i);
		max[n_max++]=a[dq->front->data];
	}
	free_Deque(dq);
	free(dq);
	return max;
}

void output(int m,int *max)
{
	for(int i=0;i<m;i++)
		printf("%d ",max[i]);
}

int main()
{
	int n,m;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	int *max;
	max=max_in_sliding_window(n,a,m);
	output(n-m+1,max);
	free(max);
	return 0;
}