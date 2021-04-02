#include <stdio.h>
#include <stdlib.h>

struct packet
{
	int arrival_time;
	int processing_time;
};
typedef struct packet Packet;

struct node
{
	int finish_time;
	struct node *next;
};
typedef struct node Node;
struct queue
{
	Node *front;
	Node *rear;
	int count;
};
typedef struct queue Queue;
Node* create_node(int finish_time)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->finish_time=finish_time;
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
void enQueue(Queue *q,int finish_time)
{
	Node *new_node=(Node*)create_node(finish_time);
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
	return q.front->finish_time;
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

int* network_packet_processing(int S,int n,Packet p[])
{
	if(n==0)
		return NULL;
	Queue *q=create_queue();
	int *result=(int*)malloc(n*sizeof(int));
	int i=0;
	while(i<n)
	{
		while(!isEmpty(*q) && p[i].arrival_time>=q->front->finish_time)
			deQueue(q);
	    if(q->count>=S)
			result[i]=-1;
		else if(!isEmpty(*q))
		{
			result[i]=q->rear->finish_time;
			enQueue(q,p[i].processing_time+q->rear->finish_time);
		}
		else//if empty
		{
			result[i]=p[i].arrival_time;
			enQueue(q,p[i].processing_time+p[i].arrival_time);
		}
	    i++;
	}
	free_queue(q);
	free(q);
	return result;
}

void output(int n,int *result)
{
	for(int i=0;i<n;i++)
		printf("%d\n",result[i]);
}

int main()
{
	int s,n;
	scanf("%d %d",&s,&n);
	Packet p[n];
	for(int i=0;i<n;i++)
		scanf("%d%d",&p[i].arrival_time,&p[i].processing_time);
	int *result;
	result=network_packet_processing(s,n,p);
	output(n,result);
	free(result);
	return 0;
}