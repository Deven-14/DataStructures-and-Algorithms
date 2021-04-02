#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
int getSumUtil(int *sT, int start, int end, int qs, int qe, int index)
{
	if(start >= qs && end <= qe)
		return sT[index];
	if(start > qe || end < qs)
		return 0;
	int mid = start + (end - start) / 2;
	return getSumUtil(sT, start, mid, qs, qe, 2 * index + 1) + getSumUtil(sT, mid + 1, end, qs, qe, 2 * index + 2);
}

int getSum(int *sT, int n, int qs, int qe)
{
	if(qs < 0 || qe > n-1 || qs > qe)
	{
		printf("Invalid Input\n");
		return -1;
	}
	return getSumUtil(sT, 0, n-1, qs, qe, 0);
}

void updateValueUtil(int *sT, int start, int end, int i, int diff, int index)
{
	if(i < start || i > end)
		return;
	sT[index] += diff;
	if(start == end)
		return;
	int mid = start + (end - start) / 2;
	updateValueUtil(sT, start, mid, i, diff, 2 * index + 1);
	updateValueUtil(sT, mid + 1, end, i, diff, 2 * index + 2);
}

void updateValue(int n, int arr[], int *sT, int index, int newValue)
{
	if(index < 0 || index > n-1)
	{
		printf("Invalid Input\n");
		return;
	}
	int diff = newValue - arr[index];
	arr[index] = newValue;
	updateValueUtil(sT, 0, n-1, index, diff, 0);
}

void buildSTUtil(int arr[], int start, int end, int *sT, int index)
{
	if(start == end)
	{
		sT[index] = arr[start];
		return;
	}
	int mid = start + (end - start) / 2;
	buildSTUtil(arr, start, mid, sT, 2 * index + 1);
	buildSTUtil(arr, mid + 1, end, sT, 2 * index + 2);
	sT[index] = sT[2 * index + 1] + sT[2 * index + 2];
}

int* buildST(int n, int arr[])
{
	int x = (int)ceil(log2(n));
	int size = 2 * pow(2, x) - 1;
	int *sTree = (int*)malloc(size * sizeof(int));
	buildSTUtil(arr, 0, n - 1, sTree, 0);
	return sTree;
}

int main()
{
	int n;
	printf("Enter the no of elements : ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the elements : ");
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	int *sT = buildST(n, a);
	printf("Sum = %d\n", getSum(sT, n, 0, n-1));
	printf("Enter 1 query (left and right index) : ");
	int l, r;
	scanf("%d%d", &l, &r);
	printf("Sum from %d to %d index = %d\n", l, r, getSum(sT, n, l, r));
	printf("Enter update index and value : ");
	int index, val;
	scanf("%d%d", &index, &val);
	updateValue(n, a, sT, index, val);
	printf("Sum = %d\n", getSum(sT, n, 0, n-1));
	free(sT);
	return 0;
}
*/

struct range
{
	int startIndex;
	int endIndex;
};
typedef struct range Range;

struct node
{
	int data;
	Range segment;
	int leftChildIndex;//instead of left child index u can make it left child itself same for right child index
	int rightChildIndex;
};
typedef struct node Node;//instead of making an array u can use linked lists can use this as a normal tree

//this is a FULL/PROPER/STRICT binary tree, full binary tree : 0 or 2 child nodes and no 1 child node FOR ANY NODE**************
//if n in arr[n], is power of 2 then there will be, n leaf nodes and n-1 internal nodes = 2*n-1 nodes, if n is not a power of 2, then we must find it's closest power, so
//int x = (int)ceil(log2(n));// 2^x = n; in log from is the left one, x might be a fraction, so to create a full binary tree, any node might have 2 or 0 nodes, so any random nodes can be dummy and we'll need the full 2*pow(2,x)-1 nodes coz any node can be occupied and any node could be empty
//int size = 2 * pow(2, x) - 1;

int getSumUtil(Node *sT, int qs, int qe, int index)
{
	Node *curr = &sT[index];
	if(curr->segment.startIndex >= qs && curr->segment.endIndex <= qe)
		return curr->data;
	if(curr->segment.startIndex > qe || curr->segment.endIndex < qs)
		return 0;
	return getSumUtil(sT, qs, qe, curr->leftChildIndex) + getSumUtil(sT, qs, qe, curr->rightChildIndex);
}

int getSum(Node *sT, int n, int qs, int qe)
{
	if(qs < 0 || qe > n-1 || qs > qe)
	{
		printf("Invalid Input\n");
		return -1;
	}
	return getSumUtil(sT, qs, qe, 0);
}

void updateValueUtil(Node *sT, int i, int diff, int index)
{
	Node *curr = &sT[index];
	if(i < curr->segment.startIndex || i > curr->segment.endIndex)
		return;
	curr->data += diff;
	if(curr->segment.startIndex == curr->segment.endIndex)
		return;
	updateValueUtil(sT, i, diff, curr->leftChildIndex);
	updateValueUtil(sT, i, diff, curr->rightChildIndex);
}

void updateValue(int n, int arr[], Node *sT, int index, int newValue)
{
	if(index < 0 || index > n-1)
	{
		printf("Invalid Input\n");
		return;
	}
	int diff = newValue - arr[index];
	arr[index] = newValue;
	updateValueUtil(sT, index, diff, 0);
}

void buildSTUtil(int arr[], int start, int end, Node *sT, int index)
{
	Node *curr = &sT[index];
	curr->segment.startIndex = start;
	curr->segment.endIndex = end;
	if(start == end)
	{
		curr->data = arr[start];
		return;
	}
	int mid = start + (end - start) / 2;
	curr->leftChildIndex = 2 * index + 1;
	curr->rightChildIndex = 2 * index + 2;
	buildSTUtil(arr, start, mid, sT, curr->leftChildIndex);
	buildSTUtil(arr, mid + 1, end, sT, curr->rightChildIndex);
	curr->data = sT[curr->leftChildIndex].data + sT[curr->rightChildIndex].data;
}

Node* buildST(int n, int arr[])
{
	int x = (int)ceil(log2(n));
	int size = 2 * pow(2, x) - 1;
	Node *sTree = (Node*)malloc(size * sizeof(Node));
	buildSTUtil(arr, 0, n - 1, sTree, 0);
	return sTree;
}

int main()
{
	int n;
	printf("Enter the no of elements : ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the elements : ");
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	Node *sT = buildST(n, a);
	printf("Sum = %d\n", getSum(sT, n, 0, n-1));
	printf("Enter 1 query (left and right index) : ");
	int l, r;
	scanf("%d%d", &l, &r);
	printf("Sum from %d to %d index = %d\n", l, r, getSum(sT, n, l, r));
	printf("Enter update index and value : ");
	int index, val;
	scanf("%d%d", &index, &val);
	updateValue(n, a, sT, index, val);
	printf("Sum = %d\n", getSum(sT, n, 0, n-1));
	free(sT);
	return 0;
}
