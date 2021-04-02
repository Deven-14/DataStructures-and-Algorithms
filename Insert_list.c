#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
}Node;
typedef struct list
{
	Node *head;
	Node *tail;
	unsigned int count;
}List;
Node* create_node(int val)
{
	Node *n=NULL;
	n=(Node*)malloc(sizeof(Node));
	if(n)
	{
		n->data=val;
		n->next=NULL;
	}
	return n;
}
List* create_list()
{
	List *l=NULL;
	l=(List*)malloc(sizeof(List));
	if(l)//checking if the memory is allocated or not
	{
		l->head=NULL;
		l->tail=NULL;
		l->count=0;
	}
	return l;
}
void print_list(List *l);
void add_head(List *l,int val)//insert a node in the begining of the list
{
	Node *new_n=create_node(val);
	if(l->tail==NULL)//first node
	{
		l->head=new_n;
		l->tail=new_n;
	}
	else
	{
		new_n->next=l->head;//putting the address of the head to the new node next pointer
		l->head=new_n;//making the new node the head
	}
	l->count++;
	print_list(l);
}
void add_tail(List *l,int val)//insert a node at the end of the list
{
	Node *new_n=create_node(val);
	if(l->tail==NULL)//first node
	{
		l->head=new_n;
		l->tail=new_n;
	}
	else
	{
		l->tail->next=new_n;//adding new node at the end
		l->tail=new_n;//making the new last node the tail
	}
	l->count++;
	print_list(l);
}
void insertafter_specfic_node(List *l,Node *n,int val)//inserting after a particular node 'n'
{
	if(n==NULL)
	{
		printf("The previous node cannot be NULL\n");
		return;
	}
	Node *new_n=create_node(val);
	new_n->next=n->next;
	n->next=new_n;
	if(l->tail==n)
		l->tail=new_n;
	l->count++;
}
void insert_at_specfic_index(List *l,int ind,int val)
{
	int i;
	Node *current=l->head;
	if(ind==0)
	{
		add_head(l,val);
		return;
	}
	for(i=0;i<(ind-1) && current!=NULL;i++)
		current=current->next;
	if(current==NULL && i<(ind-1))
	{
		printf("index %d doesn't exist hence cannot put in index %d\n",i,ind);
		print_list(l);
		return;
	}
	insertafter_specfic_node(l,current,val);
	print_list(l);
}
void print_list(List *l)
{
    Node *n=l->head;
	printf("The linked list is:");
	while(n!=NULL)
	{
		printf("%d ",n->data);
		n=n->next;
	}
	printf("\n");
}
void output_count(int c)
{
	printf("The number of elements in the linked list is =%d\n",c);
}
void list_empty(List *l)
{
	Node *n,*temp;
	n=l->head;
	while(n!=NULL)
	{
		temp=n;
		n=n->next;
		free(temp);
	}
}
void list_delete(List *l)
{
	if(l)
	{
		list_empty(l);
		free(l);
	}
}
int main()
{
	List *l=create_list();
	printf("10 is pushed in the list at the end\n");
	add_tail(l,10);
	printf("20 is pushed in the list at the begining\n");
	add_head(l,20);
	printf("30 is pushed in the list at the begining\n");
	add_head(l,30);
	printf("40 is pushed in the list after 2nd position\n");
	insertafter_specfic_node(l,l->head->next,40);
	print_list(l);
	int a,b;
	printf("enter an index and val to be inserted:\n");
	scanf("%d%d",&a,&b);
	insert_at_specfic_index(l,a,b);
	output_count(l->count);
	list_delete(l);
	return 0;
}