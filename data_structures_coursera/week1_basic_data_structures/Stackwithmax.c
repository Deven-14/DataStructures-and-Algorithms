#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		return -1;
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

/*int findMax(Stack *s)
{
    Node *n=s->top;
    if(s->top==NULL)
        return 0;
    int max=n->data;
    while(n!=NULL)
    {
        if(n->data>max)
            max=n->data;
        n=n->next;
    }
    return max;
}*/

void solveQueries(int q)
{
	Stack *s=create_stack();
	Stack *maxS=create_stack();
	char type[5];
	int data;
	while(q--)
	{
		scanf("%s",type);
		if(strcmp(type,"push")==0)
		{
			scanf("%d",&data);
			push(s,data);
			if(isEmpty(*maxS))
				push(maxS,data);
			else
				push(maxS,(data>Top(*maxS))?data:Top(*maxS));
		}
		else if(strcmp(type,"pop")==0)
		{
			pop(s);
			pop(maxS);
		}
		else
			printf("%d\n",Top(*maxS));
	}
	free_stack(s);
	free_stack(maxS);
	free(s);
	free(maxS);
}

int main()
{
	int q;
	scanf("%d",&q);
	solveQueries(q);
	return 0;
}