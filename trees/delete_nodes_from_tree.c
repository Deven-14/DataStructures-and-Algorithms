#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}Node;
Node* newNode(int data)
{
	Node *n=(Node*)malloc(sizeof(Node));
	n->data=data;
	n->left=n->right=NULL;
	return n;
}
Node* findMin(Node *root)
{
	Node *curr=root;
	while(curr->left!=NULL)
		curr=curr->left;
	return curr;
}
Node* Delete_node(Node *root,int data)
{
	if(root==NULL)
		return NULL;
	else if(data<root->data)
		root->left=Delete_node(root->left,data);
	else if(data>root->data)
		root->right=Delete_node(root->right,data);
	else
	{
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			root==NULL;
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
			root->right=Delete_node(root->right,root->data);
		}
	}
	return root;
}
Node* Insert(Node *root,int data)
{
	if(root==NULL)
		root=newNode(data);
	else if(data<=root->data)
		root->left=Insert(root->left,data);
	else if(data>root->data)
		root->right=Insert(root->right,data);
	return root;
}
void inOrder(Node *root)
{
	if(root==NULL)
		return;
	inOrder(root->left);
	printf("%d ",root->data);
	inOrder(root->right);
}
int main()
{
	/*Code To Test the logic
	  Creating an example tree
				5
			   / \
			  3   10
			 / \   \
			1   4   11
    */
	Node* root = NULL;
	root = Insert(root,5); 
	root = Insert(root,10);
	root = Insert(root,3); 
	root = Insert(root,4); 
	root = Insert(root,1); 
	root = Insert(root,11);
	root=Delete_node(root,1);
	root = Delete_node(root,3);
	root=Delete_node(root,5);
	printf("inorder");
	inOrder(root);
	return 0;
}