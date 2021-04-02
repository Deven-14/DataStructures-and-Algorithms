#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	int ht;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n = (Node*)malloc(sizeof(Node));
	n->data = data;
	n->ht = 0;//considering height of a single node as 0 and not 1
	n->left = NULL;
	n->right = NULL;
	printf("Entered data : %d\n", data);
	return n;
}

int maxHeight(Node *lnode, Node *rnode)
{
	int lh = (lnode != NULL)? lnode->ht : -1;
	int rh = (rnode != NULL)? rnode->ht : -1;
	return (lh > rh)? lh : rh;
}

int balanceFactor(Node *root)
{
	int lh = (root->left != NULL)? root->left->ht : -1;
	int rh = (root->right != NULL)? root->right->ht : -1;
	return (lh - rh);
}

Node* leftRotate(Node *root)
{
	printf("Left Rotate %d\n", root->data);
	Node *lnode = root;
	root = root->right;
	lnode->right = root->left;
	root->left = lnode;
	lnode->ht = maxHeight(lnode->left, lnode->right) + 1;
	root->ht = maxHeight(root->left, root->right) + 1;
	return root;
}

Node* rightRotate(Node *root)
{
	printf("Right Rotate %d\n", root->data);
	Node *rnode = root;
	root = root->left;
	rnode->left = root->right;
	root->right = rnode;
	rnode->ht = maxHeight(rnode->left, rnode->right) + 1;
	root->ht = maxHeight(root->left, root->right) + 1;
	return root;
}

Node* reBalance(Node *root)
{
	int bf = balanceFactor(root);
	printf("Balance Factor of %d : %d\n", root->data, bf);
	if(bf == 2)
	{
		if(balanceFactor(root->left) == -1)
		{
			printf("Balance Factor of %d : -1\n", root->left->data);
			root->left = leftRotate(root->left);
		}
		root = rightRotate(root);
	}
	else if(bf == -2)
	{
		if(balanceFactor(root->right) == 1)
		{
			printf("Balance Factor of %d : 1\n", root->right->data);
			root->right = rightRotate(root->right);
		}
		root = leftRotate(root);
	}
	return root;
}

Node* insert(Node *root, int data)
{
	if(root == NULL)
		return newNode(data);
	else if(data < root->data)
		root->left = insert(root->left, data);
	else
		root->right = insert(root->right, data);
	root->ht = maxHeight(root->left, root->right) + 1;
	root = reBalance(root);
	return root;
}

Node* findMin(Node *root)
{
	if(root == NULL)
		return NULL;
	Node *curr = root;
	while(curr->left != NULL)
		curr = curr->left;
	return curr;
}

Node* Delete(Node *root, int key)
{
	if(root == NULL)
		return NULL;
	else if(key < root->data)
		root->left = Delete(root->left, key);
	else if(key > root->data)
		root->right = Delete(root->right, key);
	else
	{
		if(root->left == NULL && root->right == NULL)
		{
			free(root);
			root = NULL;
		}
		else if(root->left == NULL)
		{
			Node *temp = root;
			root = root->right;
			free(temp);
		}
		else if(root->right == NULL)
		{
			Node *temp = root;
			root = root->left;
			free(temp);
		}
		else
		{
			Node *temp = findMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	if(root == NULL)
		return NULL;
	root->ht = maxHeight(root->left, root->right) + 1;
	root = reBalance(root);
	return root;
}

void inOrder(Node *root)
{
	if(root == NULL)
		return ;
	inOrder(root->left);
	printf("%d: %d, ", root->data, balanceFactor(root));
	inOrder(root->right);
}

void postOrderFree(Node *root)
{
	if(root == NULL)
		return ;
	postOrderFree(root->left);
	postOrderFree(root->right);
	free(root);
}

int main()
{
	Node *root = NULL;
	int data[] = {30, 31, 32, 23, 22, 28, 24, 29, 26, 27, 34, 36};
	for(int i = 0; i < 12; ++i)
	{
		root = insert(root, data[i]);
		printf("Inorder traversal (data: bf) : ");
		inOrder(root);
		printf("\n\n");
	}
	int del;
	do{
		printf("\n\nEnter data to be deleted (-999 to exit) : " );
		scanf("%d", &del);
		root = Delete(root, del);
		printf("Inorder traversal (data: bf) : ");
		inOrder(root);
	}while(del != -999);
	postOrderFree(root);
	printf("\n");
	return 0;
}
