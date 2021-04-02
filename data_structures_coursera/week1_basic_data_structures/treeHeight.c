#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	int n;
	struct node **child;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->n=0;
	n->child=NULL;
	return n;
}

struct qnode
{
    Node *data;
    struct qnode *next;
};
typedef struct qnode qNode;
struct queue
{
    qNode *front;//remove from front, i.e. dequeue
    qNode *rear;//add to rear, i.e enqueue
	int count;
};
typedef struct queue Queue;
qNode* create_node(Node *data)
{
    qNode *n=(qNode*)malloc(sizeof(qNode));
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
void enQueue(Queue *q,Node *data)
{
    qNode *new_node=(qNode*)create_node(data);
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
    qNode *temp=q->front;
    if(q->front==NULL)
        return;
    else if(q->front==q->rear)//vvvvimp ************** one element
        q->front=q->rear=NULL;
    else
        q->front=q->front->next;
    free(temp);
	q->count--;
}
int isEmpty(Queue q)
{
    if(q.front==NULL && q.rear==NULL)
        return 1;
    return 0;
}
struct node* Front(Queue q)
{
    if(q.front==NULL)
        return 0;
    return q.front->data;
}

void create_nodes(int n,Node *nodes[])
{
	for(int i=0;i<n;i++)//here the search operation for nodes is O(1), instead of search() function which takes O(h), we can do this coz the data value ranges from 0 to n-1
		nodes[i]=newNode(i);
}

Node* create_tree(int n,Node *nodes[])
{
	int parent_index;
	Node *temp,*root=NULL;
	for(int child_index=0;child_index<n;child_index++)
	{
		scanf("%d",&parent_index);
		//adding child
		if(parent_index==-1)
			root=nodes[child_index];
		else{
			temp=nodes[parent_index];
			temp->n++;
			temp->child=realloc(temp->child,temp->n*sizeof(Node));
			temp->child[temp->n-1]=nodes[child_index];
		}
	}
	return root;
}

int CalulatingHeight(Node *root)
{
	if(root==NULL)
		return 0;
	Queue *q=create_queue();
	enQueue(q,root);
	int height=0;
	while(!isEmpty(*q))
	{
		int nodecount=q->count;
		height++;
		while(nodecount>0)
		{
			Node *temp=Front(*q);
			deQueue(q);
			for(int i=0;i<temp->n;i++)
				enQueue(q,temp->child[i]);
			nodecount--;
		}
	}
	free(q);
	return height;
}

void free_tree(int n,Node *nodes[])
{
	for(int i=0;i<n;i++)
	{
		free(nodes[i]->child);//********************************
		free(nodes[i]);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	Node *nodes[n];
	Node *root;
	create_nodes(n,nodes);
	root=create_tree(n,nodes);
	int h=CalulatingHeight(root);
	printf("%d",h);
	free_tree(n,nodes);
	return 0;
}