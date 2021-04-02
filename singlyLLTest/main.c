#include <stdio.h>
#include "singly_linked_list.h"

void print(Iterator *i)
{
	printf("The singly linked list is : ");
	for(start(i); !end(i); next(i))
		printf("%d, ", *(int*)data(i));
	printf("\n");
}

int compare(const void *x, const void *y)
{
	return (*(int*)x - *(int*)y);
}

int main()
{
	int data[10] = {1,2,3,4,4,5,6,7,7,9};
	SinglyLinkedList *s = newSinglyLinkedList();
	Iterator *i = newIterator(&s);
	
	for(int j = 0; j < 5; ++j)
	{
		addTail(s, &data[j]);
		print(i);
	}
	for(int j = 5; j < 10; ++j)
	{
		addHead(s, &data[j]);
		print(i);
	}
	
	removeTail(s);
	print(i);
	removeHead(s);
	print(i);
	int delData = 7;
	removeData(s, &delData, compare);
	print(i);
	freeSinglyLinkedList(&s);
	freeIterator(&i);
	return 0;
}