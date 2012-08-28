/*
 * A C library contains useful functions many user program may use.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

#include "stdlib.h"
#include "math.h"

/*
 * This will swap the refernces of a and b.
 */
int swap(int *a,int *b)
{
	int temp = *b;
	b = a;
	*a = temp;
	return 0;
}

/*
 * Returns if the character is a numberic ASCII character. 
 */
int isNumeric(char c)
{
	return (c >= 48 && c <= 57);
}

/*
 * Convert the numeric string 'a' to an integer.
 */
int atoi(char* a) {
	char *digits = "0123456789\0";
	int i = 0;
	int l = 0;
	int s = 0;
	int c = 0;
	int start = 0;
	int end = 0;
	
	while (!isNumeric(a[i])) {
		i++;
	}
	
	start = i;
	l -= i;
	
	while (isNumeric(a[i])) {
		i++;
	}
	
	end = i;
	i = start;
	
	l = end - start - 1;
	
	while (i < end) {
		int val = indexOf(digits,a[i]);
		int power = pow(10,l-c);
		s += (val*power);
		i++;
		c++;
	}
	return s;
}

/*
 * Convert the integer i into a string copied into c
 */
int itoa(int i,char* c)
{
	//a counter for the current power of 10
	int power = 1;
	int index = 0;
	
	//if it is negative, print a '-' sign first
	if(i < 0) {
		//ASCII for '-'
		c[index] = 0x2D;
		//reverse the value
		i = -i;
		index++;
	}
	
	//find the greatest power of 10 not greater than i
	while (power <= i/10) {
		power = power * 10;
	}
	
	//keep going down by powers of 10 to get the left most digit at a time
	for (power; power >= 1; power = power / 10) {
		//integer division will give the left most digit 
		int n = i / power;
		
		//get its ASCII value
		if (n == 0)
			c[index] = 0x30;
		else if (n == 1)
			c[index] = 0x31;
		else if (n == 2)
			c[index] = 0x32;
		else if (n == 3)
			c[index] = 0x33;
		else if (n == 4)
			c[index] = 0x34;
		else if (n == 5)
			c[index] = 0x35;
		else if (n == 6)
			c[index] = 0x36;
		else if (n == 7)
			c[index] = 0x37;
		else if (n == 8)
			c[index] = 0x38;
		else if (n == 9)
			c[index] = 0x39;
		//get the remainder
		i = mod(i, power);
		index ++;
	}
	c[index] = 0x00;
	return index;
}
