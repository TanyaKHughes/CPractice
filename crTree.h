// crTree.h

#ifndef crTree_h
#define crTree_h


typedef struct crnode{  	// cross-reference tree node
	char *word;
	int count;  			// the # of times the word appears in the document
	IntList *linenums;  	// a listing of all the line numbers in which the word appears
	struct crnode *left;  	// words alphabetically prior to the word appear here
	struct crnode *right;	// words alphabetically after the word appear here
} CRTree;

typedef struct {  			// After we've filled our tree, we'll turn it into an array.
	char * word;
	int count;
	int *linenums;
} WordArray;


CRTree *addWord(CRTree *nodeptr, char *word, int linenum);
WordArray *turnTreeIntoArray(CRTree *tree, int *arrLen);
int freeTree(CRTree *tree);
int freeArray(WordArray *arr, int len);

#endif
