// intList.h

#ifndef intList_h
#define intList_h

typedef struct intlistnode{ // a linked list of integers
	int num;
	struct intlistnode *next;
	struct intlistnode *prev;
} IntList;


IntList *attachIntNode(IntList *oldLast, IntList *newLast);
IntList *getNewIntNode(int num);
IntList *rewindList(IntList *inputPtr);
int freeIntList(IntList *list);

#endif
