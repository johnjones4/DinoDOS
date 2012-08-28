/*
 * This is a simple user program to test sleeping.
 *
 * Authors: John Jones and Russell Toris
 * Version: April. 13, 2010
 */

#include "lib/sys.h"
#include "lib/stdio.h"

void enableInterrupts();

main() {
	enableInterrupts();

	dino_print("Sleeping for 20(ish) seconds...\0");
	sleep(20);
	dino_print("I'm awake!\n\0");
	terminate();
}
