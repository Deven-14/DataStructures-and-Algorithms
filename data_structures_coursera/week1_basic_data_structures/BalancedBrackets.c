#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char data;
	int index;
	struct node *next;
};
typedef struct node Node;
struct stack
{
	Node *top;
};
typedef struct stack Stack;
Node* create_node(char data,int index)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->index=index;
	n->next=NULL;
	return n;
}
Stack* create_stack()
{
	Stack *s=(Stack*)malloc(sizeof(Stack));
	s->top=NULL;
	return s;
}
void push(Stack *s,char data,int index)
{
	Node *new_node=create_node(data,index);
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
char Top(Stack s)
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

int isOpeningParentheses(char c)
{
	switch(c)
	{
		case '{':
		case '[':
		case '(':return 1;
		default:return 0;
	}
}

int isClosingParentheses(char c)
{
	switch(c)
	{
		case '}':
		case ']':
		case ')':return 1;
		default:return 0;
	}
}

int ArePairs(char c1,char c2)
{
	switch(c1)
	{
		case '{':return (c2=='}');
		case '[':return (c2==']');
		case '(':return (c2==')');
		default:return 0;
	}
}

int BalancedBrackets(char *str)
{
	Stack *s=create_stack();
	int len=strlen(str);
	for(int i=0;i<len;i++)
	{
		if(isOpeningParentheses(str[i]))
			push(s,str[i],i+1);
		else if(isClosingParentheses(str[i]))
		{
			if(!isEmpty(*s) && ArePairs(s->top->data,str[i]))
				pop(s);
			else
				return i+1;
		}
	}
	if(isEmpty(*s))
	{
		free(s);
		return len+1;
	}
	int index=s->top->index;
	free_stack(s);
	free(s);
	return index;
}

void output(int index,int len)
{
	if(index==len+1)
		printf("Success");
	else
		printf("%d",index);
}

int main()
{
	char *str=(char*)malloc(100000*sizeof(char));
	scanf("%s",str);
	str=realloc(str,(strlen(str)+1)*sizeof(char));
	int result=BalancedBrackets(str);
	output(result,strlen(str));
	free(str);
	return 0;
}