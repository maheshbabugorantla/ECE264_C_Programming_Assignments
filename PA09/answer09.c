	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include"answer09.h"


char** explode(const char* str, const char* delims,int* arrLen)
{
	int num_delim = 0; // No. of delimiters in the string 'delims'
	int str_index = 0; // String Index

	// This Below loop is used find out how many delimiters are in the string 'delims'

	while(str[str_index] != '\0')
	{
		if(strchr(delims,str[str_index]) != NULL)
		{
			num_delim += 1;
		}
		
		str_index++;
	}

	char** strArr = malloc((num_delim + 1) * sizeof(char*)); // This Allocates spaces to create (num_delim + 1) strings.

	int strArr_count = 0; // Flag for the no.of strings that can be accomodated in strArr
	
	int last_ind = 0; // Used to get the position where a character is last found.	
		
	int i = 0; // Index to check the strlen of str
	
	while(i <= strlen(str))	
	{
		if(strchr(delims,str[i]) == NULL) 
		{
			i++;
		}
		
		else
		{		
			//if(i > last_ind)
			{
				 strArr[strArr_count] = malloc(sizeof(char)*(i - last_ind + 1));
				 memcpy(strArr[strArr_count],&str[last_ind],(i - last_ind)); 
       				 strArr[strArr_count][i - last_ind] = '\0';
	      			 strArr_count += 1; // Flag to exit the loop if all the memory is utilised

			}
			
			i++;	
			last_ind = i;	

		} 
	}

	
	*arrLen = num_delim + 1; // No.of Strings that are Returned.
	
	return(strArr);
}	


BusinessNode* create_node(char * stars, char * name, char * address)
{
	BusinessNode* BNode = malloc(sizeof(BusinessNode)); // Allocating the Size First
		//printf("Just malloced %p, for node '%s'\n", BNode, name);
	
	if(BNode == NULL)
	{
		//printf("\n\nMalloc for Creating the Node Failed\n\n");
		return(NULL);
	}

	BNode -> stars = stars;
	BNode -> name =  name;
	BNode -> address = address;
	BNode -> left = NULL;
	BNode -> right = NULL;

	return(BNode);
}




void print_tree(BusinessNode * tree)
{
	if(tree == NULL)
	{
		return;
	}
	
	// Printing in Order.
	print_tree(tree -> left);
	printf("\n\nRating: %s , Name: %s , Address: %s\n\n", tree -> stars, tree -> name, tree -> address);
	print_tree(tree -> right); 

}


void destroy_tree(BusinessNode * root)
{
	if(root == NULL)
	{
		return;
	}
	
	destroy_tree(root -> left);
	destroy_tree(root -> right);
	
	//printf("About to nuke %p, for node '%s'\n", root, root -> name);
	free(root -> stars);
	free(root -> name);
	free(root -> address);
	free(root); 
}



	// Idea Taken from Prof. Yung Lu's Text Book.
BusinessNode* tree_insert(BusinessNode * node, BusinessNode * root)
{
	if(root	== NULL)
	{
		return node;
	}
		
		/*if(strcmp(node -> name,root -> name) == 0)
		{
			return(root);
		}*/
	
	if(strcmp(node -> name, root -> name) <= 0)
	{
		root -> left = tree_insert(node, root -> left);
	}
	
	else
	{
		root -> right = tree_insert(node,root -> right);
	}
	
	return root;
}	 
	
BusinessNode* load_tree_from_file(char* filename)
{
	FILE* fp = fopen(filename,"r");
	//FILE* fp = fopen("shortfile.tsv","r");
	
	
	if(fp == NULL)
	{
		printf("\nERROR\n\n");
		return(NULL);
	}
	
	int len = 0;
	char* str = malloc(sizeof(char)*2048);
	char** strArr = NULL;
	int count = 0;
	
	BusinessNode* root = NULL; // The Root Node for the Binary Search Tree
	BusinessNode* node = NULL; // The Nodes that will be inserted later on.
	
	while(fgets(str,2048,fp)!= NULL)
	{
			//printf("\n\n %s \n\n",str);
	
		strArr = explode((const char*)str,"\t",&len);
	
			/*printf("**************************************\n\nStars: %s\n",strArr[0]);
			printf("\nName: %s\n",strArr[1]);
			printf("\nAddress: %s**************************************\n\n",strArr[2]); */
		
		count += 1; 
		
		if(len == 3)
		{	
			node = create_node(strArr[0],strArr[1],strArr[2]);
			root = tree_insert(node,root);
		}

		free(strArr);
	}
	
	
	free(str);
	fclose(fp);
	
	return(root);
} 

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	if(root == NULL)
	{
		// Cannot Find the Given Business Name
		return(NULL);
	}
	
	if(strcmp(root -> name,name) == 0)
	{
		return root;
	}
	
	if(strcmp(name,root -> name) < 0)
	{
		return(tree_search_name(name,root -> left));
	}
	
	return(tree_search_name(name,root -> right));
}
	
	/*int main(int argc, char** argv)
	{
		char* str = strdup("5.0");
		char* str0 = strdup("Random Name");
		char* str_0 = strdup("Root Address");
		 
		BusinessNode* root = create_node(str,str0,str_0);
	
		BusinessNode* node1;
		BusinessNode* node2;
		BusinessNode* node3;
		BusinessNode* node4;
	
		char* str1 = strdup("4.0");
		char* str2 = strdup("Another Name");
		char* str3 = strdup("Left Address");
		char* str4 = strdup("3.0");
		char* str5 = strdup("Other Name");
		char* str6 = strdup("Right Address");
		char* str7 = strdup("2.0");
		char* str8 = strdup("Another Left");
		char* str9 = strdup("Left Left");
		char* str10 = strdup("1.0");
		char* str11 = strdup("Other Right");
		char* str12 = strdup("Left Right");
		  
		node1 = create_node(str1,str2,str3);
		node2 = create_node(str4,str5,str6);
		node3 = create_node(str7,str8,str9);
		node4 = create_node(str10,str11,str12);
	
		//  Inserting all into the Binary Tree
		root = tree_insert(node1,root);
		root = tree_insert(node2,root);
		root = tree_insert(node3,root);
		root = tree_insert(node4,root);
	
		print_tree(root);
		destroy_tree(root);
	
		return(EXIT_SUCCESS);
	} */
	
	
