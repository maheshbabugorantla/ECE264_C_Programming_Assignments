

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"answer03.h"

#define MEMORY 25

int main(int argc, char** argv)
{
	//const int size = 25;
	char* dest = "Mahesh";
	//char** dest1 = &dest;
	int size = strlen(dest);
	char* src = "Babu";

	printf("The String is %s \n\n",strcat_ex(&dest,&size,src));

	return(EXIT_SUCCESS);
}






