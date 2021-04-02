#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
	int ht;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->left=NULL;
	n->right=NULL;
	n->ht=0;
	return n;
}

Node* find(Node *root,int key)//return the last closest node if the node with key value is not found, check if root is not null before finding the ele**************8
{
	if(root->data==key)
		return root;
	else if(key<root->data){
		if(root->left!=NULL)
			return find(root->left,key);
		//return root;
	}
	else if(key>root->data){
		if(root->right!=NULL)
			return find(root->right,key);
		//return root;
	}
	return root;//it'll return root, if null
}

extern int maxHeight(Node *ln,Node *rn);
inline int maxHeight(Node *ln,Node *rn)
{
	int lh=-1,rh=-1;
	if(ln)
		lh=ln->ht;
	if(rn)
		rh=rn->ht;
	return (lh>rh)?lh:rh;
}

extern int balanceFactor(Node *n);
inline int balanceFactor(Node *n)
{
	int lh=-1,rh=-1;
	if(n->left)
		lh=n->left->ht;
	if(n->right)
		rh=n->right->ht;
	return lh-rh;
}

Node* lRotate(Node *root)
{
	Node *lnode=root;
	root=root->right;
	lnode->right=root->left;
	root->left=lnode;
	lnode->ht=maxHeight(lnode->left,lnode->right)+1;
	root->ht=maxHeight(root->left,root->right)+1;
	return root;
}

Node* rRotate(Node *root)
{
	Node *rnode=root;
	root=root->left;
	rnode->left=root->right;
	root->right=rnode;
	rnode->ht=maxHeight(rnode->left,rnode->right)+1;
	root->ht=maxHeight(root->left,root->right)+1;
	return root;
}

Node* reBalance(Node *n)
{
	int bf=balanceFactor(n);
	if(bf>1)
	{
		if(balanceFactor(n->left)<0)
			n->left=lRotate(n->left);
		n=rRotate(n);
	}
	if(bf<-1)
	{
		if(balanceFactor(n->right)>0)
			n->right=rRotate(n->right);
		n=lRotate(n);
	}
	return n;
}

Node* insert(Node *root,int data)
{
	if(root==NULL)
		root=newNode(data);
	else if(data<root->data)
		root->left=insert(root->left,data);
	else if(data>root->data)
		root->right=insert(root->right,data);
	root->ht=maxHeight(root->left,root->right)+1;
	root=reBalance(root);//instead of making it a function, write the code here itself
	return root;
}

Node* findMin(Node *root)
{
	Node *curr=root;
	while(curr->left!=NULL)
		curr=curr->left;
	return curr;
}

Node* Delete(Node *root,int key)
{
	if(root==NULL)
		return root;
	else if(key<root->data)
		root->left=Delete(root->left,key);
	else if(key>root->data)
		root->right=Delete(root->right,key);
	else
	{
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			root=NULL;
		}
		else if(root->left==NULL)
		{
			Node* temp=root;
			root=root->right;//it'll return this node address to the previous left/right node
			free(temp);
		}
		else if(root->right==NULL)
		{
			Node *temp=root;
			root=root->left;
			free(temp);
		}
		else
		{
			Node *temp=findMin(root->right);
			root->data=temp->data;
			root->right=Delete(root->right,root->data);
		}
	}
	if(root==NULL)//**************************, it might not have any sub nodes, so root=NULL
	    return NULL;
	root->ht=maxHeight(root->left,root->right)+1;//****************************when ever u add or delete or rebalance, u have to fix the height
	root=reBalance(root);
	return root;
}

/*extern Node* mergeWithRoot(Node *ln,Node *rn,Node *root);
inline Node* mergeWithRoot(Node *ln,Node *rn,Node *root)//but height will not be balanced, and this is for unbalanced binary trees
{
	root->left=ln;
	root->right=rn;//if we use parent node then as
	return root;
}*/

Node* AVLMergeWithRoot(Node *r1,Node *r2,Node *root)//for balanced binary trees*********************
{
	//not checking if r1 and r2 exist coz, we passing we check and these are balanced bt so the difference at one point will definitely be <=1 before reaching null
	if(abs(r1->ht-r2->ht)<=1)//base condition
	{
		root->left=r1;
		root->right=r2;
		root->ht=maxHeight(r1,r2)+1;
		return root;
	}
	else if(r1->ht>r2->ht)
	{
		r1->right=AVLMergeWithRoot(r1->right,r2,root);//if r1 height is greater than go right then return right
		r1->ht=maxHeight(r1->left,r1->right)+1;//change it's height
		r1=reBalance(r1);//then rebalance if necessary
		return r1;
	}
	else// if(r2->ht>r2->ht)
	{
		r2->left=AVLMergeWithRoot(r1,r2->left,root);//""
		r2->ht=maxHeight(r2->left,r2->right);
		r2=reBalance(r2);
		return r2;
	}
}

Node* merge(Node *r1,Node *r2)
{
	if(r1==NULL)
		return r2;
	if(r2==NULL)
		return r1;
	Node *temp=find(r1,INT_MAX);//or min from r2
	Node *root=newNode(temp->data);
	r1=Delete(r1,temp->data);
	if(r1==NULL)//don't need to check if r2 is null coz, if it was null then then in the begining itself it would return r1
		root->right=r2;
	else
		root=AVLMergeWithRoot(r1,r2,root);
	return root;
}

struct pair
{
	Node *first;
	Node *second;
};
typedef struct pair Pair;

extern Pair create_pair(Node *f,Node *s);
inline Pair create_pair(Node *f,Node *s)
{
	Pair p;
	p.first=f;
	p.second=s;
	return p;
}

extern Node* mergeWithRoot(Node *ln,Node *rn,Node *root);
inline Node* mergeWithRoot(Node *ln,Node *rn,Node *root)//but height will not be balanced, and this is for unbalanced binary trees
{
	root->left=ln;
	root->right=rn;//if we use parent node then as
	root->ht=maxHeight(root->left,root->right)+1;
	return root;
}

Pair split(Node *root,int key)
{
	if(root==NULL)
		return create_pair(NULL,NULL);
	else if(key<=root->data)//if i want the key on the bigger tree then here key<= or else below
	{
		Pair p=split(root->left,key);
		p.second=mergeWithRoot(p.second,root->right,root);
		return p;
	}
	else// if(key>root->data)
	{
		Pair p=split(root->right,key);
		p.first=mergeWithRoot(root->left,p.first,root);
		return p;
	}
}

void inOrder(Node *root)
{
	if(root==NULL)
		return;
	inOrder(root->left);
	printf("%d,",root->data);
	inOrder(root->right);
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
	Node *r1,*r2,*root;
	r1=NULL;//*********************
	r2=NULL;//****************************
	root=NULL;//****************************
	for(int i=1;i<=6;++i)
		r1=insert(r1,i);
	inOrder(r1);
	printf("\n");
	for(int i=7;i<=11;++i)
		r2=insert(r2,i);
	inOrder(r2);
	printf("\n");
	root=merge(r1,r2);
	r1=NULL;//*********************
	r2=NULL;//**************************
	inOrder(root);
	printf("\n");
	printf("split\n");
	Pair p=split(root,5);
	root=NULL;//***********************************
	r1=p.first;
	r2=p.second;
	inOrder(r1);
	printf("\n");
	inOrder(r2);
	printf("\n");
	postOrder_free(r1);
	postOrder_free(r2);
	return 0;
}