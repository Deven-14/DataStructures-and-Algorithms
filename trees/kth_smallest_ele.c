#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	int NoOfNodes;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->NoOfNodes=1;
	n->left=n->right=NULL;
	return n;
}

int no_of_nodes(Node *l,Node *r)
{
	int ln=0,rn=0;
	if(l)
		ln=l->NoOfNodes;
	if(r)
		rn=r->NoOfNodes;
	return ln+rn;
}

Node* insert(Node* root,int data)
{
	if(root==NULL)
		return newNode(data);
	else if(data<root->data)
		root->left=insert(root->left,data);
	else if(data>root->data)
		root->right=insert(root->right,data);
	root->NoOfNodes=1+no_of_nodes(root->left,root->right);
	return root;
}

void postOrder_Free(Node *root)
{
	if(root==NULL)
		return;
	postOrder_Free(root->left);
	postOrder_Free(root->right);
	free(root);
}

//**************for largest do right-node-left, reverse inorder
Node* kthSmallestEle(Node *root,int *k)
{
	if(root==NULL)
		return NULL;
	Node *l=kthSmallestEle(root->left,k);
	if(l!=NULL)
		return l;
	(*k)--;
	if(*k==0)
		return root;
	return kthSmallestEle(root->right,k);
}

Node* kth_Smallest_using_no_of_Nodes(Node *root,int k)
{
	if(root==NULL)
		return NULL;
	int count=1;
	if(root->left)//instead, store no of nodes in left sub tree, i.e lcount, then count=r->lcount+1;
		count=root->left->NoOfNodes+1;
	if(count>k)
		return kth_Smallest_using_no_of_Nodes(root->left,k);
	else if(count<k)
		return kth_Smallest_using_no_of_Nodes(root->right,k-count);
	return root;//if count==k
}

int main()
{
	Node* root = NULL; 
	int keys[] = { 20, 8, 22, 4, 12, 10, 14 };
	/*
	        20
		8        22
	 4    12
		10  14
		 */
	for (int i=0;i<7;i++)
		root = insert(root, keys[i]);
	int k = 3;
	Node *n;
	n=kth_Smallest_using_no_of_Nodes(root,k);
	if(n)
		printf("%d,\n",n->data);
	n=kthSmallestEle(root,&k);
	if(n)
		printf("%d\n",n->data);
	postOrder_Free(root);
	return 0;
}