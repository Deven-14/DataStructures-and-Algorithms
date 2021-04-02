#include <stdio.h>
#define MAX_SIZE 10
int a[MAX_SIZE];
int top=-1;//underflow
void push(int data)
{
	if(top==MAX_SIZE-1)
	{
		printf("overflow");//or make the array a dynamic one and increase the size by times 2
		return;
	}
	a[++top]=data;
}
void pop()
{
	if(top==-1)
		return;
	top--;
}
int Top()
{
	if(top==-1)//don't need to check overflow condition coz, if it overflows element is not added
		return -1;
	return a[top];
}
int isEmpty()
{
	if(top==-1)
		return 1;
	return 0;
}
void print()
{
	for(int i=0;i<=top;i++)
		printf("%d ",a[i]);
}
int main()
{
	push(5);
	push(10);
	push(15);
	pop();
	print();
	return 0;
}