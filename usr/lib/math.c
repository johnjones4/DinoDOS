/*
 * A C library for many math operations. This library is named after the
 * original C math library.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

#include "math.h"


/*
 * Method to compute x to the power of y. Returns -1 if y is negative. 
 */
int pow(int x, int y)
{
	//check the case of y = 0
	if (y == 0) {
		return 1;
	} else if (y > 0) {
		return x * pow(x, y-1);
	} else {
		//cannot compute negative exponents
		return -1;
	}
}

/*
 * Method that computes and returns a mod b.
 */
int mod(int a, int b)
{
	//go until we find the remainder
	while (a >= b) {
		a -= b;
	}
	return a;
}

/*
 * Get the absoulte value of i.
 */
int abs(int i)
{
	if (i < 0)
		return -i;
	else
		return i;
}

/*
 * Get the maximum of x and y
 */
int max(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}

/*
 * Get the minimum of x and y
 */
int min(int x, int y) {
	if (x < y)
		return x;
	else
		return y;
}
