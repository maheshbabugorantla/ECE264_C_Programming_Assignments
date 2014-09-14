
#include"answer03.h"


char * strcat_ex(char** dest, int * n, const char * src)
{
	int min_length = strlen(*dest) + strlen(src) + 1;

	if((*n == 0) ||(*n < (min_length)))
	{	
		char* new_dest;
		new_dest = (char*)malloc(sizeof(char)*(1 + 2*(strlen(*dest) + strlen(src))));
		*n = (1 + 2*(strlen(*dest) + strlen(src)));
		strcpy(new_dest,(char*)*dest);
		free(*dest);
		*dest = new_dest; // memcpy(*dest,new_dest,*n)
		strcpy((char*)*dest,src);
		//free(new_dest);
	}

	else
	{
		strcpy((char*)*dest,src);
	}

	return(char*)(*dest);
}


//char * * explode(const char * str, const char * delims, int * arrLen)
//{
		


	
						
