// crTree.c - Code for a specialized tree that holds words with the associated count 
// of how many times that word appears and the linenumbers where it appears.  Useful 
// for creating a cross-reference list of the words in a file.  

// Once the tree has been filled, there is code to write it into an array format.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intList.h"
#include "crTree.h"

static int arrayIndex;	// Internal use only
static CRTree *getNewCRTreeNode(char *word, int linenum);
static int treeToArray(CRTree *tree, WordArray *arr, int Nwords);
static int countWords(CRTree *tree);

/* Adds word to the tree.  Looks for the word in nodeptr; if the nodeptr is not 
   initialized, it allocates space for it and places the word in it.  If nodeptr 
   already exists and the word is there, it ups the count and records the line #; 
   if the nodeptr already exists but it contains a different word, it passes word
   down the tree to the right or left according to alphabetical order.  (aa's on 
   the far left)  !!nodeptr must be the root of the tree!!  */
CRTree *addWord(CRTree *nodeptr, char *word, int linenum){
	int compareResult;

	if (nodeptr == NULL) {  // then we need to allocate space for a new node, and place word in it
		nodeptr = getNewCRTreeNode(word,linenum);
	} else if ((compareResult = strcmp(word, nodeptr->word)) == 0){ 
		nodeptr->count++;  // The word is already in the tree, so up its count 

		// attach a new linenum to the linenum list, with num = linenum
		nodeptr->linenums = attachIntNode(nodeptr->linenums, getNewIntNode(linenum));
	}									
	else if (compareResult < 0)
		nodeptr->left = addWord(nodeptr->left, word, linenum);
	else
		nodeptr->right = addWord(nodeptr->right, word, linenum);
	return nodeptr;	
}

// Malloc & initialize a new CRTree
static CRTree *getNewCRTreeNode(char *word, int linenum){
	CRTree *newNode;
	int wordLen;

	if ((newNode = (CRTree *)malloc(sizeof(CRTree))) == NULL) return NULL;
	if (newNode != NULL){
		wordLen	= strlen(word);
		if ((newNode->word = (char *)malloc((wordLen+1) * sizeof(char))) == NULL) return NULL;
		memcpy(newNode->word, word, wordLen + 1); 
		//newNode->word = strdup(word);
		newNode->count = 1;
		newNode->linenums = getNewIntNode(linenum);
		newNode->right = newNode->left = NULL;
	}
	return newNode;
}

// Counts the number of words in the tree.
static int countWords(CRTree *tree){
	int count = 0;

	if (tree != NULL){
		count += countWords(tree->left);	// Count all the words to the left
		count++;							// Count the present word
		count += countWords(tree->right);	// Count all the words to the right
	}
	return count;
}

// You have to send the root of the tree to this as input.
int freeTree(CRTree *tree) {

	if (tree == NULL) return -1;

	if (tree->left) freeTree(tree->left); 	//Free the left branch
	if (tree->right) freeTree(tree->right);	//Free the right branch
	free(tree->word);						//Free the current node
	freeIntList(tree->linenums);
	free(tree);
	return 0;
}

// Assuming the tree is all filled out, we can then write it into a simpler array, 
// in alphabetical order.  Fills in arrLen with the length of the array.
WordArray *turnTreeIntoArray(CRTree *tree, int *arrLen){
	int Nwords;
	WordArray *arr;

	*arrLen = 0;
	if (tree == NULL) return NULL;

	// Count how many words we have, and size our array accordingly
	Nwords = countWords(tree);			
	
	arr = (WordArray *)malloc(Nwords * sizeof(WordArray));
	if (arr == NULL) return NULL;
	
	arrayIndex = 0;		// Initialize the static array counter
	if (treeToArray(tree, arr, Nwords) != Nwords)
		fprintf(stderr, "Somehow we lost some words.\n");

	*arrLen = Nwords;
	return arr;
}


// Recursive routine to take the info our of tree and write it into arr. 
// It assumes the number of 
// nodes in the tree has already been counted, and that that # of elements have already
// been allocated in arr.  It allocates new space for the variable portions of each
// array element, so that when we're done we can delete the tree and the array will 
// still be there. It returns the total # words added to the array.  Static variable
// arrayIndex keeps track of where we are in the array.  Must be set (to 0) before you 
// call treeToArray the first time.  I believe that since we need to keep an accurate
// index as we go, this needs to be static.  If we just needed the final tally at the 
// end, it could be internal as in "countWords" above.
static int treeToArray(CRTree *tree, WordArray *arr, int Nwords){
	int wordLen, i;

	if (tree == NULL) return 0;
		
	// If there's a left branch, that comes first alphabetically, so write that 
	// into the array first.
	if ((treeToArray(tree->left, arr, Nwords)) < 0) return -1;  // Error

	if (arrayIndex >= Nwords) {  // Error
		fprintf(stderr, "The array is too small for the tree!\n");
		return -1;
	}
	
	// Write the contents of the current tree node into the next array element 
	wordLen = strlen(tree->word);
	if ((arr[arrayIndex].word = (char *)malloc((wordLen + 1) * sizeof(char))) == NULL) {
		fprintf(stderr, "Couldn't allocate space for a word.\n");
		return -1;
	}
	memcpy(arr[arrayIndex].word, tree->word, wordLen+1);
	arr[arrayIndex].count = tree->count;

	// Write the list of line numbers
	// First make space for them
	if ((arr[arrayIndex].linenums = (int *)malloc(tree->count * sizeof(int))) == NULL) {
		fprintf(stderr, "Couldn't allocate space for linenums.\n");
		return 0;
	}
	// Rewind the list to the beginning
	while (tree->linenums->prev) tree->linenums = tree->linenums->prev;

	// Write them to the array, starting from the beginning of the list.
	for (i=0; i<tree->count; i++) {
		arr[arrayIndex].linenums[i] = tree->linenums->num;
		if (tree->linenums->next) tree->linenums = tree->linenums->next;	// We don't want
														// tree->linenums to end up null
	}
	
	(arrayIndex)++;
	
	// If there's a right branch, that comes next alphabetically.  Write that too.
	treeToArray(tree->right, arr, Nwords);
	
	return arrayIndex;
}

int freeArray(WordArray *arr, int len){
	int i;
	
	for (i=0;i<len;i++){
		free(arr[i].word);
		free(arr[i].linenums);
	}
	free(arr);	
	return 0;
}
