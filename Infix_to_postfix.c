#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
struct node
{
	char data;
	struct node *next;
};
typedef struct node Node;
struct stack
{
	Node *top;
};
typedef struct stack Stack;
Node* create_node(char data)
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
void push(Stack *s,char data)
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
char Top(Stack s)
{
	if(s.top==NULL){
		printf("Stack is empty\n");
		return 0;
	}
	return s.top->data;
}
char* input_infix()
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
int isOpeningParentheses(char c)
{
	switch(c)
	{
		case '(':
		case '[':
		case '{':return 1;
		default :return 0;
	}
}
int isClosingParentheses(char c)
{
	switch(c)
	{
		case ')':
		case ']':
		case '}':return 1;
		default :return 0;
	}
}
int getprecedencevalue(char operator)//greater the value greater is the precedence
{
	switch(operator)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default :
			return 0;
	}
}
int isRightAssociative(char operator)
{
	if(operator=='^')
		return 1;
	return 0;
}
int HasHigherPrecedence(char op1,char op2)
{
	int op1precedencevalue=getprecedencevalue(op1);//greater the value greater is the precedence
	int op2precedencevalue=getprecedencevalue(op2);
	if(op1precedencevalue==op2precedencevalue)
	{
		if(isRightAssociative(op1))// for ^, 3^2^3= 3^8 so it has to be 323^^ not 32^3^
			return 0;
		else
			return 1;
	}
	return op1precedencevalue>op2precedencevalue?1:0;
}
char* infixToPostfix(char *infix)
{
	int i,no_of_ele=0;
	char *postfix=(char*)malloc((strlen(infix)+1)*sizeof(char));
	Stack *s=create_stack();
	for(i=0;i<strlen(infix);i++)
	{
		if(isdigit(infix[i]) || isalpha(infix[i]))
			postfix[no_of_ele++]=infix[i];
		else if(isoperator(infix[i]))
		{
			while(!isEmpty(*s) && !isOpeningParentheses(s->top->data) && HasHigherPrecedence(s->top->data,infix[i]))
			{
				postfix[no_of_ele++]=s->top->data;
				pop(s);
			}
			push(s,infix[i]);
		}
		else if(isOpeningParentheses(infix[i]))
			push(s,infix[i]);
		else if(isClosingParentheses(infix[i]))
		{
			while(!isEmpty(*s) && !isOpeningParentheses(s->top->data))
			{
				postfix[no_of_ele++]=s->top->data;
				pop(s);
			}
			pop(s);//for the opening parentheses
		}
	}
	while(!isEmpty(*s))
	{
		postfix[no_of_ele++]=s->top->data;
		pop(s);
	}
	postfix[no_of_ele]='\0';
	postfix=realloc(postfix,(strlen(postfix)+1)*sizeof(char));
	free(s);
	s=NULL;
	return postfix;
}
void output(char *postfix)
{
	printf("%s\n",postfix);
}
int main(int argc, char **argv)
{
	//expecting input to be correct********************
	//for prefix to infix first reverse the input string with braces A+B*C so make it C*B+A then do postfix CB*A+ then reverse this +A*BC
	char *infix;
	infix=input_infix();
	char *postfix;
	postfix=infixToPostfix(infix);
	output(postfix);
	free(postfix);
	free(infix);
	return 0;
}
