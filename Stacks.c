#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
};
typedef struct node Node;
struct stack
{
	Node *top;
};
typedef struct stack Stack;
Node* create_node(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->next=NULL;
	return n;
}
Stack* create_stack()
{
	Stack *s=(Stack*)malloc(sizeof(Stack));
	s->top=NULL;
	return s;
}
void push(Stack *s,int data)
{
	Node *new_node=create_node(data);
	new_node->next=s->top;//imp
	s->top=new_node;//imp
}
void pop(Stack *s)
{
	Node *temp=s->top;
	if(s->top==NULL)
		return;
	s->top=s->top->next;
	free(temp);
}
int isEmpty(Stack s)
{
	if(s.top==NULL)
		return 1;
	return 0;
}
int Top(Stack s)
{
	if(s.top==NULL)
		return 0;
	return s.top->data;
}
void free_stack(Stack *s)
{
	Node *n,*temp;
	n=s->top;
	while(n!=NULL)
	{
		temp=n;
		n=n->next;
		free(temp);
	}
}
void print_stack(Stack s)
{
	Node *n=s.top;
	while(n!=NULL)
	{
		printf("%d ",n->data);
		n=n->next;
	}
	printf("\n");
}
int main()
{
	Stack *s=create_stack();
	push(s,5);
	print_stack(*s);
	push(s,10);
	print_stack(*s);
	push(s,15);
	print_stack(*s);
	pop(s);
	print_stack(*s);
	printf("%d\n",Top(*s));
	free_stack(s);
	free(s);
	return 0;
}
