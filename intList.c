// A basic linked list of integers.  

#include <stdlib.h>
#include <stdio.h>
#include "intList.h"

// Attaches newLast to oldLast, so that newLast is now the last element of the linked list. 
// Returns newLast.
IntList *attachIntNode(IntList *oldLast, IntList *newLast){
	
	if ((oldLast == NULL) || (newLast == NULL)) return NULL;

	oldLast->next = newLast;
	newLast->prev = oldLast;

	return newLast;
}

// Malloc & initialize a new IntList node
IntList *getNewIntNode(int num){
	IntList *newNode;

	newNode = (IntList *)malloc(sizeof(IntList));
	if (newNode == NULL) {
		fprintf(stderr, "Couldn't allocate a new Int node.\n");
		return NULL;
	}
	newNode->num = num;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

// returns a pointer to the beginning of the list
IntList *rewindList(IntList *inputPtr){
	IntList *first;

	first = inputPtr;
	while (first->prev) first = first->prev;

	return first;
}

int freeIntList(IntList *list){
	IntList *tmp = NULL;
	
	if (list == NULL) return -1;

	// Rewind the list to the beginning
	while (list->prev)  list = list->prev;

	// free each node
	while (list){
		tmp = list;
		if (list->next) {
			list = list->next;
			free(tmp);
		}
		else {
			free(list);
			break;
		}
	}
	return 0;
}

