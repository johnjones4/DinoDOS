/*
 * A C library that functions as a wrapper for dinoDOS system calls. This
 * library has many system functions for executing and terminating programs
 * as well as rebooting the system.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

#include "sys.h"

/*
 * Execute a program with the given name if it exists. -1 is returned if
 * the program does not exist and -3 if it is not executable. -2 will be
 * returned if there are no free memory segments. This should also be given
 * a priority.
 */
int exec(char *prgm_name, int priority)
{
	return interrupt(0x21,0x04,prgm_name,0,priority);
}

/*
 * Execute a program with the given name if it exists. -1 is returned if
 * the program does not exist and -3 if it is not executable. -2 will be
 * returned if there are no free memory segments.  All other programs
 * are blocked when this function is called.
 */
int execWait(char *prgm_name)
{
	return interrupt(0x21,0x04,prgm_name,1,0);
}

/*
 * Terminate a user program and return the the shell.
 */
void terminate()
{
	return interrupt(0x21,0x05,0,0,0);
}

/*
 * Kill the process with the given segment. Returns 1 if successful and -1 if
 * there is no porcess with the given segment.
 */
int kill(int seg)
{
	return interrupt(0x21,0x0B,seg,0,0);
}

/*
 * Clears the entire shell in teletype mode. 
 */
void clear_scr() 
{
	//ask the kernel to clear the shell
	return interrupt(0x21, 0xB1,0,0,0);
}

/*
 * Have the calling process yield the remainder of its time slice.
 */
void yield()
{
	return interrupt(0x21,0x09,0,0,0);
}

/*
 * Print out a list of all of the proccesses and their segments.
 */
void proc()
{
	return interrupt(0x21,0x0A,0,0,0);
}

/*
 * Have the invoking process sleep for the specified number of seconds.
 */
void sleep(int seconds)
{
	return interrupt(0x21,0xA1,seconds,0,0);
}
