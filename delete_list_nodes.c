#include<stdio.h>
#include<limits.h> //INT_MIN AND INT_MAX
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
}
void print_list(List *);
void input_list(List *l)
{
	int a,b,i=0;
	printf("Enter the no of ele(>=1):\n");
	scanf("%d",&a);
	for(i=0;i<a;i++)
	{
	    printf("Enter the %d element\n",i+1);
		scanf("%d",&b);
		add_tail(l,b);
	}
	print_list(l);
}
int pop_head(List *l)//remove the first element of the list
{
	int data=0;//for void it'll be null
	if(l->head)//empty list
	{
		Node *temp=l->head;
		if(l->head->next)//for 1 element
			l->head=l->head->next;
		else
		{
			l->head=NULL;
			l->tail=NULL;
		}
		data=temp->data;
		free(temp);
		l->count--;
		return data;
		//if(l->count==1)
			//l->tail=l->head;
	}
	return INT_MIN;
}
int pop_tail(List *l)
{
	int data=0;
	if(l->tail)
	{
		Node *current=l->head,*prev=NULL;
		while(current->next!=NULL)//to find last and it's previous node
		{
			prev=current;
			current=current->next;
		}
		data=current->data;
		free(current);
		l->tail=prev;//setting the prev ele to l->last*************************
		if(prev)
		{
			prev->next=NULL;//*****because needed while printing...prev->next=NULL or current=NULL;
		}
		else
		{
			l->head=NULL;//no ele
			l->tail=NULL;
		}
		l->count--;
		return data;
	}
	return INT_MIN;
}
void pop_specfic_val(List *l,int val)
{
	Node *current=l->head,*prev=NULL;
	while(current!=NULL && current->data!=val)//current!=NULL because we have to check for head also
	{
		prev=current;
		current=current->next;
	}
	if(current==NULL)
	{
		printf("This value doesn't exist in the list\n");
		return;
	}
	l->count--;
	if(current==l->head)
		l->head=current->next;
	else
		prev->next=current->next;
	free(current);
}
void pop_by_index(List *l,int ind)
{
	Node *current=l->head,*prev=NULL;
	for(int i=0;current!=NULL && i<ind;i++)//i<ind ***************prev will be the previous one and current will be the element
	{
		prev=current;
		current=current->next;
	}
	if(current==NULL)//for index greater than no of elements AND FOR NO ELEMENTS....
	{
		printf("wrong index\n");
		return;
	}
	l->count--;
	if(ind==0)
		l->head=current->next;
	else
		prev->next=current->next;
	free(current);
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
	input_list(l);
	printf(" %d is popped from the list\n",pop_head(l));
	printf(" %d is popped from the list\n",pop_tail(l));
	int a,b;
	printf("enter an element to be popped:\n");
	scanf("%d",&a);
	pop_specfic_val(l,a);
	printf("enter an index to be popped:\n");
	scanf("%d",&b);
	pop_by_index(l,b);
	print_list(l);
	output_count(l->count);
	list_delete(l);
	return 0;
}
