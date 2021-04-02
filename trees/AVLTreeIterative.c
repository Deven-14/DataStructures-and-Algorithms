#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	int ht;
	struct node *left;
	struct node *right;
	struct node *parent;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n = (Node*)malloc(sizeof(Node));
	n->data = data;
	n->ht = 0;//considering height of a single node as 0 and not 1
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
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
	Node *parent = root->parent;//extra
	Node *lnode = root;
	root = root->right;
	lnode->right = root->left;
	root->left = lnode;
	if(lnode->right)
	    lnode->right->parent = lnode;//extra
	lnode->parent = root;//extra
	root->parent = parent;//extra
	if(parent)
		(parent->left == lnode) ? (parent->left = root) : (parent->right = root);
	lnode->ht = maxHeight(lnode->left, lnode->right) + 1;
	root->ht = maxHeight(root->left, root->right) + 1;
	return root;
}

Node* rightRotate(Node *root)
{
	printf("Right Rotate %d\n", root->data);
	Node *parent = root->parent;//extra
	Node *rnode = root;
	root = root->left;
	rnode->left = root->right;
	root->right = rnode;
	if(rnode->left)
		rnode->left->parent = rnode;//extra
	rnode->parent = root;//extra
	root->parent = parent;//extra
	if(parent)
		(parent->left == rnode) ? (parent->left = root) : (parent->right = root);
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
	Node *curr = root, *prev = NULL;
	while(curr!=NULL)
	{
		prev = curr;
		if(data < curr->data)
			curr = curr->left;
		else if(data > curr->data)
			curr = curr->right;
	}
	curr = newNode(data);
	curr->parent = prev;
	if(data < prev->data)
		prev->left = curr;
	else
		prev->right = curr;
	curr = prev;
	while(curr != NULL)
	{
		curr->ht = maxHeight(curr->left, curr->right) + 1;
		curr = reBalance(curr);
		prev = curr;
		curr = curr->parent;
	}
	root = prev;
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
	Node *curr = root, *prev = NULL;
	while(curr!=NULL && curr->data != key)
	{
		prev = curr;
		if(key < curr->data)
			curr = curr->left;
		else if(key > curr->data)
			curr = curr->right;
	}
	if(curr == NULL)
		return root;
	if(curr->left == NULL && curr->right == NULL)
	{
	    if(prev == NULL)
	        root = NULL;
		else if(prev->left == curr)
			prev->left = NULL;
		else
			prev->right = NULL;
		free(curr);
	}
	else if(curr->left == NULL)
	{
	    if(prev == NULL)
	        root = curr->right;
		else if(prev->left == curr)
			prev->left = curr->right;
		else
			prev->right = curr->right;
		curr->right->parent = prev;//extra
		free(curr);
	}
	else if(curr->right == NULL)
	{
	    if(prev == NULL)
	        root = curr->left;
		else if(prev->left == curr)
			prev->left = curr->left;
		else
			prev->right = curr->left;
		curr->left->parent = prev;//extra
		free(curr);
	}
	else
	{
		Node *temp = findMin(curr->right);
		curr->data = temp->data;
		Node *parent = temp->parent;
		if(parent->left == temp)
			parent->left = temp->right;//*****************, coz, obviously parent->left is temp and temp->left is null and if(temp->right) then parent->left = temp->right;, if temp->right == NULL then also parent->left = null directly
		else
			parent->right = temp->right;//****coz, parent could be curr, when curr->right is the min ele
		if(temp->right)
			temp->right->parent = parent;//*************
		free(temp);
		prev = parent;//****************from here till head we have to fix ht and reBalance
	}
	if(root == NULL)
	    return NULL;
	if(prev != NULL)
		curr = prev;
	else
		curr = root;
	while(curr != NULL)
	{
		curr->ht = maxHeight(curr->left, curr->right) + 1;
		curr = reBalance(curr);
		prev = curr;// put prev here coz after rebalancing the curr will change
		curr = curr->parent;
	}
	root = prev;
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
