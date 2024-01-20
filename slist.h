#pragma once
#ifndef slist_h
#define slist_h
#include <stdio.h>

//adopted from LinkedList notes from class slides

struct node
{
	int data;
	struct node* next;
};

struct singlylinkedlist
{
	struct node* head;
	struct node* tail;
};

//defines the linkedlist which will record the moves the players make
typedef struct singlylinkedlist slist;

void insertTail(slist* list, int data);
void clearList(slist* list);
void printList(slist* list);
#endif /* slist_h */