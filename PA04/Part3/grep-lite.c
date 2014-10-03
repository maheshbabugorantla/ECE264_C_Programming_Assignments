#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv)
{

	/*********************** VARIABLE DECLARATION ********************************************************/
	
	FILE *fileptr; // File Pointer to read through all the contents of the File
	
	int index = 1; // 'argv' String Index  
	
	char str[2000]; // Used to get the Line from the File that matches the required Pattern

	char* c; // Used to read one line at a time from the input Buffer Stream

	int linecount = 0; // Used to get the Line Numbers where the Given "Pattern" is Found. 


       /********************************* USED TO CHECK IF THERE ARE INVALID NO.OF ARGUMENTS ARE PASSED *******************************************/

	if(argc < 3)
	{
		printf("Minimum of 2 Arguments along with Executable file name required \n\n"); // This is like "./exefilename (argv[1])[FILE1] (argv[2])[pattern in FILE1]"
		return(EXIT_FAILURE);
	} 


	/********************** This Loop below is Used to find out if there is an Argument called "--help" is passed as one of the Arguments.. *****************/

	for(index = 1; index<argc;index++)
	{
		if(!strcmp("--help",argv[index]))
		{
			printf("\n\nUsage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n\n");
	
		return(EXIT_SUCCESS);
		}
	}


	/************************************************* Actual Program's Algorithm **************************************************************/
		
								
	index = 1; // Reinitailzing the Index 

	fileptr = fopen(argv[index],"r"); // Opening the First File

	if(fileptr == NULL)
	{
		printf(" Sorry! File Cannot Be Opened %d\n\n",EXIT_FAILURE);
		return(EXIT_FAILURE);
	}

	
	// Initially Starting the Matching Patterns
	
	c = fgets(str,2000,fileptr);

	linecount++;

	if(strstr(c,argv[2]) != NULL)
		{
			puts(str);
		}


	/*************************** Continuing to see if there are Any other Similar Matching Patterns ****************************/
	
	while((c = fgets(str,2000,fileptr)) != NULL)
	{
		linecount++;
		if(strstr(c,argv[2]) != NULL)
		{		
			puts(str);			
		}
		
	}


	fclose(fileptr);

	return(EXIT_SUCCESS);
}
