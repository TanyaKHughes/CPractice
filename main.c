// Main.c 
// Runs my little C practice routines.  Choose which of the routines you want to run using command line arguments.

/* Arguments are expected to be in the pattern -t -h -s string -c filename, or -ths string -c filename. 
   Any combination or order will work, as long as string directly follows the 's' and filename directly follows 'c'.
   Options are not case-sensitive.
	-h 			to print hello world
	-t 			to print a temperature conversion table
	-s string 	to search for the name of a fruit (string) in an array of fruit names 
	-c filename to print a cross-referenced list of the words from a file */

#include <stdio.h>
#include "temperatures.h"
#include "binarySearch.h"
#include "cref.h"
// testing

int canGetString(int *argc, char **argvptr[], char **stringptr);

int main(int argc, char *argv[]){

	int exitStatus = 0;
	int option;
	char *searchString, *filename;
	FILE *inputFile;
	struct {
		unsigned int hello 	: 1;
		unsigned int temp 	: 1;
		unsigned int search : 1;
		unsigned int cRef	: 1;
	} flags;

	flags.hello = flags.temp = flags.search = flags.cRef = 0;

	// Grab the arguments that start with "-" and set flags for them.
	while (--argc > 0 && (*++argv)[0] == '-') // running along picking out one argument at time, provided it starts with '-'
		while ((option = *++argv[0])) /*  This allows the user to enter options together like -ht.  Here the ++ moves us
									 to the next character of the argument we are looking at */
			switch (option) {
			case 'h':
			case 'H':
				flags.hello = 1;
				break;
			case 't':
			case 'T':
				flags.temp = 1;
				break;
			case 's':  // for this case we have to gather the string to search for immediately following the s
			case 'S':
				if (canGetString(&argc, &argv, &searchString)) flags.search = 1;	
				else {
					fprintf(stderr, "Capp Main.c: Error 2: If you want to search for a string, \
you need to give the string in the options.\n");
					exitStatus = 2;
				}
				break;
			case 'c':  // for this case we have to gather the filename to use immediately following the c
			case 'C':
				if (canGetString(&argc, &argv, &filename)) flags.cRef = 1;	
				else {
					fprintf(stderr, "Capp Main.c: Error 2: If you want to cross-reference a file, \
you need to give the filename in the options.\n");
					exitStatus = 2;
				}
				break;
			default:
				fprintf(stderr, "illegal option: %c\n", option);
				exitStatus = 1;
				break;
		}

	/* Do what's been requested. */
	if (flags.hello) printf("\n***Hello World!***\n\n");
	if (flags.temp){
		printf("***Temperatures***\n\n");	
		printTemperatures();
		printf("\n\n");	
	}
	if (flags.search) {
		printf("***String Search Results***\n\n");
		printSearchResults(searchString);
		printf("\n\n");
	}
	if (flags.cRef) {
		printf("***Cross Referencer Results***\n\n");
		if ((inputFile = fopen(filename, "r"))) {
			printf("Opening file %s... \n\n", filename);
			printCrossReferenceList(inputFile);
		}
		else {
			fprintf(stderr, "Couldn't open file %s.\n", filename);
			exitStatus = 3;	
		}
	}
	return exitStatus;
}

/* Picks off the next argument of *argvptr and points *stringptr to it.  Returns 1 if there	was 
   a next argument, 0 if not. Moves the argv pointer (*argvptr) to the end of that next argument. */
int canGetString(int *argc, char **argvptr[], char **stringptr) {
	int exitStatus = 0;

	if (*argc > 1) {	/* If there is another argument, assume it is the string. */
		(*argc)--;  // get to the string argument, assuming it's there
		(*argvptr)++;
		*stringptr = **argvptr;
		while (*++(*argvptr)[0]); // Here I'm running through the characters in the search string to get to the end
		--(*argvptr)[0];			// and then backing up one so we don't keep switching over the string characters.
		exitStatus = 1;
	}
	return exitStatus;
}


















//
//  main.c
//  CPractice
//
//  Created by Tanya Hughes on 3/18/20.
//  Copyright © 2020 Tanya Hughes. All rights reserved.
//

//#include <stdio.h>

//int main(int argc, const char * argv[]) {
    // insert code here...
//    printf("Hello, World!\n");
 //   return 0;
//}
