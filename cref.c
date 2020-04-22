// cref.c	A cross-referencer. Ex. 6-3 from K & R, also listing the count for each word.
// cref.c reads input from a file and examines how often each word is used.  Using the 
// tree in crTree.c, it creates & prints a table of all words > length 2 and not in the 
// "skippedWords" list, along with the number of times that word appears, and the line 
// numbers where it appears.

// First it prints directly from the tree, then it also writes the tree into an array,
// and prints it from the array, just for fun.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cref.h"
#include "binarySearch.h"
#include "intList.h"
#include "crTree.h"

#define MAXWORDLEN 100

// We won't count these words in our cross-referencing. 
// This array must be in alphabetical order!
static char *skippedWords[] = {"and", "for", "the"}; 
static int skippedWordsLen = 3;

// Some internal functions
static void printWordTree(CRTree *words);
static CRTree *crossReferenceMyFile(FILE *myFile);
static int getNextWord(char word[], FILE *myFile, int *linenum);

// The only function listed in the header file for outside use.  It prints the list
// twice: once from the tree, and once from an array. 
void printCrossReferenceList(FILE *inputFile){
	CRTree *root = NULL;
	WordArray *arr;
	int i, j, arrLen;

	// Organize the file's words into a tree, returning a pointer to the tree's root
	root = crossReferenceMyFile(inputFile);
	if (root == NULL) {
		fprintf(stderr, "I couldn't get data from the file.\n");
		return;
	}
	
	// Print the words in a table to stdout, beginning with the header line below:
	printf("Printing the tree...\n\n");
	printf("%20s %10s     %s\n","Word", "Count", "Line Numbers");
	printWordTree(root);

	// Write the tree info into an array, for easier handling, and just for fun.
	arr = turnTreeIntoArray(root, &arrLen);

	// Free the tree
	if (freeTree(root) == 0) printf("\n\nTree freed successfully!");

	// Print the array; should look identical to the printed tree.
	printf("\nPrinting the array...\n\n");
	printf("%20s %10s     %s\n","Word", "Count", "Line Numbers");
	for (i=0;i<arrLen;i++) {
		printf("%20.20s %10d       ", arr[i].word, arr[i].count);
		for (j=0;j< arr[i].count;j++) printf("%d ", arr[i].linenums[j]);
		printf("\n");
	}
	
	// Free the array
	if (freeArray(arr, arrLen) == 0) printf("\n\nArray freed successfully!\n\n");
}

// Recursive routine; Prints out the contents of a filled crTree.  Prints out the 
// words, the count of each word, and the line numbers on which each word is found, 
// in alphabetical order. treeptr needs to be the root (top) node of the tree.
static void printWordTree(CRTree *treeptr){
	if (treeptr != NULL){
	
		// If there's a left branch, that comes first alphabetically, so print that first.
		printWordTree(treeptr->left);
		
		// Print the word and the count
		printf("%20.20s %10d       ", treeptr->word, treeptr->count);

		// Print the list of line numbers
		// First rewind the list to the beginning, so we can print them in order
		treeptr->linenums = rewindList(treeptr->linenums);

		// then print them out, starting from the beginning of the list.
		printf("%d ", treeptr->linenums->num);  // print the first one
		while (treeptr->linenums->next){		// if there are more, print those too
			treeptr->linenums = treeptr->linenums->next;
			printf("%d ", treeptr->linenums->num);
		}
		printf("\n");
		
		// If there's a right branch, that comes next alphabetically.  Print that too.
		printWordTree(treeptr->right);
	}
}

// Adds the words from the file one by one to the tree. Goes through the entire file.
static CRTree *crossReferenceMyFile(FILE *myFile){
	CRTree *root = NULL;
	char word[MAXWORDLEN+1];
	int linenum = 1;

	while ((linenum = getNextWord(word, myFile, &linenum)) != EOF) 
		root = addWord(root, word, linenum); // always returns the tree's root
		
	return root;
}

/* Reads the next word from myFile.  It skips over words that are only 1 or 2 letters and 
   the words in the "skippedWords" array".  It reads an underscore as part of a word. If 
   there's a word larger than MAXWORDLEN, it will break it up into multiple words. It 
   returns the line number on which the word was found, or EOF. It does not handle words
   that span more than one line; end-of-line will be taken as the end of the word.*/
static int getNextWord(char *word, FILE *myFile, int *linenum){
	char c = 'a'; // initalize to any value other than EOF
	int i; 

	do { 					// If we get a word that is <3 characters long, or that is
		i = 0;				// in the "skippedWords" array, discard it and get another.
		word[0] = '\0';
		if (c == EOF) return EOF;

		// Add characters to our word until we get to EOF, or a non-alpha character besides an _
		// Abort if the word gets up to MAXWORDLEN.
		while (((c = fgetc(myFile)) != EOF) && (i < MAXWORDLEN) && (isalpha(c) || (c == '_')))
			word[i++] = tolower(c);	
		if (c == '\n') (*linenum)++;
		word[i] = '\0';
	} while ((i<3) || (binarySearch(word, skippedWords, skippedWordsLen) >= 0));
	
	return *linenum;
}

