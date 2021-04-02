#include<stdio.h>
#include<stdlib.h>

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
	n->left=n->right=NULL;
	return n;
}

Node* insert(Node* root,int data)
{
	if(root==NULL)
		return newNode(data);
	else if(data<root->data)
		root->left=insert(root->left,data);
	else if(data>root->data)
		root->right=insert(root->right,data);
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

Node* find(Node *root,int data)
{
	if(root==NULL)
		return NULL;
	else if(data<root->data)
		return find(root->left,data);
	else if(data>root->data)
		return find(root->right,data);
	return root;
}

Node* findMin(Node *n)
{
	while(n->left!=NULL)
		n=n->left;
	return n;
}

Node* InOrderSuccessor(Node *root,int data)//here if u have the node, then u can pass the node itself and avoid find();
{
	Node *current=find(root,data);
	if(current==NULL)
		return NULL;
	if(current->right!=NULL)
		return findMin(current->right);
	else{// u can use another field in the node as parent and do this easily, or u can do it like this
		Node *successor=NULL;//********************
		Node *ancestor=root;
		while(ancestor!=current)
		{
			if(data<ancestor->data)
			{
				successor=ancestor;
				ancestor=ancestor->left;
			}
			else 
				ancestor=ancestor->right;
		}
		return successor;
	}
}
/*
Node* successor(Node *root, int data)
{
	Node *current=find(root,data);
	if(current==NULL)
		return NULL;
	if(current->right)
		return findMin(current->right);
	else
	{
		while(current->parent && current->data>current->parent->data)
			current=current->parent;
		return current->parent;
		//findAncestor() recusively
		if(current->parent==NULL)
			return NULL;
		if(current->data<current->parent->data)
			return current->parent;
		else
			return findAncestor(current->parent);
		//
	}
}
*/
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
	Node *n=InOrderSuccessor(root,10);
	if(n)
		printf("%d",n->data);
	postOrder_Free(root);
	return 0;
}