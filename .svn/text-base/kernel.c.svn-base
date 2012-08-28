/*
 * dinoDOS is a very basic and simple OS named after the cover of the course
 * textbook. This is the main kernel file. 
 *
 *
 * Authors: John Jones and Russell Toris
 * Version: 0.5 March. 28, 2010
 */

#define MAIN

#include "kernel.h"
#include "system.h"
#include "proc.h"
#include "usr/lib/string.h"

main()
{
	//call a few helpful functions at startup
	startupSequence();
	//load the shell
	interrupt(0x21, 0x04, "shell\0",0, 0);
	//start our infinite loop
	while(1);
}

/*
 * This function clears the screen, places the cursor at the top left, and 
 * prints the dinoDOS logo. This should be the first function to be called from
 * within main.
 */
void startupSequence()
{
	//used when waiting for enter to be pressed
	char tmp[0];

	//clear the screen
	clearScreen();
	//print the logo
	printLogo();
	//setup proc structures
	initializeProcStructures();
	//setup handling of interrupt 21
	makeInterrupt21();
	//setup timer interrupts
	makeTimerInterrupt();
	//wait for enter to be pressed
	printString("Welcome to dinoDOS v. 0.5! Press any key to begin.\0");
	getChar(); //waits a key
	//clear the screen again (removes logo)
	clearScreen();
}

/*
 * Prints an awesome logo in the center of the screen. 
 */
void printLogo()
{
	putStr("                ----------\0", 5, 20, 0x04);
	putStr("            ----           ----\0", 6, 20, 0x04);
	putStr("         ---          _____    ---\0", 7, 20, 0x04);
	putStr("        --           / /\\  \\_    --\0", 8, 20, 0x04);
	putStr("       -          __/  \\/     \\__   -\0", 9, 20, 0x04);
	putStr("      -      ____/         ______|   -\0", 10, 20, 0x04);
	putStr("     -    __/         _  /            -\0", 11, 20, 0x04);
	putStr("     -___/       ___/ \\ \\____         -\0", 12, 20, 0x04);
	putStr("     -          /      \\ \\----        -\0", 13, 20, 0x04);
	putStr("     -        /\\\\  _                  -\0", 14, 20, 0x04);
	putStr("      -     _/  \\\\/_   |-------|     -\0", 15, 20, 0x04);
	putStr("      -    /     \\_    |dinoDOS|     -\0", 16, 20, 0x04);
	putStr("        --/            |-------|  --\0", 17, 20, 0x04);
	putStr("         ---            v. 0.5 ---\0", 18, 20, 0x04);
	putStr("            ----           ----\0", 19, 20, 0x04);
	putStr("                ----------\0", 20, 20, 0x04);
}


/*
 * Handle an int 21 based on the value of ax. -1 is returned if an invalid ax
 * is given.
 */
int handleInterrupt21(int ax, int bx, int cx, int dx)
{
	if (ax == 0x00) {
		/*
  		 * Print the string given by bx and returns the number of
		 * characters printed
		 */
		return printString(bx);
	} else if (ax == 0x01) {
		/*
		 * Wait for a line to be entered as input and place it into bx
		 * returns the number of characters read. cx is the max buf size
		 */
		return readLine(bx, cx); 
	} else if (ax == 0x02) {
		/*
		 * Read the sector given by the absolute sector cx and place it
		 * into the buffer at bx. Returns 1.
		 */
		return readSector(bx, cx);
	} else if (ax == 0x03) {
		/*
		 * Read the file with the name at bx, into the buffer at cx. The
		 * value at dx is the max buffer size. This returns -1 if the
		 * file does not exist, or the number of sectors read.
		 */
		return readFile(bx, cx, dx);
	} else if (ax == 0x04) {
		/*
		 * Execute the program with name given by bx. If there are no 
		 * free memory segments, -2 is returned. -1 is returend if the 
		 * file name does not exist. -3 is returned if the file is not 
		 * marked as executable. Otherewise 1 is returned. The cx value 
 		 * is used to decicde if all other processes should wait for 
		 * this program to terminate before continuing. 0 will disable 
		 * this function, and anything greater will enable it. The 
		 * 'dx' is used to schedule priority to a process within the
		 * ready queue. The default is 0. Note, this queue does NOT
		 * protect against process starvation. Negative numbers will 
		 * default to 0. Use priorities wisely.
		 */
		return executeProgram(bx, cx, dx);
	} else if (ax == 0x05) {
		/*
		 * Terminate the running program and return to the shell.
		 */
		terminate();
	} else if (ax == 0x06) {
		/*
		 * Writes a sector with the 512 byte buffer in bx to the sector
		 * given in cx. 1 is returned.
		 */
		return writeSector(bx, cx);
	} else if (ax == 0x07) {
		/*
		 * Delete the file with the name given by bx. If the file was
		 * found and deleted, 1 is returned. If the file name cannout be
		 * found, -1 is returned.
		 */
		return deleteFile(bx);
	} else if (ax == 0x08) {
		/*
		 * Write the file with the name given in bx, file contents in
		 * the buffer at cd, and number of sectors in dx. If that file
		 * name already exists, it will overwrite that file. This will 
		 * return -1 if the disk directory is full, -2 if the disk was
 		 * filled while writing the file, or the number of sectors
 		 * written.
 		 */
		return writeFile(bx, cx, dx);
	} else if (ax == 0x09) {
		/*
		 * Have the running program give up the remainder of its time
		 * slice. 
 		 */
		return yield();
	} else if (ax == 0x0A) {
		/*
		 * Print a list of currently running processes.
		 */
		showProcesses();
	} else if (ax == 0x0B) {
		/*
		 * Kill the process with the given segment. Returns 1 if 
 		 * successful and -1 if there is no porcess with the given
		 * segment. The segment should be in bx.
 		 */
		return kill(bx);
	} else if (ax == 0xA0) {
		/*
		 * Create a symbolic link. This will return -1 if the file to
		 * link to does not exist, -2 if the disk directory is full, or
		 * 1 if it was sucessful.
		 */
		return makeSymLink(bx, cx);
	} else if (ax == 0xA1) {
		/*
		 * Sleep for the amount of seconds in bx.
		 */
		sleep(bx);
	} 
	else if (ax == 0xB1) {
		/*
		 * Clear the screen.
		 */
		clearScreen();
	} else if (ax == 0xA2) {
		/*
		 * Get the next character read in. This is type byes. The ASCII
		 * value and scan code.
		 */
		return getChar();
	} else if (ax == 0xA3) {
		/*
		 * Print the int in bx to to screen.
		 */
		return printInt(bx);
	} else {
		/*
		 * Invalid ax value.
		 */
		return -1;
	}
	return 1;
}

void handleTimerInterrupt(int segment, int stackPointer)
{
	int i;
	setKernelDataSegment();
	//update the sleep timers of all SLEEPING pcbs
	for(i=0;i<8;i++) {
		if(pcbPool[i].state == SLEEPING) {
			pcbPool[i].sleepCount--;
			//now check if we can place it back to the ready queue
			if(pcbPool[i].sleepCount <= 0) {
				pcbPool[i].state = READY;
				addToReady(&pcbPool[i]);
			}
		}
	}
	
	//check if the queue is empty
	if(readyHead == NULL) {
		//mark idle as running
		running = &idleProc;
	}
	
	//save the segment
	running->segment = segment;
	//save the stack pointer
	running->stackPointer = stackPointer;

	//mark it as ready add it to the tail if it is not defunct or SLEEPING
	if(running->state != DEFUNCT && running->state != SLEEPING) {
		running->state = READY;
		addToReady(running);
	}
	
	//get the next PCB that is not defunct or sleeping
	running = removeFromReady();
	while(running->state == DEFUNCT || running->state == SLEEPING) {
		running = removeFromReady();
	}

	//check if we are waiting to return (dont change running)
	if(wait_segment > 0)  {
		while(running->segment != wait_segment && running != &idleProc) {
			//put the old one back
			addToReady(running);
			running = removeFromReady();
		}
	}
	//set it as running
	running->state = RUNNING;
	returnFromTimer(running->segment, running->stackPointer);
	restoreDataSegment();
}
