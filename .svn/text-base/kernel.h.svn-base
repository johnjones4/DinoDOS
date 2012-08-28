/*
 * This is the main header file for the dinoDOS kernel. 
 *
 * Authors: John Jones and Russell Toris
 * Version: 0.4 March. 28, 2010
 */

#ifndef KERNEL_DEF
#define KERNEL_DEF
typedef char byte;
typedef int bool;

#define TRUE 1;
#define FALSE 0;
#define NULL '\0'

struct dirEntry {
	char name[6];
	byte sector[26];
};

struct directory {
	struct dirEntry entries[16];
};
#endif
int handleInterrupt21(int ax, int bx, int cx, int dx);
void handleTimerInterrupt(int segment, int stackPointer);
void returnFromTimer(int segment, int stackPointer);
void printLogo();
void startupSequence();
