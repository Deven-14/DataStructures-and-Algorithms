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

void print_Deque(Deque *dq)
{
	Node *n=dq->front;
	while(n!=NULL)
	{
		printf("%d,",n->data);
		n=n->next;
	}
	printf("\n");
}

int main()
{
	Deque *dq=create_Deque();
	insertFront(dq,1);
	insertRear(dq,2);
	print_Deque(dq);
	deleteFront(dq);
	print_Deque(dq);
	deleteRear(dq);
	print_Deque(dq);
	free_Deque(dq);
	free(dq);
	return 0;
}