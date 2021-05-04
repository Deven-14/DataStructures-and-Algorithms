#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
	unsigned long long sum;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->left=NULL;
	n->right=NULL;
	n->sum=data;//changed to data instead of 0, coz in null case it has to be the newnode with data=data and sum=data, or else it'll be zero
	return n;
}

extern unsigned long long subtreeSum(Node *l,Node *r);
inline unsigned long long subtreeSum(Node *l,Node *r)
{
	unsigned long long sum=0;//long long or unsigned long long***************************************************************
	if(l)
		sum+=l->sum;
	if(r)
		sum+=r->sum;
	return sum;
}

Node* leftRotate(Node *root)
{
	Node *lnode=root;
	root=root->right;
	lnode->right=root->left;
	root->left=lnode;
	lnode->sum=subtreeSum(lnode->left,lnode->right)+lnode->data;//don't do lnode->sum+=coz in lnode we might have removed it's left node and the sum value will be higher then adding will make it even higher, not just for this node, for all
	root->sum=subtreeSum(root->left,root->right)+root->data;
	return root;
}

Node* rightRotate(Node *root)//not inine coz we are calling another inline function inside this
{
	Node *rnode=root;
	root=root->left;
	rnode->left=root->right;
	root->right=rnode;
	rnode->sum=subtreeSum(rnode->left,rnode->right)+rnode->data;
	root->sum=subtreeSum(root->left,root->right)+root->data;
	return root;
}

//zig-left, zag-right
Node* Splay(Node *root,int key)
{
	if(root==NULL || root->data==key)
		return root;
	if(key<root->data)
	{
		if(root->left==NULL)
			return root;//*********************no node available to rotate, so return root
		if(key<root->left->data)//zig zig
		{
			root->left->left=Splay(root->left->left,key);
			root=rightRotate(root);//coz root exists we don't need to check
		}
		else if(key>root->left->data)//zig zag
		{
			root->left->right=Splay(root->left->right,key);
			if(root->left->right!=NULL)//the element might not be found and this node will be null and hence we no need to rotate when it is not found
				root->left=leftRotate(root->left);
		}//this down is for zig case (key equal case) and key<root->left->data case, if key not found then root->left will be null, we've already rotated once that's y, so return root that time and in key> case, if key is not found then there is only root->left and root->left->right is null, so root->left is rotated, i.e rotated for other elements
		return (root->left==NULL)?root:rightRotate(root);//for key equal case and if the key is not found, then root->left here will be null,so the rotation will be done for other nodes and at root left key should be there,if it isn't there(null) then just return root of the other elements which have been rotated(the next closest element will come to the root)
	}
	else //key>root->data
	{
		if(root->right==NULL)
			return root;//*************no node available to rotate, so return root
		if(key>root->right->data)//zag zag
		{
			root->right->right=Splay(root->right->right,key);
			root=leftRotate(root);//coz root exists we don't need to check
		}
		else if(key<root->right->data)//zag zig
		{
			root->right->left=Splay(root->right->left,key);
			if(root->right->left!=NULL)//the element might not be found and this node will be null and hence we no need to rotate when it is not found
				root->right=rightRotate(root->right);
		}
		return (root->right==NULL)?root:leftRotate(root);
	}
}

Node* insert(Node *root,int data)
{
	if(root==NULL)
		return newNode(data);
	root=Splay(root,data);
	if(root->data==data)
		return root;
	Node *newN=newNode(data);
	if(data<root->data)
	{
		newN->left=root->left;
		root->left=NULL;
		root->sum=subtreeSum(root->left,root->right)+root->data;
		newN->right=root;
	}
	else
	{
		newN->right=root->right;
		root->right=NULL;
		root->sum=subtreeSum(root->left,root->right)+root->data;//or root->sum=root->left->sum+root->data,check if root->left exists
		newN->left=root;
	}
	root=newN;
	root->sum=subtreeSum(root->left,root->right)+root->data;
	return root;
}

Node* search(Node *root,int data)
{
	root=Splay(root,data);
	return root;//the root will be changed, so return root and check there if data==root->data then do
}

Node* Delete(Node *root,int key)
{
	if(root==NULL)
		return root;
	root=Splay(root,key);
	if(root->data!=key)
		return root;
	Node *lnode=root->left;
	Node *rnode=root->right;
	free(root);
	if(lnode==NULL)//u can do this with rnode also
		return rnode;
	lnode=Splay(lnode,key);//key is greater than any of the elements in the left
	lnode->right=rnode;
	root=lnode;
	root->sum=subtreeSum(root->left,root->right)+root->data;
	return root;
}

struct pair
{
	Node* first;
	Node* second;
};
typedef struct pair Pair;

Pair SplayTreeSplit(Node *root,int key)
{
	Pair p={NULL,NULL};
	if(root==NULL)
		return p;
	root=Splay(root,key);
	if(root->data>=key)//split as desired
	{
		p.first=root->left;
		root->left=NULL;
		root->sum=subtreeSum(root->left,root->right)+root->data;//root is split into root(root with right) and root->left, so only root sum will change coz, we are removing root->left from root
		p.second=root;//putting the key also in the second
	}
	else
	{
		p.second=root->right;
		root->right=NULL;
		root->sum=subtreeSum(root->left,root->right)+root->data;
		p.first=root;
	}
	return p;
}

Node* SplayTreeMerge(Node *lnode,Node *rnode)//left all are less than right
{
	if(lnode==NULL)
		return rnode;
	if(rnode==NULL)
		return lnode;
	lnode=Splay(lnode,INT_MAX);//there won't be a right node in the max ele, so directly root->right=right;
	Node *root=lnode;
	root->right=rnode;
	root->sum=subtreeSum(root->left,root->right)+root->data;
	return root;
}

struct query
{
	char type[2];
	int data;
	int l,r;
};
typedef struct query Query;

Query* inputQueries(int n)
{
	Query *q=(Query*)malloc(n*sizeof(Query));
	for(int i=0;i<n;++i)
	{
		scanf("%s",q[i].type);
		if(strcmp(q[i].type,"s")==0)
			scanf("%d%d",&q[i].l,&q[i].r);
		else
			scanf("%d",&q[i].data);
	}
	return q;
}

unsigned long long sum(Node **root,int l,int r)
{
	unsigned long long sum=0;
	Pair p1,p2;
	p1=SplayTreeSplit(*root,l);
	if(p1.second)
	{
		p2=SplayTreeSplit(p1.second,r+1);//r+1 coz, we need all ele <=r in the first node of pair and the rest in right
		if(p2.first)
			sum=p2.first->sum;
		p1.second=SplayTreeMerge(p2.first,p2.second);
	}
	*root=SplayTreeMerge(p1.first,p1.second);
	return sum;
}

void postOrder_free(Node *root);

void processQueries(int n,Query *q)
{
	int i=0;
	Node *root=NULL;//***********************************
	unsigned long long x=0;
	int M=1000000001;
	while(n--)
	{
		if(strcmp(q[i].type,"+")==0)
			root=insert(root,(q[i].data+x)%M);
		else if(strcmp(q[i].type,"-")==0)
			root=Delete(root,(q[i].data+x)%M);
		else if(strcmp(q[i].type,"?")==0)
		{
			root=search(root,(q[i].data+x)%M);
			if(root!=NULL && root->data==(q[i].data+x)%M)
				printf("Found\n");
			else
				printf("Not found\n");
		}
		else
		{
			x=sum(&root,(q[i].l+x)%M,(q[i].r+x)%M);
			printf("%lld\n",x);
		}
		i++;
	}
	postOrder_free(root);
}

void postOrder_free(Node *root)
{
	if(root==NULL)
		return;
	postOrder_free(root->left);
	postOrder_free(root->right);
	free(root);
}

int main()
{
	int n;
	scanf("%d",&n);
	Query *q=inputQueries(n);
	processQueries(n,q);
	free(q);
	return 0;
}
