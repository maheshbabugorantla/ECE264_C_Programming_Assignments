#include"answer02.h"

size_t my_strlen(const char * str)
{
	size_t string_len = 0; // Used to mesaure the length of the string
	
	int index = 0 ; // Used for the index of the 'str' array 		

	while(str[index] !='\0')
	{
		string_len += 1;
		index += 1;
	}
	
 return(string_len);
}

int my_countchar(const char * str, char ch)
{
	int char_count = 0; // Counts the No.of appearances of 'ch' in 'str'
	int index = 0; // Index of String 'str'
 
	while( str[index] != '\0')
	{
		if(str[index] == ch)
		{
			char_count += 1;
		}
		
		index += 1;
	}

	return(char_count);
}

char* my_strchr(const char * str, int ch)
{
	int index = 0; // Used as an Index to loop through the whole string	        
	/*char* str_new = "''"; 
	
	if(ch == '\\0')
	{		
		return(str_new);
	}*/

      	while(index <= (int)my_strlen(str))
	{
		if(str[index] == ch)
		{ 			
			return (char *)(&str[index]);			
		}
	
 		index += 1;
	}

	return(NULL);
}


char* my_strrchr(const char* str, int ch) // From the Right Side
{
	int index = (int)my_strlen(str); // Used as an Index to loop through the whole string	        
//	char* str_new = "''"; 
	
/*	if(ch == '\0')
	{		
		return('\0');
	}
*/
      	while(index>=0)
	{
		
		if(str[index] == ch)
		{ 			
			return (char *)(&str[index]);			
		}
	
 		index -= 1;
	}

	return(NULL);
}

char* my_strstr(const char* haystack, const char* needle)
{
	int mindex = 0 ; //Index for the Main String
	int subindex = 0; // Index for the Sub-String Needle	

     /* This below if is executed when the length of the needle is Zero */
	
	if((int)my_strlen(needle) == 0)
	{
	   return(char*)(&haystack[0]);
	}

    /* This below part is executed if the length of the needle is greater than Zero */	
	
	while(haystack[mindex] != '\0')
	{
		while((haystack[mindex] == needle[subindex])&&(needle[subindex] != '\0'))
		{
			mindex+= 1;
			subindex += 1;
			
			if(needle[subindex] == '\0')
			{
				return((char*)(&haystack[mindex - subindex]));			
			}
		} 

		subindex = 0; // Re-initialize substring Index if not found in the string.
		mindex += 1;  // Incrementing the 'haystack' string index
	}

	return(NULL); // This is returned if the String is not found in the 'HayStack'
} 

char* my_strcpy(char* dest,const char* src)
{

	int str_index = 0; // Used for both the 'dest' and 'src' String 

 	while(src[str_index] != '\0')
	{
		dest[str_index] = src[str_index];
		str_index += 1;
	}
		
		dest[str_index] = '\0';

	return(dest);
}
 /*
char * my_strdup(const char * src)
{
	size_t len = my_strlen(src);
	char * dest = malloc(sizeof(char) * (len + 1));
    	my_strcpy(dest, src);
	return dest;
} */

char* my_strcat(char* dest, const char* src)
{
	int str_index = my_strlen(dest); // Used for 'dest' string 
	int index = 0; // Used for 'src' string

	while(src[index] != '\0')
	{
		dest[str_index] = src[index]; 
		index += 1;
		str_index += 1;
	}

	dest[str_index] = '\0';

	return(dest);

}

int my_isspace(int ch)
{
	return(ch == ' '|| ch == '\f'|| ch == '\n' || ch == '\t'|| ch == '\v' || ch == '\r');
}

int my_atoi(const char* str)
{
	int ret = 0; // Used to get the integer in the first part of the string 
	int flag = 0; // Used to Check if the number is 'Negative"
	
	while(my_isspace(*str)) str++;
	
	if(*str == '-')
		{	
			flag = 1;
			str++;
		}	
	
	while((*str >= '0') && (*str<='9') && (*str != '\0'))	
	{
		ret *= 10;
		ret += (*str - '0');
		str ++;
	}

	if(flag == 1)
	{
		return(-ret);
	}
	
	return(ret);
}
		
			
