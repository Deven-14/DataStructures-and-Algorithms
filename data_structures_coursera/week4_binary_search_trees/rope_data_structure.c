#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct node
{
	char ch;
	struct node *left;
	struct node *right;
	int NoOfNodes;
};
typedef struct node Node;

Node* newNode(char ch)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->ch=ch;
	n->left=NULL;
	n->right=NULL;
	n->NoOfNodes=1;//one coz, we have this node in the begining 
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



extern int calNoOfNodes(Node *l,Node *r);
inline int calNoOfNodes(Node *l,Node *r)
{
	int n=0;
	if(l)
		n+=l->NoOfNodes;
	if(r)
		n+=r->NoOfNodes;
	return n;
}

Node* leftRotate(Node *root)
{
	Node *lnode=root;
	root=root->right;
	lnode->right=root->left;
	root->left=lnode;
	lnode->NoOfNodes=calNoOfNodes(lnode->left,lnode->right)+1;//don't do lnode->NoOfNodes+=coz in lnode we might have removed it's left node and the NoOfNodes value will be higher then adding will make it even higher, not just for this node, for all
	root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
	return root;
}

Node* rightRotate(Node *root)//not inine coz we are calling another inline function inside this
{
	Node *rnode=root;
	root=root->left;
	rnode->left=root->right;
	root->right=rnode;
	rnode->NoOfNodes=calNoOfNodes(rnode->left,rnode->right)+1;
	root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
	return root;
}

//zig-left, zag-right
Node* Splay(Node *root,int index)
{
	if(root==NULL)
		return root;
	int pos=((root->left==NULL)?0:root->left->NoOfNodes)+1;
	if(pos==index+1)
		return root;
	if(index+1<pos)
	{
		if(root->left==NULL)
			return root;//*********************no node available to rotate, so return root
		pos=((root->left->left==NULL)?0:root->left->left->NoOfNodes)+1;
		if(index+1<pos)//zig zig
		{
			root->left->left=Splay(root->left->left,index);
			root=rightRotate(root);//coz root exists we don't need to check
		}
		else if(index+1>pos)//zig zag
		{
			root->left->right=Splay(root->left->right,index-pos);
			if(root->left->right!=NULL)
				root->left=leftRotate(root->left);
		}
		return (root->left==NULL)?root:rightRotate(root);
	}
	else //key>root->data
	{
		index-=pos;
		if(root->right==NULL)
			return root;//*************no node available to rotate, so return root
		pos=((root->right->left==NULL)?0:root->right->left->NoOfNodes)+1;
		if(index+1>pos)//zag zag
		{
			root->right->right=Splay(root->right->right,index-pos);
			root=leftRotate(root);//coz root exists we don't need to check
		}
		else if(index+1<pos)//zag zig
		{
			root->right->left=Splay(root->right->left,index);
			if(root->right->left!=NULL)
				root->right=rightRotate(root->right);
		}
		return (root->right==NULL)?root:leftRotate(root);
	}
}

Node* insert(Node *root,char ch,int index)
{
	if(root==NULL)
		return newNode(ch);
	root=Splay(root,index);
	int pos=((root->left==NULL)?0:root->left->NoOfNodes)+1;
	if(pos==index+1)
		return root;
	Node *newN=newNode(ch);
	if(index+1<pos)
	{
		newN->left=root->left;
		root->left=NULL;
		root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
		newN->right=root;
	}
	else
	{
		newN->right=root->right;
		root->right=NULL;
		root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;//or root->NoOfNodes=root->left->NoOfNodes+root->data,check if root->left exists
		newN->left=root;
	}
	root=newN;
	root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
	return root;
}

Node* search(Node *root,int index)
{
	root=Splay(root,index);
	return root;//the root will be changed, so return root and check there if data==root->data then do
}

struct pair
{
	Node* first;
	Node* second;
};
typedef struct pair Pair;

Pair SplayTreeSplit(Node *root,int index)
{
	Pair p={NULL,NULL};
	if(root==NULL)
		return p;
	root=Splay(root,index);
	int pos=((root->left==NULL)?0:root->left->NoOfNodes)+1;
	if(pos>=index+1)//split as desired
	{
		p.first=root->left;
		root->left=NULL;
		root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;//root is split into root(root with right) and root->left, so only root NoOfNodes will change coz, we are removing root->left from root
		p.second=root;//putting the key also in the second
	}
	else
	{
		p.second=root->right;
		root->right=NULL;
		root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
		p.first=root;
	}
	return p;
}

Node* SplayTreeMerge(Node *lnode,Node *rnode)//left all are less than right
{
	if(lnode==NULL)
		return rnode;
	if(rnode==NULL)
		return lnode;//INT_MAX-1 COZ INDEX+1 IN SPLAY FUNCTION**************************
	lnode=Splay(lnode,INT_MAX-1);//there won't be a right node in the max ele, so directly root->right=right;
	Node *root=lnode;
	root->right=rnode;
	root->NoOfNodes=calNoOfNodes(root->left,root->right)+1;
	return root;
}

void postOrder_free(Node *root)
{
	if(root==NULL)
		return;
	postOrder_free(root->left);
	postOrder_free(root->right);
	free(root);
}

char* inOrder(Node *root,int len)
{
	if(root==NULL)
		return NULL;
	Stack *s=create_stack();
	Node *curr=root;
	int size=0;
	char *result=(char*)malloc((len+1)*sizeof(char));//u can do using capacity and all, simply passed len
	while(!isEmpty(*s) || curr!=NULL)
	{
		while(curr!=NULL)
		{
			push(s,curr);
			curr=curr->left;
		}
		curr=Top(*s);
		pop(s);
		result[size++]=curr->ch;
		curr=curr->right;//if(curr->right)curr=curr->right else curr=NULL;one and the same
	}
	free(s);
	return result;
}

struct query
{
	int i;
	int j;
	int k;
};
typedef struct query Query;

char* processQueries(char *s,int n,Query *q)
{
	Node *root=NULL;
	int len=strlen(s);
	for(int i=0;i<len;++i)
		root=insert(root,s[i],i);
	Pair p1,p2,p3;
	for(int l=0;l<n;++l)
	{
		p1=SplayTreeSplit(root,q[l].i);
		p2=SplayTreeSplit(p1.second,q[l].j-q[l].i+1);
		root=SplayTreeMerge(p1.first,p2.second);
		if(q[l].k!=0)
		{
    		p3=SplayTreeSplit(root,q[l].k);
    		root=SplayTreeMerge(p3.first,p2.first);
    		root=SplayTreeMerge(root,p3.second);
		}
		else
		    root=SplayTreeMerge(p2.first,root);//u can do this without the if condition also, but this saves a lot of time
	}
	char *result;
	result=inOrder(root,len);
	postOrder_free(root);
	return result;
}

int main()
{
	char *s=(char*)malloc(300001*sizeof(char));
	scanf("%s",s);
	s=(char*)realloc(s,(strlen(s)+1)*sizeof(char));
	int n;
	scanf("%d",&n);
	Query *q=(Query*)malloc(n*sizeof(Query));
	for(int i=0;i<n;++i)
		scanf("%d%d%d",&q[i].i,&q[i].j,&q[i].k);
	char *result;
	result=processQueries(s,n,q);
	printf("%s",result);
	free(result);
	free(q);
	return 0;
}