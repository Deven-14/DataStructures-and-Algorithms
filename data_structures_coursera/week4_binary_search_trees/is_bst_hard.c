#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

extern Node* newNode(int data);
inline Node* newNode(int data)
{
	Node* n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->left=NULL;
	n->right=NULL;
	return n;
}

struct s_node
{
    Node *data;//node of the tree
    struct s_node *next;
};
typedef struct s_node s_Node;
struct stack
{
    s_Node *top;
};
typedef struct stack Stack;
extern s_Node* create_node(struct node* data);
inline s_Node* create_node(struct node* data)
{
    s_Node *n=malloc(sizeof(s_Node));
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
void push(Stack *s,Node* data)
{
    s_Node *new_node=create_node(data);
    new_node->next=s->top;//imp
    s->top=new_node;//imp
}
extern void pop(Stack *s);
inline void pop(Stack *s)
{
    s_Node *temp=s->top;
    if(s->top==NULL)
        return;
    s->top=s->top->next;
    free(temp);
}
extern int isEmpty(Stack s);
inline int isEmpty(Stack s)
{
    if(s.top==NULL)
        return 1;
    return 0;
}
extern Node* Top(Stack s);
inline Node* Top(Stack s)
{
    if(s.top==NULL)
        return NULL;
    return s.top->data;
}

struct treenodeData
{
	int key;
	int left;
	int right;
};
typedef struct treenodeData TreenodeData;

Node** make_nodes(int n, TreenodeData *t)
{
	Node **nodes=(Node**)malloc(n*sizeof(Node*));
	for(int i=0;i<n;++i)
		nodes[i]=newNode(t[i].key);
	return nodes;
}

Node* make_tree(int n,TreenodeData *t)
{
	if(n==0)
		return NULL;
	Node **nodes=make_nodes(n,t);
	Node *root=nodes[0];
	for(int i=0;i<n;++i)
	{
		if(t[i].left!=-1)
			nodes[i]->left=nodes[t[i].left];
		if(t[i].right!=-1)
			nodes[i]->right=nodes[t[i].right];
	}
	free(nodes);
	return root;
}

void postOrder_free(Node *root)
{
	if(root==NULL)
		return;
	Stack *s=create_stack();
	Node *curr=root;
	do{
		while(curr!=NULL)
		{
			if(curr->right)
				push(s,curr->right);
			push(s,curr);
			curr=curr->left;
		}
		curr=Top(*s);//use top func itself and s->top->data, coz, if there is no ele, then it'll return null
		pop(s);
		if(curr->right && curr->right==Top(*s))//use top func itself and s->top->data, coz, if there is no ele, then it'll return null*******************************************
		{
			pop(s);
			push(s,curr);
			curr=curr->right;
		}
		else
		{
			free(curr);
			curr=NULL;
		}
	}while(!isEmpty(*s));
	free(s);
}

/*int isBST(Node *root,int min,int max)
{
	if(root==NULL)//if it is null also, it is true...**************************************that node exists
		return 1;
	if(root->data>min && root->data<max && isBST(root->left,min,root->data) && isBST(root->right,root->data,max))
		return 1;
	return 0;
}*///normal version

/*
int isBST(Node *root,int min,int max)
{
	if(root==NULL)//if it is null also, it is true...**************************************that node exists
		return 1;
	if(root->data<min || root->data>max)
		return 0;
	return isBST(root->left,min,root->data-1) && isBST(root->right,root->data+1,max);//for distinct values -1 and +1
}*/

//hard version
/*int isBST(Node *root,int min,int max)//coz the element might be equal to INT_MAX OR INT_MIN ALSO(i had used long and long max and long min,********this is not working in this compiler but it is working in other compiler
{
	if(root==NULL)//if it is null also, it is true...**************************************that node exists
		return 1;
	if(root->data<min || root->data>max)
		return 0;
	return (isBST(root->left,min,root->data-1) && isBST(root->right,root->data,max));//only right can have duplicate, so only leftsubtrr root->data-1
}*///to allow duplication, we don't need -1 or +1, to remove duplication from left side, we have to -1 from max value, if any number is greater than root->data-1,i.e >=root->data then remove 

/*int isBST(Node *root,int min,int max)//coz the element might be equal to INT_MAX OR INT_MIN ALSO(i had used long and long max and long min,********this is not working in this compiler but it is working in other compiler
{
	if(root==NULL)//if it is null also, it is true...**************************************that node exists
		return 1;
	if(root->data>=min && root->data<=max && isBST(root->left,min,root->data-1) && isBST(root->right,root->data,max))
		return 1;
	return 0;
}*///first i allowed >=min and <=max, for duplication and so that even if they are INTMIN AND INT MAX they'll work and then to remove duplication on the left side, i subtracted -1 from the max value of the left subtree, i.e left subtree<=root->data-1

//U CAN USE INORDER TRAVERSAL ALSO*************************

//coz the element might be equal to INT_MAX OR INT_MIN ALSO(i had used long and long max and long min,********this is not working in this compiler but it is working in other compiler
//other methods it is that it fails a case in coursera
int isBST(Node *root,long min,long max)
{
	if(root==NULL)//if it is null also, it is true...**************************************that node exists
		return 1;
	if(root->data>=min && root->data<max && isBST(root->left,min,root->data) && isBST(root->right,root->data,max))
		return 1;
	return 0;
}//>=min to allow duplicate on right side

char* checkBst(Node *root)
{
	char *result=(char*)malloc(10*sizeof(char));
	if(isBST(root,LONG_MIN,LONG_MAX))
		strcpy(result,"CORRECT");
	else
		strcpy(result,"INCORRECT");
	return result;
}

int main()
{
	int n;
	scanf("%d",&n);
	TreenodeData *t=malloc(n*sizeof(TreenodeData));
	for(int i=0;i<n;++i)
	    scanf("%d%d%d",&t[i].key,&t[i].left,&t[i].right);
	Node *root=make_tree(n,t);
	free(t);
	char* result=checkBst(root);
	printf("%s\n",result);
	free(result);
	postOrder_free(root);
	return 0;
}