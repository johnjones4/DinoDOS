/*
 * This is a simple user program to test multiprogramming.
 *
 * Authors: John Jones and Russell Toris
 * Version: April. 13, 2010
 */

#include "lib/sys.h"
#include "lib/stdio.h"

void enableInterrupts();

main() {
	int i,j,k;	
	enableInterrupts();

	for(i=0; i<500; i++) {
 		dino_print(".\0");
 		yield();
		for(j=0; j<1000; j++) {
			for(k=0; k<250; k++) {
			}
  		}
	}
	terminate();
}
