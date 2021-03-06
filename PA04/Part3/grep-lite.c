#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char** argv)
{

	/*********************** VARIABLE DECLARATION ********************************************************/
	
	//FILE *fileptr; // File Pointer to read through all the contents of the File
	
	int index = 1; // 'argv' String Index  
	
	char str[2001]; // Used to get the Line from the File that matches the required Pattern

	char* c; // Used to read one line at a time from the input Buffer Stream

	int linecount = 0; // Used to get the Line Numbers where the Given "Pattern" is Found. 


	/********************** This Loop below is Used to find out if there is an Argument called "--help" is passed as one of the Arguments.. *****************/

	int invert = FALSE;
	int line = FALSE;
	int quiet = FALSE;


	for(index = 1; index<argc;index++)
	{
		if(!strcmp("--help",argv[index]))
		{
			printf("\n\nUsage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n\n");
	
		return(EXIT_SUCCESS);
		}
	}

	index = 0;

 	/******* PATTERN SWITCHES ******************/
	for(index = 1;index < argc;index++)
	{
	
		if(argv[index] == "-v" || (strcmp(argv[index],"--invert-match") == 0))
		{
			invert = TRUE;
		}
			
		if(argv[index] == "-n" || (strcmp(argv[index],"--line-number") == 0))
		{
			line = TRUE;
		}
			
		if(argv[index] == "-q" || (strcmp(argv[index],"--quiet") == 0))
		{
			quiet = TRUE;
		}
		
	 }


	/************************************************* Actual Program's Algorithm **************************************************************/
		
								
	index = 1; // Reinitailzing the Index 


	// Initially Starting the Matching Patterns
	
	c = fgets(str,2000,stdin);

	linecount++;

	if(strstr(c,argv[1]) != NULL)
		{
			puts(str);
		}


	/*************************** Continuing to see if there are Any other Similar Matching Patterns ****************************/
	
	while((c = fgets(str,2000,stdin)) != NULL)
	{
		linecount++;
		if(strstr(c,argv[1])!= NULL)
		{		
			puts(str);			
		}
		
	}


//	fclose(fileptr);

	return(EXIT_SUCCESS);
}
