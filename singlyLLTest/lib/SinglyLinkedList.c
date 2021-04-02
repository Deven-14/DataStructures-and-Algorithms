#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "singlyLinkedList.h"

extern int errno;

Node* newNode(void *data)
{
	Node *n = (Node*)malloc(sizeof(Node));
	
	if(n != NULL)
	{
		n->data = data;
		n->next = NULL;
	}
	
	return n;
}

SinglyLinkedList* newSinglyLinkedList()
{
	SinglyLinkedList *s = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
	
	if(s != NULL)
	{
		s->head = NULL;
		s->tail = NULL;
	}
	
	return s;
}

Iterator* newIterator(SinglyLinkedList **s)
{
	Iterator *i = (Iterator*)malloc(sizeof(Iterator));
	
	if(i != NULL)
	{
		if(*s != NULL)
		{
			i->curr = (*s)->head;
			i->s = s;
		}
		else
		{
			i->curr = NULL;
			i->s = NULL;
		}
	}
	
	return i;
}

int addHead(SinglyLinkedList *s, void *data)
{
	if(s == NULL)
		return errno;
	
	Node *newEle = newNode(data);
	if(newEle == NULL)
		return errno;
	
	if(s->head == NULL)
		s->head = s->tail = newEle;
	else
	{
		newEle->next = s->head;
		s->head = newEle;
	}
	
	return 0;
}

int addTail(SinglyLinkedList *s, void *data)
{
	if(s == NULL)
		return errno;
	
	Node *newEle = newNode(data);
	if(newEle == NULL)
		return errno;
		
	if(s->head == NULL)
		s->head = s->tail = newEle;
	else
	{
		s->tail->next = newEle;
		s->tail = newEle;
	}
	
	return 0;
}

int removeHead(SinglyLinkedList *s)
{
	if(s == NULL)
		return errno;
	
	if(s->head == NULL)
		return -1;
	
	Node *temp = s->head;
	
	if(s->head == s->tail)
		s->head = s->tail = NULL;
	else
		s->head = s->head->next;
	
	free(temp);
	
	return 0;
}

int removeTail(SinglyLinkedList *s)
{
	if(s == NULL)
		return errno;
	
	if(s->head == NULL)
		return -1;
	
	Node *last = s->tail;
	
	if(s->head == s->tail)//one ele
		s->head = s->tail = NULL;
	else
	{
		Node *curr = s->head;
		
		while(curr->next != last)
			curr = curr->next;
		
		curr->next = NULL;
		s->tail = curr;//**
	}
	
	free(last);
	
	return 0;
}

int removeData(SinglyLinkedList *s, void *key, int (*compare)(const void *, const void *))
{
	if(s == NULL)
		return errno;
	
	Node *curr = s->head, *prev = NULL;
	
	while(curr != NULL)
	{
		if(compare(curr->data, key) == 0)
		{
			if(curr == s->head)
			{
				if(s->head == s->tail)
					s->head = s->tail = NULL;
				else
					s->head = s->head->next;
			}
			else if(curr == s->tail)
			{
				prev->next = NULL;
				s->tail = prev;
			}
			else
				prev->next = curr->next;
			
			free(curr);
			
			if(prev == NULL)
				curr = s->head;
			else
				curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	
	return 0;
}

void emptySinglyLinkedList(SinglyLinkedList *s)
{
	if(s == NULL)
		return ;
	
	Node *curr = s->head, *temp = NULL;
	
	while(curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	
	s->head = NULL;
	s->tail = NULL;
	
}

void freeSinglyLinkedList(SinglyLinkedList **s)
{
	if(*s == NULL)
		return ;
	
	emptySinglyLinkedList(*s);
	
	free(*s);
	*s = NULL;
}


inline void start(Iterator *i)
{
	if(i != NULL && *(i->s) != NULL)
		i->curr = (*(i->s))->head;
	else
		i->curr = NULL;
}


inline bool end(Iterator *i)
{
	return (i == NULL || *(i->s) == NULL || i->curr == NULL);
}

inline void next(Iterator *i)
{
	if(i != NULL && *(i->s) != NULL && i->curr != NULL)
		i->curr = i->curr->next;
}

inline void* data(Iterator *i)
{
	return ((i != NULL && (*(i->s)) != NULL && i->curr != NULL) ? (i->curr->data) : NULL);
}


void freeIterator(Iterator **i)
{
	if(*i == NULL)
		return ;
	
	free(*i);
	*i = NULL;//so that once the it is freed we won't use it by mistake
}
