#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
};
typedef struct node Node;
struct queue
{
	Node *front;//remove from front, i.e. dequeue
	Node *rear;//add to rear, i.e enqueue
	int count;
};
typedef struct queue Queue;
Node* create_node(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->next=NULL;
	return n;
}
Queue* create_queue()
{
	Queue *q=(Queue*)malloc(sizeof(Queue));
	q->front=NULL;
	q->rear=NULL;
	q->count=0;
	return q;
}
void enQueue(Queue *q,int data)
{
	Node *new_node=(Node*)create_node(data);
	if(q->front==NULL && q->rear==NULL)
	{
		q->front=q->rear=new_node;
		q->count++;
		return;
	}
	q->rear->next=new_node;
	q->rear=new_node;
	q->count++;
}
void deQueue(Queue *q)
{
	Node *temp=q->front;
	if(q->front==NULL)
		return;
	else if(q->front==q->rear)//vvvvimp ************** one element
		q->front=q->rear=NULL;
	else
		q->front=q->front->next;
	q->count--;
	free(temp);
}
int isEmpty(Queue q)
{
	if(q.front==NULL && q.rear==NULL)
		return 1;
	return 0;
}
int Front(Queue q)
{
	if(q.front==NULL)
		return 0;
	return q.front->data;
}
int size(Queue q)
{
	return q.count;
}
void print_queue(Queue q)
{
	Node *n=q.front;
	while(n!=NULL)
	{
		printf("%d ",n->data);
		n=n->next;
	}
	printf("\n");
}
void free_queue(Queue *q)
{
	Node *n,*temp;
	n=q->front;
	while(n!=NULL)
	{
		temp=n;
		n=n->next;
		free(temp);
	}
}
int main()
{
	Queue *q=create_queue();
	enQueue(q,5);
	print_queue(*q);
	enQueue(q,10);
	print_queue(*q);
	enQueue(q,15);
	print_queue(*q);
	deQueue(q);
	print_queue(*q);
	printf("%d\n",Front(*q));
	print_queue(*q);
	free_queue(q);
	free(q);
	return 0;
}
