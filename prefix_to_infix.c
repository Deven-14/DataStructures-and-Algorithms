//2017 7th problem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	char* data;
	struct node *next;
};
typedef struct node Node;
struct stack
{
	Node *top;
};
typedef struct stack Stack;
Node* create_node(char* data)
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
void push(Stack *s,char* data)
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
char* Top(Stack s)
{
	if(s.top==NULL){
		printf("Stack is empty\n");
		return 0;
	}
	return s.top->data;
}
int input_n()
{
	int n;
	scanf("%d",&n);
	return n;
}
void input_prefix(int n,char *all_prefix[n])
{
	for(int i=0;i<n;i++)
	{
		all_prefix[i]=(char*)malloc(50*sizeof(char));
		scanf(" %[^\n]s",all_prefix[i]);//make sure space is there before %
		all_prefix[i]=realloc(all_prefix[i],strlen(all_prefix[i])+1);
	}
}
int isoperator(char* c)
{
	if(strcmp(c,"+")==0 || strcmp(c,"-")==0 || strcmp(c,"*")==0 || strcmp(c,"/")==0)
		return 1;
	return 0;
}
int isOperand(char* c)
{
	if(!isoperator(c))
		return 1;
	return 0;
}
char** convertStrtoArrayofStr(char *str,int* n)//instead of this accept it in this manner i.e char***
{
	int i=0;
	char **s=(char**)malloc(sizeof(char*)),*token;//getting free() in char **prefix
	*s=(char*)malloc(50*sizeof(char));//coz this can expand coz we are doing op1+operator+op2
	token=strtok(str," ");
	strcpy(*(s+i),token);
	*s=realloc(*s,(strlen(*s)+1)*sizeof(char));
	i++;
	while((token=strtok(NULL," "))!=NULL)
	{
		s=realloc(s,(i+1)*sizeof(char*));
		*(s+i)=(char*)malloc(50*sizeof(char));
		strcpy(*(s+i),token);
		*(s+i)=realloc(*(s+i),(strlen(*(s+i))+1)*sizeof(char));
		i++;
	}
	*n=i;
	return s;
}
char* prefixToInfix(char** prefix,int n)
{
	Stack *s=create_stack();
	char *op1,*op2,temp[100],bracket[2],*result;
	result=malloc(100*sizeof(char));//it'll get free'd in 
	for(int i=n-1;i>=0;i--)
	{
		if(isOperand(prefix[i]))
			push(s,prefix[i]);
		else if(isoperator(prefix[i]))
		{
			op1=s->top->data;
			pop(s);
			op2=s->top->data;
			pop(s);
			strcpy(bracket,"(");
			strcpy(temp,bracket);//make sure strcpy coz before value of temp is getting attached otherwise
			strcat(temp,op1);//no including spaces, if spaces needed then strcat that also
			strcat(temp,prefix[i]);
			strcat(temp,op2);
			strcpy(bracket,")");
			strcat(temp,bracket);
			prefix[i]=realloc(prefix[i],(strlen(temp)+1)*sizeof(char));
			strcpy(prefix[i],temp);//coz this should reamin in the stack, temp will keep changing
			push(s,prefix[i]);
		}
	}
	strcpy(result,s->top->data);
	pop(s);
	free(s);
	s=NULL;
	return result;
}
void free_arrayofstring(int n,char *a[]);
void prefixToInfix_of_all(int n,char* all_prefix[],char* all_infix[])// they asked us to do 2 + 15 + 5
{
	char **prefix,*temp;
	int no_of_ele;
	for(int i=0;i<n;i++)
	{
		temp=malloc(strlen(all_prefix[i])+1);
		strcpy(temp,all_prefix[i]);//coz i don't wanted to change input string
		prefix=convertStrtoArrayofStr(temp,&no_of_ele);
		all_infix[i]=prefixToInfix(prefix,no_of_ele);
		free_arrayofstring(no_of_ele,prefix);//it has array of pointers in heap
		free(prefix);
		free(temp);
	}
}
void output(int n,char* all_infix[])
{
	for(int i=0;i<n;i++)
		printf("%s\n",all_infix[i]);
}
void free_arrayofstring(int n,char *a[])
{
	for(int i=0;i<n;i++)
		free(a[i]);
}
int main()
{//make sure to give space while giving input, for postfix just do it from i=0
	int n;
	n=input_n();
	char *all_prefix[n];
	input_prefix(n,all_prefix);
	char *all_infix[n];
	prefixToInfix_of_all(n,all_prefix,all_infix);
	output(n,all_infix);
	free_arrayofstring(n,all_prefix);
	free_arrayofstring(n,all_infix);
	return 0;
}
