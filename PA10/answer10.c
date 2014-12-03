#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"answer10.h"
#include<inttypes.h>

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



typedef struct review
{
	int no_reviews;
	long int offset; // For the reviews.tsv
}ReviewNode;


typedef struct location
{	
	struct location* next;
	long int offset; // For the businesses.tsv
	int bus_id; // Id of a Business's different Location
	ReviewNode reviews;
	
}LocationNode;	


typedef struct business
{
	//BusinessNode* Root = NULL;
	struct business* Left; 
	struct business* Right;
	LocationNode* location;
	char* BusinessName;
	
}BusinessNode;	 


typedef struct YelpDataBST
{
	BusinessNode* BNode;		
}YelpData;


BusinessNode* create_business(char* businessname)
{
	BusinessNode* busNode = malloc(sizeof(BusinessNode)); // Have to allocate memory for the Business Node 
	
	busNode -> BusinessName = strdup(businessname); // strdup is done in another function 
	busNode -> Left = NULL; // Left Branch of the Binary Tree.
	busNode -> Right = NULL; // Right Branch of the Binary Tree.
	busNode -> location = NULL; // Used for storing the Address of different locations of a single business.
	
	return(busNode);
}

LocationNode* create_Location(long int bus_offset, long int rev_offset, int count,int business_id)
{
	LocationNode* locNode = malloc(sizeof(LocationNode));	
	locNode -> offset = bus_offset;
	locNode -> next = NULL;
	locNode -> bus_id = business_id;
	(locNode -> reviews).offset = rev_offset;
	(locNode -> reviews).no_reviews = count;
	
	return locNode;
}

/* The Below Function is Used to insert the entering node at the End. */

LocationNode* Location_list(LocationNode* head,long int bus_offset,long int rev_offset,int count,int business_id)
{
	if(head == NULL)
	{
		return(create_Location(bus_offset,rev_offset,count,business_id));
	}
	
	head -> next = Location_list(head -> next, bus_offset,rev_offset,count,business_id);	
		
	return(head);
}


// This is to print the Reviews of the Each Independent Business location.
void print_Locations(LocationNode* head, const char* filename_bus,const char* filename_rev)
{
	FILE* fp_bus = fopen(filename_bus,"r"); // for Businesses.tsv
	FILE* fp_rev = fopen(filename_rev,"r"); // For Reviews.tsv 

	char* str_bus = malloc(sizeof(char)* 6000); // Used to read and Print the address of the business Location.
	char* str_rev = malloc(sizeof(char)* 6000); // Used to read and print the review of the business Location.
	int count_rev = 0; // For printing all the reviews.
	//long int offset_rev = 
	
	while(head != NULL)
	{
		fseek(fp_bus,head -> offset,SEEK_SET); // makes the File Pointer Read at the offset from the beginning of the file.
 	
 		if(fgets(str_bus,6000,fp_bus) != NULL)
 		{
 			printf(" %s \n\n",str_bus); // Prints the Business Name 
 			
 			count_rev = (head -> reviews).no_reviews; // Gets the no.of reviews. 				
 		
 			fseek(fp_rev,(head -> reviews).offset,SEEK_SET);
 			
 			if(fgets(str_rev,6000,fp_rev) != NULL)
 			{
 			
 				// This Below loop is used to print the reviews of a business Location.
 				while(count_rev > 0)
 				{
 					printf("\n	%s\n",str_rev); // Prints review from a specific Customer.
 					fseek(fp_rev,1 + (int)(floor(log10(head -> bus_id)) + 1),SEEK_CUR); 
 					fgets(str_rev,6000,fp_rev);
 					count_rev -= 1;
 				}	 
 			}
 		
 	//	printf("Offset is %ld",head -> offset);
 		}
 		
 		head = head -> next;
	}

	free(str_bus); // Have to free this
	free(str_rev); // Have to free this...
	fclose(fp_bus);
	fclose(fp_rev);
}

// CREATING THE BUSINESS BINARY TREE
BusinessNode* create_BST(char* business, BusinessNode* root,long int bus_offset,long int rev_offset, int count,int business_id)
{
	if(root == NULL)
	{
		BusinessNode* bus_node = create_business(business); // This Business Node has to created first.
		bus_node -> location = Location_list(bus_node -> location,bus_offset,rev_offset,count,business_id); // Location is created pointing from that Business Location.
		return bus_node; // Creates and Inserts the Node at the NULL.
	}
	
	// Here We add the Address of the Business Location(Offset in businesses.tsv File) to the location linked list (Because We do not need to add the same business name)
	
	if(strcmp(business , root -> BusinessName) == 0) 
	{ 
		root -> location = Location_list(root -> location,bus_offset,rev_offset,count,business_id);	
	} 
	
	if(strcmp(business , root -> BusinessName) < 0)
	{
		root -> Left = create_BST(business,root -> Left,bus_offset,rev_offset,count,business_id); // Inserts the Node in the Left Side of the Binary Tree.
	}
	
	if(strcmp(business , root -> BusinessName) > 0)
	{
		root -> Right = create_BST(business, root -> Right,bus_offset,rev_offset,count,business_id); // Inserts the Node in the Right Side of the Binary Tree.
	}
		
	return(root);	
}

void print_tree(BusinessNode* Root,const char* filename1,const char* filename2)
{
	if(Root == NULL)
	{
		return;
	}
	

	print_tree(Root -> Left,filename1,filename2); // Prints the Left Side of the Tree

	printf("\n\nThe Business Name is %s at ",Root -> BusinessName);

	print_Locations(Root -> location,filename1,filename2);

	print_tree(Root -> Right,filename1,filename2); // Print the Right Side of the Tree

	//fclose(fp);	

}

// Destroying the Location List

void destroy_Loclist(LocationNode* location)
{
	while(location != NULL)
	{
		LocationNode* locpointer = location -> next;
		free(location);
		location = locpointer;
	}
}

void destroy_BST(BusinessNode* Root)
{
	if(Root == NULL)
	{
		return;
	}
	
	// Destroys the Left Part of the Tree
	destroy_BST(Root -> Left);
	
	// Destroys the Right part of the Tree
	destroy_BST(Root -> Right); 
	
	destroy_Loclist(Root -> location);
	free(Root -> BusinessName);
	free(Root);

	return;
}

YelpData* readfile(const char* busfilename, const char* revfilename)
{
	FILE* fp1 = fopen(busfilename,"r");
	FILE* fp2 = fopen(revfilename,"r");
	
	YelpData* BusinessData = malloc(sizeof(YelpData));
	
	//fclose(fp2); // Shift it to the Bottom Once Done Constructing the Whole BST and Location Nodes Pointing. 
	
	char* str1 = malloc(sizeof(char)*6000);
	char* str2 = malloc(sizeof(char)*6000); // For Reviews.tsv
	
	BusinessNode* BST = NULL; // Initialize it to NULL.

	int len1 = 0;
	int len2 = 0;
	
	long int posbus = ftell(fp1); // File Pointer Position for the Businesses.tsv
	long int posrev = ftell(fp2); // File Pointer Position for the Reviews.tsv
		 
	int ind1 = 0; // For Business
	int ind2 = 0; // For Reviews
	int count = 0; // No.of Reviews
	
	while(!feof(fp1))
	{			
		 fgets(str1,6000,fp1);
		 
		 if(feof(fp1))
		 {
		 	break;
		 }
		 
		 char** strArr1 = explode(str1,"\t",&len1);
		 		 
		 //char* business = strArr[1]; // This gives the Business Name and Need not malloc the 'business' because malloc is done in explode. 
		 int business_id = atoi(strArr1[0]); // To get the business ID
		 long int bus_offset = posbus + strlen(strArr1[0]) + strlen(strArr1[1]) + 2; // Used to get the Offset of the Address Location in the File.
		 long int rev_offset = 0;	
		
		// This Below Loop is used to get the offset the review and the no.of reviews.
		 while(fgets(str2,6000,fp2)!= NULL)
		 { 	
		 	char** strArr2 = explode(str2,"\t",&len2);
		 	rev_offset = posrev + strlen(strArr2[0]) + 1;
		 			 		
		 	if(strcmp(strArr2[0],strArr1[0]) == 0)
		 	{
				count += 1;				 
		 
			 	for(ind2 = 0; ind2 < len2; ind2++)
			 	{
			 		free(strArr2[ind2]);
			 	}
			 	
			 	free(strArr2);
			 }
			 
			 // This is used to break if the Business ID is greater than the Required BusinessID 
			 else
			 {
			 
			 	//if(strlen(str2) > 0)
			 	//{
			 	fseek(fp2,-strlen(str2),SEEK_CUR); // This Brings the File Pointer to the beginning of the Reviews of a Business Location.
				//}
				
				/*else
				{
					break;
				}*/
				
				posrev = ftell(fp2);
				
				for(ind2 = 0; ind2 < len2; ind2++)
			 	{
			 		free(strArr2[ind2]);
			 	}
			 	
			 	free(strArr2);	
			 	
			 	break; 	
			 } 	
			 	
		}
		
		BST = create_BST(strArr1[1],BST,bus_offset,rev_offset,count,business_id);
		
		count = 0;
		 
		for(ind1 = 0; ind1 < len1; ind1++)
		{
			free(strArr1[ind1]);
		}
			 
			 
		// Updating the Position of the File Pointer
		posbus = ftell(fp1); 
			  
		free(strArr1);
			
	}
	
	free(str1);
	free(str2);
	fclose(fp1);
	fclose(fp2);
	
	BusinessData -> BNode = BST;
	
	return BusinessData;
}



// CREATING YELP DATA BUSINESS TREE		 	
struct YelpDataBST* create_business_bst(const char* businesses_path,const char* reviews_path)
{
	return(readfile(businesses_path,reviews_path));
}


// GET THE REVIEWS OF A GIVEN BUSINESS LOCATION ( By Giving a Name 


void destroy_business_bst(struct YelpDataBST* bst)
{
	destroy_BST(bst -> BNode);
	free(bst); // Freeing the YelpData
	
	return;
}
	
int main(int argc, char** argv)
{
		
	YelpData* Root = create_business_bst("samplebus.tsv","samplerev.tsv");
	print_tree(Root -> BNode,"samplebus.tsv","samplerev.tsv");
	destroy_business_bst(Root);

	return(EXIT_SUCCESS);
}
	
	
	
	

