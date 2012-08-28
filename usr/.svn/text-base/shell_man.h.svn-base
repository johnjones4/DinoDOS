/*
 * This is the header file for the shell_man extension.
 *
 * Authors: John Jones and Russell Toris
 * Version: April 1, 2010
 */

#ifndef SHELL_DEF
#define SHELL_DEF

typedef char byte;
typedef int bool;

#define TRUE 1;
#define FALSE 0;
#define NULL '\0'

//Note: printing 0x08 moves the cursor back
//This macro prints 0x08, a space to clear, and 0x08 again
#define BACKSPACE char clr[4];clr[0]=0x08;clr[1]=' ';clr[2]=0x08;clr[3]=NULL;dino_print(clr);

//the max length for the input
#define MAX_INPUT 60

struct command_line {
	char cmd[60];
	char arg[60];
};

#include "lib/string.h"
#include "lib/stdio.h"
#endif

void print_man(char *cmd);
