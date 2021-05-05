#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node* newNode(int data)
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

s_Node* create_node(struct node* data)
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

Node** make_nodes(int n, TreenodeData t[])
{
	Node **nodes=(Node**)malloc(n*sizeof(Node*));
	for(int i=0;i<n;++i)
		nodes[i]=newNode(t[i].key);
	return nodes;
}

Node* make_tree(int n,TreenodeData t[])
{
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

void inOrder(Node *root)
{
	if(root==NULL)
		return;
	Stack *s=create_stack();
	Node *curr=root;
	while(!isEmpty(*s) || curr!=NULL)//this curr!=null is needed for first entry and then when there is only ele in stack, it is poped and put that value in curr, curr value is printed and then moved to it's right node, so there are nodes to be printed yet but the stack is empty, so this condition is imp
	{
		while(curr!=NULL)
		{
			push(s,curr);
			curr=curr->left;
		}
		curr=Top(*s);//use top func itself and s->top->data, coz, if there is no ele, then it'll return null
		pop(s);
		printf("%d ",curr->data);
		curr=curr->right;//use top func itself and s->top->data, coz, if there is no ele, then it'll return null, here u can use s->top->data,coz it'll not be empty
	}
	printf("\n");
	free(s);
}

void preOrder(Node *root)
{
	if(root==NULL)
		return;
	Stack *s=create_stack();
	Node *curr=root;
	while(!isEmpty(*s) || curr!=NULL)//this curr!=null is imp, coz if there is only one ele in stack and it is popped and put to curr, then stack is empty but there is still a node to be printed and go ahead from
	{
		while(curr!=NULL)
		{
			printf("%d ",curr->data);
			if(curr->right)
				push(s,curr->right);
			curr=curr->left;
		}
		if(!isEmpty(*s))
		{
			curr=Top(*s);//use top func itself and s->top->data, coz, if there is no ele, then it'll return null
			pop(s);
		}
	}
	printf("\n");
	free(s);
}

void preOrder2(Node *root)
{
	if(root == NULL)
		return;
	Stack *s = create_stack();
	push(s, root);
	Node *curr;
	while(!isEmpty(*s))
	{
		curr = Top(*s);
		pop(s);
		printf("%d ", curr->data);
		if(curr->right)
			push(s, curr->right);
		if(curr->left)
			push(s, curr->left);
	}
	free(s);
}

void postOrder(Node *root)
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
		if(curr->right && curr->right==Top(*s))//use top func itself and s->top->data, coz, if there is no ele, then it'll return null
		{
			pop(s);
			push(s,curr);
			curr=curr->right;
		}
		else
		{
			printf("%d ",curr->data);
			curr=NULL;
		}
	}while(!isEmpty(*s));
	free(s);
	printf("\n");
}

void postOrder2(Node *root)
{
	if(root == NULL)
		return;
	Stack *s1 = create_stack();
	Stack *s2 = create_stack();
	push(s1, root);
	Node *curr;
	while(!isEmpty(*s1))
	{
		curr = Top(*s1);
		pop(s1);
		push(s2, curr);
		if(curr->left)
			push(s1, curr->left);
		if(curr->right)
			push(s1, curr->right);
	}
	while(!isEmpty(*s2))
	{
		curr = Top(*s2);
		printf("%d ", curr->data);
		pop(s2);
	}
	free(s1);
	free(s2);
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

int main()
{
	int n;
	scanf("%d",&n);
	TreenodeData t[n];
	for(int i=0;i<n;++i)
	    scanf("%d%d%d",&t[i].key,&t[i].left,&t[i].right);
	Node *root=make_tree(n,t);
	inOrder(root);
	preOrder(root);
	//preOrder2(root);
	postOrder(root);
	//postOrder2(root);
	postOrder_free(root);
	return 0;
}