#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

//this function inserts the newNode at the end of the linkedList
void insertTail(slist* list, int data)
{
	//---- create new node
	struct node* newnode;
	newnode = malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	
	
	//initializes the head and tail of the linkedlist if it hasn't been already
	if (list->head == NULL) {
		list->head = newnode;
		list->tail = newnode;
	}
	
	//whatever the current tail is, want its "next" to point to newNode.
	//that way the tail doesn't get lost when it gets replaced
	list->tail->next = newnode;
	//now want the newNode to become the tail
	list->tail = newnode;

	
}

//this function wil free up memory in the linkedlist
void clearList(slist* list) {
	//begin by starting at the head of the linkedList
	struct node* tmp = list->head;
	//need another node to help keep track
	struct node* nextNode;
	while (tmp != NULL)
	{
		//set nextNode to point at next address of current node
		nextNode = tmp->next;
		//free up memory at the current node
		free(tmp);
		//updates the tmp to point to the element that comes after it
		tmp = nextNode;
	}
	//after clearing memory, set head and tail equal to NULL
	list->head = NULL;
	list->tail = NULL;

}

void printList(slist* list)
{
	struct node* tmp = list->head;
	while (tmp != NULL)
	{
		printf("%d->", tmp->data);
		tmp = tmp->next;
	}
	printf("NULL\n");
}