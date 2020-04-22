// binarySearch.c   A binary search implementation.  Searches in the constant char array arr for 
// a string entered by the user.

#include <stdio.h>
#include <string.h>
#include "binarySearch.h"

// arr must be in alphabetical order.
static char *arr[] = {"apple","banana", "blackberry", "blueberry", "grape", "kiwi", "marionberry", "nectarine", "orange", "peach", "pear", "persimmon", "pineapple", "plantain", "raspberry"};
static int arrLength = 15;

/* Performs and prints the results of a search on the above array. Searching for str in arr.  */
void printSearchResults(char *str){

		int i;

		// print out the data array we're searching through
		printf("Searching for string \"%s\" in array:\n", str);
		for (i=0;i< arrLength-1; i++)
			printf("%s  ", arr[i]);
		printf("%s\n\n", arr[arrLength-1]);

		// do the search
		i = binarySearch(str, arr, arrLength);

	 	if (i >=0) printf("Found string \"%s\" at position %d!\n", arr[i],i+1);
		else printf("Your fruit is not in the list!\n");
}

/*This routine looks for a string in an alphabetically-ordered (A-Z) string array. If it's found, it returns  
 the location of the matching string in the array (0 to L-1).  If it's not found, it returns -1.
 String is the string we're searching for, arr is the array, L is the length of the array */
int binarySearch(char *string, char *arr[], int L){
	
	/* We'll be splitting the array in half, determining which half might have the string, and then 
	working only with that half. */

	int middle = (L-1)/2; //the upper array index for the lower half of the current part of the array we're working with
	int compareResult, searchResult; //Some intermediate results
	
	if (L == 0) return -1;  // String not found
	if (string == NULL) return -1;  // Empty string

	
	/* First compare our string to the string in the middle of the array.  If it's correct, return that value. */
	if ((compareResult = strcmp(string,*(arr+middle))) == 0){
		return middle;	
	}
	/* In this case, our string, if it is to be found, will be found in the lower half of arr, so we continue
	   looking using only the lower half (not including the middle value). */
	else if (compareResult < 0)
		return binarySearch(string, arr, middle); 	

	/* In this case, our string, if it is to be found, will be found in the upper half of arr, so we continue
	   looking using only the upper half. */
	else {
		/* If we are using the upper half of the array, we'll need to add in the offset afforded by "middle" so as 
		   to return the actual position of the found string with respect to the initial array indices. */
		if((searchResult = binarySearch(string, arr+(middle+1), (L-1) - middle)) >=0)
			return middle + 1 + searchResult;

		/* If we have a negative value returned by binarySearch, that means we have searched all the members
				 of arr and have not found our string. */
		else  			
			return searchResult;
	}
}
