#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

//#define data(i) ((i != NULL && (*(i->s)) != NULL && i->curr != NULL) ? (i->curr->data) : NULL)

#include <stdbool.h>

struct node
{
	void *data;
	struct node *next;
};
typedef struct node Node;

struct singlyLinkedList
{
	Node *head;
	Node *tail;
};
typedef struct singlyLinkedList SinglyLinkedList;

struct iterator
{
	Node *curr;
	SinglyLinkedList **s;
};
typedef struct iterator Iterator;

Node* newNode(void *);
SinglyLinkedList* newSinglyLinkedList();

int addHead(SinglyLinkedList *, void *);
int addTail(SinglyLinkedList *, void *);

int removeHead(SinglyLinkedList *);
int removeTail(SinglyLinkedList *);
int removeData(SinglyLinkedList *, void *, int (*compare)(const void *, const void *));

void emptySinglyLinkedList(SinglyLinkedList *);
void freeSinglyLinkedList(SinglyLinkedList **);//**

Iterator* newIterator(SinglyLinkedList **);// ** coz, i want to know if *s i.e the SinglyLinikedList *s == NULL or it has a list assigned to it, if *s = null then no operations on the iterator will be performed

extern void start(Iterator *);
extern bool end(Iterator *);
extern void next(Iterator *);
extern void* data(Iterator *);

void freeIterator(Iterator **);//**

#endif
