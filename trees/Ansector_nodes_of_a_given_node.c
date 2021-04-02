#include<stdio.h>
#include<stdbool.h>
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
//if we want single ancestor see inorder traversal
void printAncestors(Node *root,int data)//this is for binary search tree
{
	if(root==NULL)
		return;
	if(data<root->data)
		printAncestors(root->left,data);
	else if(data>root->data)
		printAncestors(root->right,data);
	else
		return;//when found
	printf("%d,",root->data);
}
// this is for a normal binary tree and not a bst
bool print_Ancestors_of_bt(Node *root, int data)
{
	if(root==NULL)
		return false;
	if(root->data==data)
		return true;
	/* If target is present in either left or right subtree of this node, 
     then print this node */
	if(print_Ancestors_of_bt(root->left,data) || print_Ancestors_of_bt(root->right,data))
	{
		printf("%d,",root->data);
		return true;
	}
	return false;
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
	printAncestors(root,10);
	if(!print_Ancestors_of_bt(root,10))
		printf("10 is not present");
	postOrder_Free(root);
	return 0;
}