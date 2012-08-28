/*
 * A C library for many string operations. This library is named after the
 * original C string library. A valid string is considered to be an character
 * array of characters ended by the null character '\0'. 
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

#include "string.h"
#include "stdio.h"

//keeps track of the current string used in strtok
char *tok;

char *strcpy(char *dest, char *src)
{
	int i = 0;
	//copy until we hit null
	while(src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	//add the null pointer
	dest[i] = '\0';
	return dest;
}

/*
 * Compares two strings. Returns -1 if str1 < str2, 0 if str1 = str2, and 1 if
 * str1 > str2.
 */
int strcmp(char *str1, char *str2)
{
	int i = 0;	
	//breaks when both are the null character or one condition is met
	while(str1[i] != '\0' || str2[i] != '\0') {
		//check equalities
		if(str1[i] < str2[i]) {
			return -1;
		} else if (str1[i] > str2[i]) {
			return 1;
		} else {
			i++;
		}
	}
	//strings match
	return 0;
}

/*
 * Get a pointer to the first instance of c in str. Returns a pointer to "\0"
 * if c does not exist in str.
 */
char *strchr(char *str, char c)
{
	//create a pointer to null
	char *tmp = "\0";
	int i = 0;
	//search until we reach the end
	while(str[i] != '\0') {
		//check if we have found it yet
		if(str[i] == c) {
			return &str[i];
		}
		i++;
	}
	//never found
	return tmp;
}

/*
 * Get a pointer to the last instance of c in str. Returns a pointer to "\0"
 * if c does not exist in str.
 */
char *strrchr(char *str, char c)
{
	//create a pointer to null
	char *tmp = "\0";
	int i = 0;
	//search until we reach the end
	while(str[i] != '\0') {
		//check if we have found it yet
		if(str[i] == c) {
			return &str[i];
		}
		i++;
	}
	//never found
	return tmp;
}

/*
 * Get the length of str. A valid string is terminated by '\0'.
 */
int strlen(char *str)
{
	//count until we reach the end
	int i = 0;
	while(str[i] != '\0') {
		i++;
	}
	return i;
}

/*
 * Acts as a string tokenizer. When given a new string in str, it will search
 * for the next intance of 't' in 'str' and place everything before it into 
 * 'dest'. If no instance is found, '\0' is returned. To get multiple tokens
 * of the same string, initially make this call with the string, and then make
 * calls using '\0' as 'str' to get the next token. Passing a new 'str' will
 * start from the begining of that string.
 */
char *strtok(char *str, char t, char *dest)
{
	//counter
	int i = 0;

	//check if we have a new string
	if (str != '\0') {
		//copy the pointer
		tok = str;
	}

	//go through until we find an instance of t
	while(tok[i] != '\0') {
		//copy the current character
		dest[i] = tok[i];
		//check if we are done
		if(dest[i] == t) {
			//null terminate it
			dest[i] = '\0';
			//advance the pointer in our saved string
			tok += ++i;
			return dest;
		}
		i++;
	}
	//we found '\0' before t. If t == '\0', return what we found
	if (t == '\0') {
		//null terminate it
		dest[i] = '\0';
		//advance the pointer in our saved string
		tok += ++i;
		return dest;
	}

	//if we are here, we never found t
	return '\0';
}

int indexOf(char* str,char c) {
	int i;
	int l = strlen(str);
	for(i=0;i<l;i++)
	{
		if (str[i] == c)
			return i;
	}
	return -1;
}

int concat(char* a, char* b, char* r) {
	int i = 0;
	int j = 0;
	while(a[j] != '\0') {
		r[i] = a[j];
		i++;
		j++;
	}
	j=0;
	while(b[j] != '\0') {
		r[i] = b[j];
		i++;
		j++;
	}
	r[i] = '\0';
	return i;
}
