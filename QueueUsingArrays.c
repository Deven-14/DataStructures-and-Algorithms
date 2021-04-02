#include <stdio.h>
#define N 10
int a[N];
int front=-1;
int rear=-1;//empty
//linear implementation
/*
int isEmpty()
{
	if(front==-1 && rear==-1)
		return 1;
	return 0;
}
int isFull()
{
	int size=sizeof(a)/sizeof(a[0]);
	if(rear==size-1)
		return 1;
	return 0;
}
void enQueue(int data)
{
	if(isFull())
	{
		printf("full");
		return;
	}
	if(isEmpty())
		front==rear==0;
	else
		rear++;
	a[rear]=data;
}
void deQueue()
{
	if(isEmpty())
	{
		printf("empty");
		return;
	}
	if(front==rear)
		front==rear==-1;
	else
		front++;
}
*/
//circular implementation
//current pos=i;
//next pos=(i+1)%N; eg, N=10, i=5, so next pos=6%10=6 coz 6 on dividing by 10 gives 6 as remainder, but if i=9 then next pos=10%10=0 i.e the next pos is the begining of the lop i.e i=0
//previous pos=(i-1+N)%N; "+N" so that the answer is always positive, eg i=5 then p=(4+10)%10=14%10=4; if i=0; then p=(-1+10)%10=9%10=9 i.e p=9 the previous ele in the cirular loop, if it was only (i-1)%N then -1%10=-1 so i-1+N
int isEmpty()
{
	if(front==-1 && rear==-1)
		return 1;
	return 0;
}
int isFull()
{
	if((rear+1)%N==front)
		return 1;
	return 0;
}
void enQueue(int data)
{
	if(isFull())
	{
		printf("full");
		return;
	}
	if(isEmpty())
		front=rear=0;
	else
		rear=(rear+1)%N;
	a[rear]=data;
}
void deQueue()
{
	if(isEmpty())
	{
		printf("empty");
		return;
	}
	if(front==rear)
		front=rear=-1;
	else
		front=(front+1)%N;
}
void print()
{
	if(isEmpty())//front==rear==-1
		return;
	for(int i=front;i<=rear;i++)//this print won't work for circular queues*************
		printf("%d ",a[i]);
}
int main()
{
	enQueue(5);
	enQueue(10);
	enQueue(15);
	deQueue();
	print();
	return 0;
}