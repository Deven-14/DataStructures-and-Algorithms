#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
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
	Node *new_node=(Node*)create_node(data);
	new_node->next=s->top;//imp
	s->top=new_node;//imp
}
void pop(Stack *s)
{
	Node *temp=s->top;
	if(s->top==NULL)
	{
		printf("No elements in stack");
		return;
	}
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
	if(s.top==NULL){
		printf("Stack is empty\n");
		return 0;
	}
	return s.top->data;
}
char* input_string()
{
	char *s=(char*)malloc(50*sizeof(char));
	scanf("%s",s);
	s=realloc(s,strlen(s)+1);
	return s;
}
int isoperator(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':return 1;
		default:return 0;
	}
}
int performOperation(int op1,int op2,char c)
{
	switch(c)
	{
		case '+':
			return op1+op2;
		case '-':
			return op1-op2;
		case '*':
			return op1*op2;
		case '/':
			return op1/op2;
		case '^':
			return pow(op1,op2);
		default:
			return 0;
	}
}
int postfix_evaluation(char *s)//for preflix start the for loop from the last ele in string that's all
{
	int i,operand1,operand2,result,len=strlen(s);
	Stack *res=create_stack();
	for(i=0;i<len;i++)
	{
		if(isdigit(s[i]))
			push(res,(int)(s[i]-'0'));//so that it converts to num, 5 ascii 53, 0 ascii 48, so 53-48=5
		else if(isoperator(s[i]))
		{
			operand2=res->top->data;
			pop(res);
			operand1=res->top->data;
			pop(res);
			push(res,performOperation(operand1,operand2,s[i]));
		}
	}
	result=res->top->data;
	pop(res);
	free(s);
	s=NULL;
	return result;
}
void output(int result)
{
	printf("%d\n",result);
}
int main()
{
	char *s;
	int result;
	s=input_string();
	result=postfix_evaluation(s);
	output(result);
	free(s);
	return 0;
}
