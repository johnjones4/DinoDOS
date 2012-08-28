/*
 * A C library that functions as a wrapper for dinoDOS system calls. This
 * library has standard input/output functions.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

#include "stdio.h"

/*
 * Print the string 'str' to the shell. This should be null terminated.
 */
int dino_print(char* str)
{
	//pass it to the kernel
	return interrupt(0x21,0x00,str,0,0);
}

/*
 * Print the integer to the shell.
 */
int dino_printint(int n)
{
	//pass it to the kernel
	return interrupt(0x21,0xA3,n,0,0);
}

/*
 * Wait for the full input line and place it into the buffer. The max value is
 * used to prevent buffer overflow. A new line is terminated by the return key.
 */
int read_line(char* buf, int max)
{
	//pass it to the kernel
	return interrupt(0x21,0x01,buf,max,0);
}

/*
 * Wait and return the next character from the keyboard. This is made up for two
 * bytes. The first is the ASCII value. If the key pressed is an extended key
 * like an arrow key, the first byte is 0xE0. The second byte is the scan code.
 */
int getchar()
{
	//as the kernel for the next character
	return interrupt(0x21,0xA2,0,0,0);
}

/*
 * Read the sector at the given sector into the 512 byte buffer 'buf'. Returns 1
 */
int read_sect(char *buf, int sector)
{
	return interrupt(0x21,0x02,buf,sector,0);
}

int write_sect(char *buf, int sectors) {
	return interrupt(0x21,0x06,buf,sectors,0);
}

/*
 * Load the file with the given name into the given buffer. -1 is returned if
 * that file does not exist. Max is the max size of the buffer to prevent
 * buffer overflow. The file is loaded in whole sectors (512 bytes). Therefore, 
 * a buffer of size 511 will read 0 sectors. 
 */
int fopen(char *filename, char *buf, int max) 
{
	//as the kernel to load the file
	return interrupt(0x21,0x03,filename,buf,max);
}

/*
 * Attempts to delete the file with the given name. If the file was found and
 * deleted, 1 is returned. If the file name cannout be found, -1 is returned.
 */
int fdelete(char *fname)
{
	//call the interrupt
	return interrupt(0x21,0x07,fname,0,0);
}

/*
 * Attempts to write the file defined int file with the provided number of
 * sectors to the given name. If that file name already exists, it will
 * overwrite that file. This will return -1 if the disk directory is full, -2 if
 * the disk was filled while writing the file, or the number of sectors written.
 */
int fwrite(char *fname, char *file, int sectors)
{
	return interrupt(0x21,0x08,fname,file,sectors);
}

/*
 * Attempts to copy the file with the name provided in src to the destination
 * name provided by dest. If the file name cannont be found, -3 is returned. If
 * the disk directory is full, -1 is returned, and if the disk was filled while
 * writing the file -2 is returned. Otherwise, the number of sectors written is
 * given.
 */
int fcopy(char *src, char *dest)
{
	//try and load the file
	char buf[13312];
	//the size in sectors of src
	int f = fopen(src, buf, 13312);
	if (fopen(src, buf, 13312) == -1) {
		//file not found
		return -3;
	} else {
		//write the file (f is the size in sectors of src)
		return fwrite(dest, buf, f);
	}
}

/*
 * Create a symbolic link. This will return -1 if the file to
 * link to does not exist, -2 if the disk directory is full, or
 * 1 if it was sucessful.
 */
int link(char *fname, char *lname)
{
	return interrupt(0x21,0xA0,fname,lname,0);
}

