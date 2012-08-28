/*
 * This is an extension of the shell which stores the definitions for the man
 * commmand.
 *
 * Authors: John Jones and Russell Toris
 * Version: April 1, 2010
 */

#include "shell_list.h"

/*
 * Prints a manual for the command 'cmd' if one exists.
 */
void print_man(char *cmd)
{
	//find the command
	if(strcmp(cmd, "clear\0") == 0) {
		dino_print("\n Clear Screen Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > clear\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will clear all information\0");
		dino_print(" in the shell.\0");
	} else if(strcmp(cmd, "delete\0") == 0) {
		dino_print("\n Delete Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > delete <file_name>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will delete the file with \0");
		dino_print("file name 'file_name'.\0");
	} else if(strcmp(cmd, "dir\0") == 0) {
		dino_print("\n Directory Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > dir\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will print a list of all \0");
		dino_print("files on the disk and their size.\0");
	} else if(strcmp(cmd, "echo\0") == 0) {
		dino_print("\n Echo Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > echo <string>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will print out <string> to \0");
		dino_print("the shell.\0");
	} else if(strcmp(cmd, "execute\0") == 0) {
		dino_print("\n Execute Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > execute <prgm_name>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will attempt to execute the \0");
		dino_print("program or shell script with the\n\0");
		dino_print("file name 'prgm_name'.\0");
	} else if(strcmp(cmd, "help\0") == 0) {
		dino_print("\n Help Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > help\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will print a list of all\0");
		dino_print(" valid shell commands.\0");
	} else if(strcmp(cmd, "kill\0") == 0) {
		dino_print("\n Kill Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > kill <segment>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will kill the process with the\0");
		dino_print(" given segment number.\0");
	} else if(strcmp(cmd, "logout\0") == 0) {
		dino_print("\n Logout Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > logout\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will log you out of the current\0");
		dino_print(" shell session.\0");
	}  else if(strcmp(cmd, "man\0") == 0) {
		dino_print("\n Manual Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > man <cmd_name>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will display the manual for\0");
		dino_print(" the command with name 'cmd_name'.\0");
	} else if(strcmp(cmd, "ps\0") == 0) {
		dino_print("\n Process List Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > ps\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will print a list of all \0");
		dino_print("running processes.\0");
	} else if(strcmp(cmd, "symlink\0") == 0) {
		dino_print("\n Symbolic Link Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > symlink <src> <dest>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will create a symbolic link from <src> \0");
		dino_print("to <dest>.\0");
	} else if(strcmp(cmd, "type\0") == 0) {
		dino_print("\n Type Manual\0");
		dino_print("\n\0");
		dino_print("\nUSE:\0");
		dino_print("\n\0");
		dino_print("\n > type <file_name>\0");
		dino_print("\n\0");
		dino_print("\nDESCRIPTION:\0");
		dino_print("\n\0");
		dino_print("\n - This command will print the contents of \0");
		dino_print("file with file name 'file_name'.\0");
	} else {
		//go to the next line
		dino_print("\n\0");
		//command not found
		dino_print(cmd);
		dino_print(": command not found. Type 'help' for a list.\0");
	}
}
