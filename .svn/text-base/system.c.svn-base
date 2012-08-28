/*
 * dinoDOS is a very basic and simple OS named after the cover of the course
 * textbook. This is a C library which contains many of the low level system
 * functions for the OS. 
 *
 * Authors: John Jones and Russell Toris
 * Version: 0.3 March. 1, 2010
 */

#include "system.h"
#include "proc.h"
#include "usr/lib/string.h"
#include "usr/lib/math.h"

/*
 * Prints a character 'c' at the given row and col (both starting from 0) with
 * the given color. 0 <= row < 25; 0 <= col < 80. If an invalid value for row, 
 * col are given, no changes will be made. 
 */
void putChar(char c, int row, int col, byte color)
{
	//check if it is on the screen
	if (row >= 0 && row < 25 && col >= 0 && col < 80) {
		//offset based on segment 0xB800 
		int offset = ((80*row) + col) * 2;
		//put the character
		putInMemory(0xB800,offset,c);
		//set the color
		putInMemory(0xB800,offset+1,color);
	}
}

/*
 * Prints the string str starting at the given row and col with the given color.
 * 0 <= row < 25; 0 <= col < 80. Printing to far to the right will continue on
 * the next line if such a line exists. Printing off the screen will have no
 * result.
 */
void putStr(char* str, int row, int col, byte color)
{
	//check if we are at a correct starting position
	if (row >= 0 && col >= 0 && row < 25) {
		//used to iterate through the string
		int i = 0;
		while(str[i] != NULL) {
			//if we are off the screen, advance a row
			if (col > 79) {
				col=0;
				row++;
			}
			//only continue if we are still on the screen
			if (row <= 24) {
				putChar(str[i],row,col,color);
				col++;
				i++;
			} else {
				break;
			}
		}
	}
}

/*
 * Pring the character string str starting at the current cursor position and
 * returns the number of characters printed.
 */
int printString(char *str)
{
	//used as a counter
	int i = 0;
	//print until we hit the end
	while(str[i] != NULL) {
		char ah = 0x0E;
		//calculate ax
		int ax;
		//check for the \n or \r (need to print both to get a new line)
		if (str[i] == 0x0D || str[i] == 0x0A) {
			ax = ah * 256 + 0x0A;
			interrupt(0x10, ax, 0, 0, 0);
			ax = ah * 256 + 0x0D;
			interrupt(0x10, ax, 0, 0, 0);
		} else {
			//print the character
			ax = ah * 256 + str[i];
			interrupt(0x10, ax, 0, 0, 0);
		}
		i++;
	}
	//number of characters printed
	return i;
}

/* 
 * This method will print the value of the int i provided at the current cursor
 * location. 
 */
void printInt(int i)
{
	//holds an array to print
	char toPrint[2];
	//a counter for the current power of 10
	int power = 1;
	
	//add a null terminator to the end of our printing array
	toPrint[1] = NULL;
	
	//if it is negative, print a '-' sign first
	if(i < 0) {
		//ASCII for '-'
		toPrint[0] = 0x2D;
		printString(toPrint);
		//reverse the value
		i = -i;
	}

	//find the greatest power of 10 not greater than i
	while (power <= i/10) {
		power = power * 10;
	}
	
	//keep going down by powers of 10 to get the left most digit at a time
	for (power; power >= 1; power = power / 10) {
		//integer division will give the left most digit 
		int n = i / power;

		//get its ASCII value
		if (n == 0)
			toPrint[0] = 0x30;
		else if (n == 1)
			toPrint[0] = 0x31;
		else if (n == 2)
			toPrint[0] = 0x32;
		else if (n == 3)
			toPrint[0] = 0x33;
		else if (n == 4)
			toPrint[0] = 0x34;
		else if (n == 5)
			toPrint[0] = 0x35;
		else if (n == 6)
			toPrint[0] = 0x36;
		else if (n == 7)
			toPrint[0] = 0x37;
		else if (n == 8)
			toPrint[0] = 0x38;
		else if (n == 9)
			toPrint[0] = 0x39;
		//print it
		printString(toPrint);
		//get the remainder
		i = mod(i, power);
	}
}

/*
 * Clear the screen and place the cursor at the top left. 
 */
void clearScreen()
{
	//first actually clear the screen
	byte ah = 6; //scrolling mode
	byte al = 0x00; //clears cells
	byte bh = 0x0E; //black with yellow text (dino theme!)
	byte ch = 0x00; //start at row 0
	byte cl = 0x00;	//start at col 0
	byte dh = 24; //end at row index 24
	byte dl = 79; //end at col index 
	//place in ax, bx, cx, dx
	int ax = ah * 256 + al; 
	int bx = bh * 256;
	int cx = ch * 256 + cl;
	int dx = dh * 256 + dl;
	interrupt(0x10, ah * 256 + al, bh * 256, cx, dx);

	//disable weird blinking thing
	interrupt(0x10, 0x1003,0,0,0);
	//full block cursor
	//interrupt(0x10, 0x0100, 0, 0x00FF, dx);
	//place cursor back at the top
	interrupt(0x10, 0x0200,0,0,0); //ah=0x02, bh=page, dh=row, dl=col
}

/*
 * Read a string from the keyboard into the character string 'buf'. The max
 * parameter should be the max number of characters to be read (the size of 
 * the buffer. Note that buf should be char[max+1] as char[max] needs to be '\0'
 * Any characters after buf[max] will not be read. The loop will also break if 
 * the return key is pressed. Only valid printable ASCII characters (>= 32, 
 * <=126) will count and be printed. All other characters are printed to the 
 * screen. The backspace key will clear one character back. This method returns
 * the number of characters read in.
 */
int readLine(char *buf, int max)
{
	
	//used as a counter
	int i = 0;

	//read the next character and check if it is the return key
	while ((buf[i] = interrupt(0x16, 0, 0, 0, 0)) != 0x0D) {
		//continue if we are less than max or backspace is pressed
		if (i < max || buf[i] == 0x08) {
			//convert the character as a string with \0 to end it
			char tmp[2];
			tmp[0] = buf[i];
			tmp[1] = NULL;
			//handle backspace
			if(buf[i] == 0x08 && i > 0) {
				//note: printing 0x08 moves the cursor back
				//print 0x08, a space to clear, and 0x08 again
				char clr[4];
				clr[0] = buf[i];
				clr[1] = ' ';
				clr[2] = buf[i];
				clr[3] = NULL;
				//moves the cursor back
				printString(clr);
				//remove one from the count
				i--;
			}
			//check that it is a valid printable ASCII character
			else if (buf[i] >= 32 && buf[i] <= 126) {
				//print out the string
				printString(tmp);
				//add one to the count
				i++;
			}
		}
	}
	//end the string
	buf[i] = NULL;
	//number of characters read in
	return i;
}

/*
 * Get the full AX value from next key returned from the keyboard. The value is
 * ah =  BIOS scan code and al = ASCII character. If an extended keystroke
 * value is recived, al will be 0xE0 and the scan code should be used. An 
 * extended keystroke is a non ASCII character (i.e. arrow keys)
 */
int getChar()
{
	//AH = 0x10 get extended keys as well	
	return interrupt(0x16, 0x1000, 0, 0, 0);
}

/*
 * Read a sector from the disk into the buf array starting from the absoulute
 * sector provided. The integer '1' is returned. 
 */
int readSector(byte *buf, int absSector)
{
	//convert to C:H:S
	byte cl = (mod(absSector, 18)) + 1;
	byte ch = (absSector / 36);
	byte dh = mod((absSector / 18),2);
	
	//place in cx and dx
	int cx = ch * 256  + cl;
	int dx = dh * 256 + 0x00;
	interrupt(0x13, 0x0201, buf, cx, dx);
	return 1;
}

/*
 * Write the 512 byte buffer into the sector provided. Returns 1.
 */
int writeSector(byte *buf, int absSector)
{
	//convert to C:H:S
	byte cl = (mod(absSector, 18)) + 1;
	byte ch = (absSector / 36);
	byte dh = mod((absSector / 18),2);
	
	//place in cx and dx
	int cx = ch * 256  + cl;
	int dx = dh * 256 + 0x00;
	interrupt(0x13, 0x0301, buf, cx, dx);
	return 1;
}

/*
 * Read a file with a given name into the given buffer. If the file name does
 * not exist, -1 is returned. Otherwise it will be loaded into buf and return 
 * the number of sectors read. Max size should be the size of the buffer used
 * to prevent buffer overflow. The file is loaded in whole sectors (512 bytes).
 * Therefore, a buffer of size 511 will read 0 sectors. The number of sectors
 * read is returend.
 */
int readFile(char *filename, char *buf, int max)
{
	//the main disk directory
	struct directory diskDir;
	int index, i;

	//populate the disk directory
	readSector((byte *)&diskDir, 2);
	
	//check for the file
	index = dirEntryIndex(filename,&diskDir);
	index_check:
	if (index >= 0) {
		//now check if this is a symbolic link
		if (diskDir.entries[index].sector[0] == 0xFF) {
			//try and find the file its linking to
			char newName[7];
			//copy the name
			for(i=0; i<6; i++) {
				//offset by one to ignore the 0xFF
				newName[i] = diskDir.entries[index].sector[i+1];
			}
			//null terminate
			newName[6] = '\0';
			//try and find that file
			index = dirEntryIndex(newName,&diskDir);
			//now try to load it
			goto index_check;
		}
		for(i = 0; i < 26; i++) {
			//check if we are at the end yet or 
			//if we reached the end of the buffer
			if(diskDir.entries[index].sector[i] == 0 || 
				(i+1) * 512 > max) {
				break;
			}
			readSector(buf,diskDir.entries[index].sector[i]);
			//add to the pointer
			buf += 512;
		}
		return i;
	} else {
		//file not found
		return -1;
	}
}

/*
 * Execute a program with the given name. If there are no free memory segments,
 * -2 is returned. -1 is returend if the file name does not exist. -3 is 
 * returned if the file is not marked as executable. Otherwise, the program is
 * added to the ready queue and 1 is returned. The 'wait' parameter is used to
 * decicde if all other processes should wait for this program to terminate
 * before continuing. 0 will disable this function, and anything greater will
 * enable it. The priority is used to schedule priority to a process within the
 * ready queue. The default is 0. Note, this queue does NOT protect against
 * process starvation. Negative numbers will default to 0. Use priorities wisely.
 */
int executeProgram(char *name, int wait, int priority)
{
	int segment, toWait = wait, curPrio = max(0, priority);
	setKernelDataSegment();
	segment = getFreeMemorySegment();
	restoreDataSegment();
	if (segment == -1) {
		//none free segments left
		return -2;
	} else {
		//max file size
		byte buf[13312];
		//size in bytes is sectors * 512
		int size = readFile(name, buf, 13312) * 512;
		if (size > 0) {
			int i;
			
			//check the "magic number"
			if(buf[0] != 'r' && buf[1] != 'j') {
				//not executable
				//free the memory segment
				setKernelDataSegment();
				releaseMemorySegment(segment);
				restoreDataSegment();
				return -3;
			} else {
				//it is executable, setup a PCB
				struct PCB *cur;
				setKernelDataSegment();
				cur = getFreePCB();
				//check that it is not null
				if (cur == NULL) {
					//free the memory segment
					releaseMemorySegment(segment);
					restoreDataSegment();
					return -2;
				}
				//initialize the PCB
				restoreDataSegment();
				//keep a pointer to teh shell for priority reasons
				if(strcmp(name, "shell\0") == 0) {
					setKernelDataSegment();
					shellPtr = cur;
					restoreDataSegment();
				}
				setKernelDataSegment();
				//NAME COPIES DO NOT WORK, CALL IT DINO
				cur->name[0] = 'D';
				cur->name[1] = 'I';
				cur->name[2] = 'N';
				cur->name[3] = 'O';
				cur->name[4] = '\0';
				
				cur->state = STARTING;
				cur->segment = segment;
				cur->stackPointer =  0xFF00;
				cur->priority = curPrio;
				//set the shells priority to the highest so it does multiprogramming still
				shellPtr->priority = highestCurPriority();
				restoreDataSegment();

				for(i = 2; i<size; i++) { 
					//starts at i=2 to get rid of magic num
					putInMemory(segment, i-2, buf[i]);
				}
				setKernelDataSegment();
				//add it to the queue
				addToReady(cur);
				//check if we are waiting to return
				if(toWait > 0) {
					wait_segment = cur->segment;
				}
				restoreDataSegment();

				//initialize the program
				initializeProgram(segment);
				return 1;
			}
		} else {
			//-1 was returned by readFile. Thus it does not exist
			//free the memory segment
			setKernelDataSegment();
			releaseMemorySegment(segment);
			restoreDataSegment();
			return -1;
		}
	}
}

/*
 * Attempts to delete the file with the given name. If the file was found and
 * deleted, 1 is returned. If the file name cannout be found, -1 is returned.
 */
int deleteFile(char *fname)
{
	//the main disk directory
	struct directory diskDir;
	byte diskMap[512];
	int index;
	
	//populate the disk directory
	readSector((byte *)&diskDir, 2);
	
	//check for the file
	index = dirEntryIndex(fname,&diskDir);
	
	if (index >= 0) {
		int i, max;
		diskDir.entries[index].name[0] = '\0';
		//read the disk map
		readSector(diskMap, 1);
		//sectors used it null terminated or 26
		max = min(26, strlen(diskDir.entries[index].sector));
		for(i=0; i<max; i++) {
			byte sector = diskDir.entries[index].sector[i];
			diskMap[sector] = 0x00;
		}
		writeSector(diskMap, 1);
		writeSector((byte*)&diskDir,2);
		return 1;
	} else {
		return -1;
	}
}

/*
 * Write the contents of buffer as a file with the given number of sectors
 * and the given name. If that file name already exists, it will overwrite that
 * file. This will return -1 if the disk directory is full, -2 if the disk was
 * filled while writing the file, or the number of sectors written.
 */
int writeFile(char *fname, char *buffer, int sectors)
{
	//the main disk directory and map
	struct directory diskDir;
	byte diskMap[512];
	//holds which directory struct we will save to
	int d;

	//load the sector and map
	readSector((byte *)&diskDir, 2);
	readSector(diskMap, 1);

	//check if the does not exist, otherwise overwrite it
	if((d = dirEntryIndex(fname, &diskDir)) == -1) {
		//did not find it, lets look for an empty spot
		//used to check for empty name in the directory
		char null[1];
		null[0] = '\0';
		d = dirEntryIndex(null, &diskDir);
	}

	if (d >= 0) {
		//total number of sectors written and a counter
		int total, i;
		//current place in the map we are looking at
		int curMap = 0;
		//current sector in the directory we are saving to
		int curSect = 0;

		//only write up to 26 sectors
		sectors = min(sectors,26);
		while (curSect < sectors && curMap < 512)
		{
			if (diskMap[curMap] == 0x00) {
				//store that sector in the directory
				diskDir.entries[d].sector[curSect] = curMap;
				//mark that sector as used
				diskMap[curMap] = 0xFF;
				//write that sector from the file
				writeSector(buffer, curMap);
				//add to the file pointer
				buffer += 512;
				curSect++;
			}
			curMap++;
		}

		//check if any sectors were written
		if (curSect == 0) {
			//no space avilable
			return -1;
		}

		//check if we wrote all that we wanted to
		else if (curSect < sectors) {
			//means we ran out of space at some point
			total = -2;
		} else {
			total = curSect;
		}
		//fill in the rest of the sectors in the directory as '\0'
		for (i = curSect; i < 26; i++) {
			diskDir.entries[d].sector[i] = '\0';
		}

		//store the name in the directory (up to 6 characters)
		for (i = 0; i < 6; i++) {
			diskDir.entries[d].name[i] = fname[i];
		}
		//write the map and directory back to the disk
		writeSector(diskMap, 1);
		writeSector((byte*)&diskDir,2);

		return total;
	} else {
		//no room in the directory
		return -1;
	}
}



/* 
 * Get the index in the given directory struct of the file with the given name
 * or -1 if that file does not exist.
 */
int dirEntryIndex(char *fname, struct directory *dir)
{
	//used as counter
	int i,j;
	//go through each entry in the directory
	for(i = 0; i < 16; i++) {
		//copy the name into a bigger array to add a null terminator
		char curName[7];
		for(j = 0; j < 6; j++) {
			curName[j] = dir->entries[i].name[j];
		}
		curName[6] = NULL;
		//check the names of each entry
		if (strcmp(curName, fname) == 0) {
			return i;
		}
	}
	//not found
	return -1;
}

/*
 * Create a symbolic link. This will return -1 if the file to link to does not 
 * exist, -2 if the disk directory is full, or 1 if it was sucessful.
 */
int makeSymLink(char* fname, char* lname)
{
	//the main disk directory
	struct directory diskDir;
	int index;

	//populate the disk directory
	readSector((byte *)&diskDir, 2);
	
	//make sure the desired file name to link to exists
	if((index = dirEntryIndex(fname, &diskDir)) >= 0) {
		//index in the directory to store the link information
		int l;
		//used to check for empty name/spot in the directory
		char null[1];
		null[0] = '\0';
		l = dirEntryIndex(null, &diskDir);
		//check if we found an empty spot
		if (l >= 0) {
			int i;
			//mark the first sector as 0xFF (means its a link)
			diskDir.entries[l].sector[0] = 0xFF;
			for (i = 0; i < 6; i++) {
				//copy the name of the link
				diskDir.entries[l].name[i] = lname[i];
				//store the name of the file we are linking to
				diskDir.entries[l].sector[i+1] = fname[i];
			}
			//save the directroy
			writeSector((byte*)&diskDir,2);
		} else {
			//disk directory is full
			return -2;
		}
	} else {
		//fname not found
		return -1;
	}
}

/*
 * Have the running program give up the remainder of its time
 * slice. 
 */
void yield()
{
	//call a timer interrupt
	interrupt(0x08,0,0,0,0);
}

/*
 * Kill the process with the given segment. Returns 1 if successful and -1 if
 * there is no porcess with the given segment.
 */
int kill(int segment)
{
	struct PCB *curPCB;
	int curSeg;
	setKernelDataSegment();
	curPCB = readyHead;
	//check the running process
	curSeg = running->segment;
	restoreDataSegment();
	if (curSeg == segment) {
		//release it and set it to DEFUNCT
		setKernelDataSegment();
		releaseMemorySegment(running->segment);
		running->state = DEFUNCT;
		running->priority = 0;
		//set the shells priority to the highest again
		shellPtr->priority = highestCurPriority();
		restoreDataSegment();
		return 1;
	}
	//go through the queue and check if we found it
	setKernelDataSegment();
	while(curPCB != NULL)
	{
		curSeg = curPCB->segment;
		restoreDataSegment();
		//check if we found it
		if (curSeg == segment) {
			//release it and set it to DEFUNCT
			setKernelDataSegment();
			releaseMemorySegment(curPCB->segment);
			curPCB->state = DEFUNCT;
			curPCB->priority = 0;
			//set the shells priority to the highest again
			shellPtr->priority = highestCurPriority();
			restoreDataSegment();
			return 1;
		}
		setKernelDataSegment();
		curPCB = curPCB->next;
	}
	restoreDataSegment();
	//segment never found
	return -1;
}

/*
 * Print out a list of all of the proccesses and their segments.
 */
void showProcesses()
{
	struct PCB *printpcb;
	int curSeg;
	setKernelDataSegment();
	//start at the head
	printpcb = readyHead;
	//print information about the running state
	printString("Process \"\0");
	printString(running->name);
	printString("\" is running at segment \0");
	curSeg = running->segment;
	restoreDataSegment();
	printInt(curSeg);
	setKernelDataSegment();
	printString("\n\0");
	//go through the ready queue
	while(printpcb != NULL)	{
		//dont print the idle process
		if(strcmp(printpcb->name, "IDLE\0") != 0) {
			//print the current information
			printString("Process \"\0");
			printString(printpcb->name);
			printString("\" is running at segment \0");
			curSeg = printpcb->segment;
			restoreDataSegment();
			printInt(curSeg);
			setKernelDataSegment();
			printString("\n\0");
		}
		printpcb = printpcb->next;
	}
	restoreDataSegment();
}

/*
 * Have the invoking process sleep for the specified number of seconds.
 */
void sleep(int seconds)
{
	int s = seconds * 12; //12 times per second
	setKernelDataSegment();
	//change the state to SLEEPING
	running->state = SLEEPING;
	//set its sleep counter
	running->sleepCount = s;
	restoreDataSegment();
	//call a timer interrupt to stop running this running process
	interrupt(0x08,0,0,0,0);
}

/*
 * Terminate the program.
 */
void terminate()
{
	setKernelDataSegment();
	//a program has terminated, we can continue all other processes
	wait_segment = 0;
	//free the running processes memory
	releaseMemorySegment(running->segment);
	//release the PCB
	releasePCB(running);
	//set the shells priority to the highest again
	shellPtr->priority = highestCurPriority();
	restoreDataSegment();
	//enter its while loop
	while(1);
}
