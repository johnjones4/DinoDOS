/*
 * This is a simple text editor used in dinoDOS. It will prompt the user for a
 * file name at start. If the file exists, it will allow the user to edit the
 * file. Otherwise a new file is created. When finished, the file is written to
 * the disk if it can fit.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#include "dedit.h"
#include "lib/sys.h"
#include "lib/math.h"
#include "lib/stdio.h"
#include "lib/string.h"

//holds the file name
char fname[6];
//holds the file information
char f[13312];

int main()
{
	//return value from fwrite
	int ret;
	enableInterrupts();
	//clear the screen
	clear_scr();
	//get the file name
	dino_print("Enter a file name to edit: \0");
	read_line(fname, 6);

	//try and load the file if it exists or create a new one
	if (fopen(fname, f, 13312) == -1) {
		//file does not exist, put a null in the start
		f[0] = '\0';
	}

	//start the editor
	edit(f);

	//clear the screen again
	clear_scr();

	//write the file back
	ret = fwrite(fname, f, (strlen(f)/512)+1);
	//check if it was successful
	if (ret == -2) {
		dino_print("Disk is full.\n\0");
	} else if (ret == -1) {
		dino_print("Disk directory is full.\n\0");
	}
	//finished
	terminate();
}

/*
 * This is the main editor function. This will work with the global buffer 'f'.
 * This function is ended by the user pressing ctrl-d and confirming that they 
 * are finished.
 */
void edit()
{
	int i; //counter
	//used to see if we are done
	char done;
	edit:
	//paint the editor
	repaint();
	//set i to where we are in the file
	i = strlen(f);
	//read the next character and check if it ctrl-d
	while ((f[i] = getchar()) != 0x04) {
		//continue if we are less than file size or backspace is pressed
		if (i < 13312 || f[i] == 0x08) {
			//convert the character as a string with \0 to end it
			char tmp[2];
			tmp[0] = f[i];
			tmp[1] = '\0';
			//handle backspace
			if(f[i] == 0x08 && i > 0) {
				//note: printing 0x08 moves the cursor back
				//print 0x08, a space to clear, and 0x08 again
				char clr[4];
				clr[0] = 0x08;
				clr[1] = ' ';
				clr[2] = 0x08;
				clr[3] = '\0';
				//moves the cursor back
				dino_print(clr);
				//move the counter
				i--;
				/*
				 * repait the editor - fixes the issue that
				 * printing the backspace does not go up to the
				 * previous line. VERY INEFFICIENT... :(
				 */
				//end the file first
				f[i] = '\0';
				repaint();
			}
			//check that it is a valid ASCII character or a return
			else if ((f[i] >= 32 && f[i] <= 126) || f[i] == 0x0D) {
				//print out the string
				dino_print(tmp);
				//add one to the count
				i++;
			}
		}
	}
	//end the file
	f[i] = '\0';

	//check if we are sure we want to save
	dino_print("\nAre you sure you want to save and quit? (y/n) \0");
	//wait for a y or n
	while((done = getchar()) != 'y' && done != 'n');
	//check if we are done
	if(done == 'n') {
		//start editing again
		goto edit;
	}
}

/*
 * Repaint the editor and the contents of the file's buffer. Useful when using
 * the backspace.
 */
void repaint()
{
	int i; //counter
	//clear the screen
	clear_scr();
	//add the header
	dino_print("DEDIT - '\0");
	dino_print(fname);
	dino_print("'\0");
	//print some spaces so the save message is left aligned
	for(i=0; i<57-strlen(fname); i++) {
		dino_print(" \0");
	}
	dino_print("CTRL-D - Save\0");
	//print a line of '-'s (length 80)
	for(i=0; i<4; i++) {
		dino_print("--------------------\0");
	}
	//print the file
	dino_print(f);
}
