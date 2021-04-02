#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node 
{
	int data;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->left=NULL;
	n->right=NULL;
	return n;
}

extern Node* leftRotate(Node *root);
inline Node* leftRotate(Node *root)
{
	Node *lnode=root;
	root=root->right;
	lnode->right=root->left;
	root->left=lnode;
	return root;
}

extern Node* rightRotate(Node *root);
inline Node* rightRotate(Node *root)
{
	Node *rnode=root;
	root=root->left;
	rnode->left=root->right;
	root->right=rnode;
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
			root=rightRotate(root);//coz root exists we don't need to check, and we do this first coz, 6<-5<-4 is converted ot 6<-5->4 and then to 6->5->4, so here we do rRotate of root and then later on we do rRotate of root->left
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
		newN->right=root;
		newN->left=root->left;
		root->left=NULL;
	}
	else
	{
		newN->left=root;
		newN->right=root->right;
		root->right=NULL;
	}
	root=newN;
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
	lnode=Splay(lnode,key);//coz the lnode and rnode both might have both it's left and right nodes and hence we need to splay, so that the largest ele comes to the top, coz it won't have left or right nodes and we can attach rnode to this
	lnode->right=rnode;
	root=lnode;
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
		p.second=root;//putting the key also in the second
	}
	else
	{
	    p.second=root->right;
	    root->right=NULL;
		p.first=root;
	}
	return p;
}

Node* SplayTreeMerge(Node *left,Node *right)//left all are less than right
{
	if(lnode==NULL)
		return rnode;
	if(rnode==NULL)
		return lnode;
	left=Splay(left,INT_MAX);
	Node *root=left;
	root->right=right;
	return root;
}

void preOrder(Node *root)
{
	if(root==NULL)
		return;
	printf("%d,",root->data);
	preOrder(root->left);
	preOrder(root->right);
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
	Node *root=NULL;//************************
	for(int i=0;i<7;++i)
	{
		root=insert(root,i);
		preOrder(root);
		printf("\n");
	}
	root=search(root,3);
	preOrder(root);
	printf("\n");
	root=Delete(root,3);
	preOrder(root);
	printf("\n");
    Pair p;
	p=SplayTreeSplit(root,4);
	preOrder(p.first);
	printf("\n");
	preOrder(p.second);
	printf("\n");
	root=SplayTreeMerge(p.first,p.second);
	preOrder(root);
	printf("\n");
	postOrder_free(root);
	return 0;
}