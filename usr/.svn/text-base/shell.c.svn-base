/*
 * This is the main shell program for the dinoDOS operating system.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#include "shell.h"
#include "shell_list.h"
#include "shell_users.h"
#include "lib/sys.h"
#include "lib/stdlib.h"

//the prompt string for the shell
char *prompt = "dinoDOS> \0";
//if we have made a logout call yet
bool logout = FALSE;

int main()
{
	enableInterrupts();

	while(1) {
		clear_scr();
		dino_print("Welcome to dinoDOS. Please login.\n\0");
		while(!validate()) {
			dino_print("Error: invalid credentials.\n\0");
		}
		//we do not want to logout yet
		logout = FALSE;
		clear_scr();
		//begin the shell promt
		while(!logout) {
			//holds the current input
			char curInput[MAX_INPUT];
			//used to print or not print a new line after a command
			bool addNewLine;
			//print the prompt
			dino_print(prompt);
			//wait for input
			read_input(curInput, MAX_INPUT);

			//only run on non-empty inputs
			if (strlen(curInput) > 0) {
				//return tells if a line break should be printed
				addNewLine = interpret_cmd(curInput);
			} else {
				//we want to add a new line if it was empty
				addNewLine = TRUE;
			}
			//print the new line if we want it		
			if (addNewLine) {
				dino_print("\n\0");
			}
			//let the another process continue
			yield();
			//on to the next command!
		}
	}
}

/*
 * Read the input from the shell character by character into the given buffer.
 * The max parameter should be used to prevent buffer overflow. Any characters
 * after max will not be read. Characters are printed to the shell as they
 * are entered. The number of characters read is returned. This is terminated
 * once a return key is pressed. 
 */
int read_input(char *buf, int max)
{
	//used as a counter
	int i = 0;
	//initialize the first entry
	buf[i] = NULL;
	//runs until we get a return key
	while (buf[i] != 0x0D) {
		//wait and get the next keyboard response
		int cur = getchar();
		//check its ASCII value
		char c = (char) cur;
		//0xE0 means its an extended key (arrow)
		if (c == 0xE0) {
			//get the scan code
			byte scan = cur / 256;
			//check if it is either arrow
			if (scan == 72 || scan == 80) {
				//get the command from the list
				char *listCmd;
				if (scan == 72) {
					listCmd = prev();
				} else {
					listCmd = next();
				}
				//only continue on a non-empty command
				if(strlen(listCmd > 0)) {
					//clear the current command
					for(i; i > 0; i--) {
						//call backspace macro
						BACKSPACE
					}
					//copy the incoming command
					while(listCmd[i] != 0) {
						buf[i] = listCmd[i];
						i++;
					}
					dino_print(listCmd);
				}
			}
			continue;
		}
		//we have a valid ASCII code if we are here
		buf[i] = c;
		//check for the return
		if (buf[i] == 0x0D) {
			//end the string
			buf[i] = NULL;
			break;
		}
		//check if we are under max or if we have a backspace pressed
		else if (i < max || buf[i] == 0x08) {
			//convert the character as a string with \0 to end it
			char tmp[2];
			tmp[0] = buf[i];
			tmp[1] = NULL;
			//handle backspace
			if(buf[i] == 0x08 && i > 0) {
				//call backspace macro
				BACKSPACE
				//remove one from the count
				i--;
			}
			//check that it is a valid printable ASCII character
			else if (buf[i] >= 32 && buf[i] <= 126) {
				//print out the character
				dino_print(tmp);
				//add one to the count
				i++;
			}
		} 
	}
	//add it to the list if it is non-empty
	if (strlen(buf) > 0) {
		push(buf);
	}
	//number of characters read in
	return i;
}

/*
 * This is a function to interpret the current command from the shell. The
 * return is a decision if the shell should print a new line after returning.
 */
bool interpret_cmd(char *str)
{
	//stores current command and argument
	struct command_line command;
	//get the command first (before first instance of ' ')
	int i = 0;
	while(str[i] != NULL) {
		if (str[i] != ' ') {
			command.cmd[i] = str[i];
			i++;
		} else {
			command.cmd[i] = NULL;
			break;
		}
	}
	//if i is the length, we have no spaces (thus, no arguments)
	if (i == strlen(str)) {
		command.cmd[i] = NULL;
		command.arg[0] = NULL;
	} else {
		int j = 0; //counter for the argument array
		//start after the space
		i++; //don't change value of i -- this is where we want to start
		//same as before, continue til null
		while(str[i] != NULL) {
			command.arg[j] = str[i];
			i++;
			j++;
		}
		//end the argument
		command.arg[j] = NULL;
	}

	//find the matching command
	if(strcmp(command.cmd, "clear\0") == 0) {
		//clear the screen
		clear_scr();
		//dont add a new line
		return FALSE;
	} else if(strcmp(command.cmd, "copy\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//what is returned from fcopy
			int copy_ret;

			//split the argument into two (command.arg is 60 chars) 
			char arg0[30];
			char arg1[30];
			//get the first argument and check for a second
			if (strtok(command.arg, ' ', arg0) == NULL) {
				//missing an argument
				print_argerror(command.cmd);
				return;
			}
			//copy the remainder into the second argument
			i = strlen(arg0);
			while(command.arg[i] != NULL) {
				arg1[i-strlen(arg0)] = command.arg[i+1];
				i++;
			}

			//start program output on a new line
			dino_print("\n\0");
			copy_ret = fcopy(arg0, arg1);
			//check the return
			if (copy_ret == -3) {
				dino_print(arg0);
				dino_print(": file not found.\0");
			} else if (copy_ret == -2) {
				dino_print("Disk is full.\0");
			} else if (copy_ret == -1) {
				dino_print("Disk directory is full.\0");
			} else {
				//dont print a new line after the program
				return FALSE;
			}
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if(strcmp(command.cmd, "delete\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//what is returned from delete
			int delete_ret;
			//start program output on a new line
			dino_print("\n\0");
			delete_ret = fdelete(command.arg);
			//check the return
			if (delete_ret == -1) {
				dino_print(command.arg);
				dino_print(": file not found.\0");
			} else {
				//dont print a new line after the program
				return FALSE;
			}
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if (strcmp(command.cmd, "dir\0") == 0) {
		struct directory diskDir;
		int i,j;
		//print a header
		dino_print("\nNAME       SIZE\0");
		dino_print("\n---------------\0");
		//load the disk directory
		read_sect((byte *)&diskDir, 2);		
		//go through each entry in the directory
		for(i = 0; i < 16; i++) {
			//dont print empty names
			if (diskDir.entries[i].name[0] != '\0') {
				//copy the name into a bigger array to 
				//add a null terminator
				char curName[7];
				int size, k;
				for(j = 0; j < 6; j++) {
					curName[j] = diskDir.entries[i].name[j];
				}
				curName[6] = NULL;
				//print the name
				dino_print("\n\0");
				dino_print(curName);
				//print an equal number of spaces to align the
				//size column
				//get the number of spaces to print
				size = (6 - strlen(curName)) + 5;
				for(k=0; k<size; k++) {
					dino_print(" \0");
				}
				//to get the size, get the size of the sector
				//array which is null terminated or 26
				size = strlen(diskDir.entries[i].sector);
				size = min(26, size);

				//check if it is a symlink, if so just have
				//size equal to 1
				if (diskDir.entries[i].sector[0] == 0xFF) {
					size = 1;
				}
				//decide if there need to be an extra space
				//to align it correctly
				if (size < 10) {
					dino_print(" \0");
				}
				//print the size
				dino_printint(size);
			}
		}
	} else if (strcmp(command.cmd, "echo\0") == 0) {
		//place the argument it on a new line
		dino_print("\n\0");
		dino_print(command.arg);
	} else if(strcmp(command.cmd, "execute\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//what is returned from exec
			int exec_ret;

			if (command.arg[strlen(command.arg)-1] != '&') {
				//first try it as a script
				exec_ret = execute_script(command.arg);
			} else {
				exec_ret = -3;
			}
			
			//if it was not a script, execute as a user program
			if (exec_ret == -3) {			
				dino_print("\n\0");				
				if (command.arg[strlen(command.arg)-1] == '&') {
					int priority = 0; //default to 0
					char nameBuf[15]; //holds the actual program name
					char prioBuf[15]; //holds the priority
					//pull out the command (take out & and priority)
					strtok(command.arg,' ',nameBuf);
					//now check if there is a priority
					if(strtok(0x00,' ',prioBuf) != 0x00) {
						priority = atoi(prioBuf);
					}
					exec_ret = exec(nameBuf, priority);
				} else {
					exec_ret = execWait(command.arg);
				}
			
				
			}
			
			//check the return 
			if (exec_ret == -1) {
				//start program output on a new line
				dino_print("\n\0");
				dino_print(command.arg);
				dino_print(": file does not exist.\0");
			} else if (exec_ret == -2) {
				dino_print("Error: no free memory segments.\0");
			} else if (exec_ret == -3) {
				dino_print(command.arg);
				dino_print(": program is not executable.\0");
			} else {
				//dont print a new line after the program
				return FALSE;
			}
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if(strcmp(command.cmd, "help\0") == 0) {
		//print all valid commands
		print_help();
	} else if(strcmp(command.cmd, "kill\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//get the segment from the argument and try to kill it
			if (kill(atoi(command.arg)) == -1) {
				dino_print("\nNo such processes segment.\0");
			} else {
				dino_print("\nProcess killed.\0");
			}
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if(strcmp(command.cmd, "logout\0") == 0) {
		//set the logout variable
		logout = TRUE;
		//no need to print a new line
		return FALSE;
	} else if(strcmp(command.cmd, "man\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//print its manual
			print_man(command.arg);
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if(strcmp(command.cmd, "ps\0") == 0) {
		dino_print("\n\0");
		proc();
		return FALSE;
	} else if(strcmp(command.cmd, "symlink\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//what is returned from link
			int link_ret;

			//split the argument into two (command.arg is 60 chars) 
			char arg0[30];
			char arg1[30];
			//get the first argument and check for a second
			if (strtok(command.arg, ' ', arg0) == NULL) {
				//missing an argument
				print_argerror(command.cmd);
				return;
			}
			//copy the remainder into the second argument
			i = strlen(arg0);
			while(command.arg[i] != NULL) {
				arg1[i-strlen(arg0)] = command.arg[i+1];
				i++;
			}

			//start program output on a new line
			dino_print("\n\0");
			link_ret = link(arg0, arg1);
			//check the return
			if (link_ret == -1) {
				dino_print(arg0);
				dino_print(": file not found.\0");
			} else if (link_ret == -2) {
				dino_print("Disk directory is full.\0");
			} else {
				//dont print a new line after the program
				return FALSE;
			}
		} else {
			//missing an argument
			print_argerror(command.cmd);
		}
	} else if(strcmp(command.cmd, "type\0") == 0) {
		//check if we have an argument
		if (strlen(command.arg) > 0) {
			//try and load the file
			byte buf[13312];
			//start output on a new line
			dino_print("\n\0");
			if (fopen(command.arg, buf, 13312) == -1) {
				//file does not exist
				dino_print(command.arg);
				dino_print(": file does not exist.\0");
			} else {
				//print the file contents
				dino_print(buf);
			}
		} else {
			//missing argument
			print_argerror(command.cmd);
		}
	} else {
		//go to the next line
		dino_print("\n\0");
		//command not found
		dino_print(command.cmd);
		dino_print(": command not found. Type 'help' for a list.\0");
	}
	//we want a new line after we finish
	return TRUE;
}

/*
 * Print an error message that the command 'cmd' is missing arguments.
 */
void print_argerror(char *cmd)
{
	dino_print("\nError: missing argument. \0");
	dino_print("Type 'man \0");
	dino_print(cmd);
	dino_print("' for additional help.\0");
}

/*
 * Prints out a list of all valid shell commands.
 */
void print_help()
{
	dino_print("\nThe following are valid commands:\0");
	dino_print("\n\0");
	dino_print(" clear\0");
	dino_print("\n\0");
	dino_print(" copy\0");
	dino_print("\n\0");
	dino_print(" delete\0");
	dino_print("\n\0");
	dino_print(" dir\0");
	dino_print("\n\0");
	dino_print(" echo\0");
	dino_print("\n\0");
	dino_print(" execute\0");
	dino_print("\n\0");
	dino_print(" help\0");
	dino_print("\n\0");
	dino_print(" kill\0");
	dino_print("\n\0");
	dino_print(" logout\0");
	dino_print("\n\0");
	dino_print(" man\0");
	dino_print("\n\0");
	dino_print(" ps\0");
	dino_print("\n\0");
	dino_print(" symlink\0");
	dino_print("\n\0");
	dino_print(" type\0");
}

/*
 * Attempt to execute the shell script with the file name sname. If no such
 * file exists, -1 is returned. If the file is not a valid shell script, -2 is
 * returned. No spaces should be put in the begining or end of a line and each
 * command must begin on its own line. Comments can be added by using # as the 
 * first character of the line. Valid shell scripts must have #! on the first
 * line.
 */
int execute_script(char* sname) {
	//buffer for the file
	byte buffer[512*26];
	//try and load the file
	if (fopen(sname,buffer,512*26) >= 0) {
		//check if it is a valid shell script.
		if (buffer[0] == '#' && buffer[1] == '!') {
			//temp buffer for a line of the file
			char line[512*26];
			//get the file line by line
			strtok(buffer, '\r', line); //first line is #! - ignore
			//continue until only the last line remains
			while (strtok('\0', '\r', line) != '\0') {
				//make sure it is not a comment line or empty
				if(line[0] != '#' && strlen(line) > 0) {
					interpret_cmd(line);
				}
			}
			//now get the last line
			strtok('\0', '\0', line);
			//make sure it is not a comment line or empty
			if(line[0] != '#' && strlen(line) > 0) {
				interpret_cmd(line);
			}
			dino_print("\n\0");
		} else {
			return -3;
		}
	} else {
		return -1;
	}
}
