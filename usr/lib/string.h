/*
 * This is the header file for the string library. 
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

char *strcpy(char *dest, char *src);
int strcmp(char *str1, char *str2);
char *strchr(char *str, char c);
char *strrchr(char *str, char c);
int strlen(char *str);
char *strtok(char *str, char t, char *dest);
int indexOf(char* str,char c);
int concat(char* a, char* b, char* r);
