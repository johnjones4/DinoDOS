/*
 * This is an extension of the shell which stores a history of recent commands
 * into a list.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#include "shell_list.h"

char history[HISTORY_MAX][MAX_INPUT];
int size = 0; //size goes from 0...MAX
int top = -1; //points to the front of the list
int pointer = 0; //pointer to the current element being looked at

/*
 * Push character command 'cmd' to the front of the list if it is not a 
 * duplicate of the current front. This resets the pointer to look at the front
 * of the list.
 */
void push(char *cmd)
{
	int i = 0;
	//copy if it is a not a duplicate of the top element
	if (size == 0 || (strcmp(cmd, history[top]) != 0)) {
		//if we have not maxed out yet, increment top
		if (top < HISTORY_MAX-1) {
			top++;
		} else {
			//if there is no room, go back to the begining
			top = 0;
		}

		//copy the command
		while(cmd[i] != '\0') {
			history[top][i] = cmd[i];
			i++;
		}
		//add the null pointer
		history[top][i] = '\0';

		//only add to size until it is filled
		if(size < HISTORY_MAX) {
			size++;
		}
	}
	//point to the front of the list. 
	pointer = top;
}

/*
 * Get the next element in the list. This will return a pointer to the null
 * character if the list is empty.
 */
char *next()
{
	//check if the stack is empty
	if (top == -1) {
		//creates a pointer to null
		return "\0";
	} else {
		//move the pointer
		if(pointer == size-1) {
			//go back to the start
			pointer = 0;
		} else {
			pointer++;
		}
		return history[pointer];
	}
}

/*
 * Get the previous element in the list starting with the element at the front.
 * This will return a pointer to the null character if the list is empty.
 */
char *prev()
{
	//check if the stack is empty
	if (top == -1) {
		//creates a pointer to null
		return "\0";
	} else {
		//get a reference
		char *ptr = history[pointer];
		//move the pointer
		if (pointer == 0) {
			//circle around
			pointer = size-1;
		} else {
			pointer--;
		}
		return ptr;
	}
}
