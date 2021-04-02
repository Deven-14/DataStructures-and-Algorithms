#include <stdio.h>
#include <stdlib.h>

#define red 0
#define black 1

//enum Color{red, blac};

struct node
{
	int data;
	int color;
	struct node *left, *right, *parent;
};
typedef struct node Node;

Node* newNode(int data)
{
	Node *n = (Node*)malloc(sizeof(Node));
	n->data = data;
	n->color = red;
	n->left = n->right = n->parent = NULL;
	return n;
}

Node* search(Node *root, int key)
{
	if(root == NULL)
		return NULL;
	else if(key < root->data)
		return search(root->left, key);
	else if(key > root->data)
		return search(root->right, key);
	return root;
}

Node* bstInsert(Node *root, Node *new_node)
{
	if(root == NULL)
		return new_node;
	else if(new_node->data < root->data)
	{
		root->left = bstInsert(root->left, new_node);
		root->left->parent = root;
	}
	else
	{
		root->right = bstInsert(root->right, new_node);
		root->right->parent = root;
	}
	return root;
}

Node* leftRotate(Node *root)
{
	
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
	
	return root;
}

Node* rightRotate(Node *root)
{
	
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
	
	return root;
}

extern void swap(int *, int *);
inline void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

Node* fixViolation(Node *root, Node *curr)
{
	Node *parent = NULL, *grandParent = NULL, *uncle = NULL;//w.r.t curr
	
	while((curr != root) && (curr->color != black) && (curr->parent->color == red))
	{
		parent = curr->parent;
		grandParent = parent->parent;//if all the 3 cases of the while loop are true then tree must be a grandParent
		
		if(parent == grandParent->left)
		{
			uncle = grandParent->right;
			
			if(uncle != NULL && uncle->color == red)
			{
				uncle->color = black;
				parent->color = black;
				grandParent->color = red;
				curr = grandParent;
			}
			else
			{
				if(curr == parent->right)
					parent = leftRotate(parent);
				grandParent = rightRotate(grandParent);
				curr = grandParent;
				swap(&curr->color, &curr->right->color);
			}
		}
		else
		{
			uncle = grandParent->left;
			
			if(uncle != NULL && uncle->color == red)
			{
				uncle->color = black;
				parent->color = black;
				grandParent->color = red;
				curr = grandParent;
			}
			else
			{
				if(curr == parent->left)
					parent = rightRotate(parent);
				grandParent = leftRotate(grandParent);
				curr = grandParent;
				swap(&curr->color, &curr->left->color);
			}
		}
	}
	
	if(curr->parent == NULL)
		root = curr;//instead of putting it in rotations, i put it here, orelse we can put it in if(parent){} else { MainRoot = root; } in both left and right rotation, MainRoot, we would have to pass as an argument
	root->color = black;
	
	return root;
}

Node* fixRedRed(Node *root, Node *curr)
{
	if(curr == root)
	{
		root->color = black;
		return root;
	}
	if(curr->color == black  || curr->parent->color == black)
		return root;
	
	Node *parent = curr->parent, *grandParent = parent->parent;//grand parent exists if curr->color = red and curr->par->color=red
	Node *uncle = (grandParent->left == parent) ? (grandParent->right) : (grandParent->left);
	
	if(uncle != NULL && uncle->color == red)
	{
		uncle->color = black;
		parent->color = black;
		grandParent->color = red;
		root = fixRedRed(root, grandParent);
	}
	else if(parent == grandParent->left)
	{
		if(curr == parent->right)
			parent = leftRotate(parent);
		grandParent = rightRotate(grandParent);
		curr = grandParent;
		swap(&curr->color, &curr->right->color);
	}
	else
	{
		if(curr == parent->left)
			parent = rightRotate(parent);
		grandParent = leftRotate(grandParent);
		curr = grandParent;
		swap(&curr->color, &curr->left->color);
	}
	
	if(curr->parent == NULL)
		root = curr;//instead of putting it in rotations, i put it here, orelse we can put it in if(parent){} else { MainRoot = root; } in both left and right rotation, MainRoot, we would have to pass as an argument
	root->color = black;
	
	return root;
}

Node* insert(Node *root, int data)
{
	Node *new_node = newNode(data);
	root = bstInsert(root, new_node);
	//root = fixViolation(root, new_node);
	root = fixRedRed(root, new_node);
	return root;
}

int hasRedChild(Node *root)
{
	if(root == NULL)
		return 0;
	if(root->left != NULL && root->left->color == red)
		return 1;
	if(root->right != NULL && root->right->color == red)
		return 1;
	return 0;
}

Node* fixDoubleBlack(Node *root, Node *key)
{
	if(key == root)
		return root;
	Node *parent = key->parent;
	Node *sibling = (parent->left == key) ? parent->right : parent->left;//if key is not root then it has a parent
	
	if(sibling == NULL)//nothing is there to rotate, so go up
		root = fixDoubleBlack(root, parent);
	else if(sibling->color == red)
	{//if sibling red then only 2 cases, i.e sibling to the left or right then recur
		parent->color = red;
		sibling->color = black;//remember red cannot have red as parent
		if(sibling == parent->left)
			parent = rightRotate(parent);
		else
			parent = leftRotate(parent);
		if(parent->parent == NULL)
			root = parent;
		root = fixDoubleBlack(root, key);
	}
	else//sibling color black
	{
		if(hasRedChild(sibling))
		{
			if(sibling->left != NULL && sibling->left->color == red)
			{
				if(sibling == parent->left)//left left
				{
					sibling->left->color = sibling->color;
					sibling->color = parent->color;//(and key->parent->color = black; down)//coz parent could be red
					parent = rightRotate(parent);
				}
				else//right left
				{
					sibling->color = red;
					sibling->left->color = black; //rr
					//sibling->left->color = parent->color;
					sibling = rightRotate(sibling);
					//sibling is changed, now for the new sibling 
					sibling->color = parent->color;
					sibling->right->color = black;//(and key->parent->color = black; down)
					//instead of all this, it is nothing but, sibling->left->color = black in the begining and then change parent color, coz parent could be red
					parent = leftRotate(parent);
				}
			}
			else
			{
				if(sibling == parent->right)//right right
				{
					sibling->right->color = sibling->color;
					sibling->color = parent->color;
					parent = leftRotate(parent);
				}
				else//left right
				{
					//sibling->right->color = parent->color;
					sibling->color = red;
					sibling->right->color = black;
					sibling = leftRotate(sibling);
					sibling->color = parent->color;
					sibling->left->color = black;
					parent = rightRotate(parent);
				}
			}
			key->parent->color = black;//********************remember to use key->parent->color and not parent->color, obvio coz it would have changed
			if(parent->parent == NULL)//************
				root = parent;
		}
		else//all children are black
		{
			sibling->color = red;
			if(parent->color == black)
				root = fixDoubleBlack(root, parent);
			else
				parent->color = black;
		}
	}
	return root;
}

Node* findMin(Node *root)
{
	if(!root)
		return NULL;
	Node *n = root;
	while(n->left != NULL)
		n = n->left;
	return n;
}

Node* deleteNode(Node *root, Node *key)
{
	if(key->left == NULL && key->right == NULL)//leaf node
	{
		if(root == key)
			root = NULL;
		else
		{
			if(key->color == black)//double black condition coz, it's child is null and hence black
				root = fixDoubleBlack(root, key);
			//else if red then delete directly
			Node *parent = key->parent;
			if(key == parent->left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		free(key);
	}
	else if(key->left == NULL || key->right == NULL)//has one child
	{
		Node *child = (key->right != NULL) ? key->right : key->left;
		Node *parent = key->parent;
		if(key == root)
		{
			root = child;
			root->color = black;
			root->parent = NULL;
		}
		else
		{
			if(parent->left == key)
				parent->left = child;
			else
				parent->right = child;
			child->parent = parent;//detaching key
			if(key->color == black && child->color == black)//double black case
				root = fixDoubleBlack(root, child);
			else//either one is red
				child->color = black;
		}
		free(key);
	}
	else//has 2 children
	{
		Node *temp = findMin(key->right);
		key->data = temp->data;
		key->right = deleteNode(key->right, temp);
	}
	return root;
}

Node* Delete(Node *root, int key)
{
	if(root == NULL)
		return root;
	Node *Key = search(root, key);
	if(!Key)
		return root;
	root = deleteNode(root, Key);
	return root;
}

void inOrder(Node *root)
{
	if(root == NULL)
		return;
	inOrder(root->left);
	printf("%d-color-%d, ", root->data, root->color);
	inOrder(root->right);
}

void postOrderFree(Node *root)
{
	if(root == NULL)
		return;
	postOrderFree(root->left);
	postOrderFree(root->right);
	free(root);
}

int main()
{
	Node *root = NULL;
	root = insert(root, 3);
	printf("Inorder : ");
	inOrder(root);
	root = insert(root, 21);
	printf("\nInorder : ");
	inOrder(root);
	root = insert(root, 32);
	printf("\nInorder : ");
	inOrder(root);
	root = insert(root, 17);
	printf("\nInorder : ");
	inOrder(root);
	postOrderFree(root);
	return 0;
}