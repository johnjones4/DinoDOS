/*
 * This is the main header file for the main dinoDOS shell.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 04, 2010
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

struct dirEntry {
	char name[6];
	byte sector[26];
};

struct directory {
	struct dirEntry entries[16];
};

int interpret_cmd(char *str);
void print_argerror(char *cmd);
void print_help();
int read_input(char *buf, int max);
int execute_script(char* sname);
void enableInterrupts();
