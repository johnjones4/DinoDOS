/*
 * This is the header file for the dinoDOS system libray. 
 *
 * Authors: John Jones and Russell Toris
 * Version: 0.3 March. 1, 2010
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
int interrupt(int irq, int ax, int bx, int cx, int dx);
int readLine(char *buf, int max);
int getChar();
int readFile(char *filename, char *buf, int max);
int readSector(byte *buf, int absSector);
void putInMemory(int segment, int offset, char b);
void putChar(char c, int row, int col, byte color);
void putStr(char* str, int row, int col, byte color);
void clearScreen();
void launchProgram(int segment);
void resetSegments();
int printString(char *str);
void printInt(int i);
int executeProgram(char* name, int wait, int priority);
void terminate();
int writeSector(byte *buf, int absSector);
int deleteFile(char *fname);
int dirEntryIndex(char *fname, struct directory *dir);
int writeFile(char *fname, char *buffer, int sectors);
int makeSymLink(char* fname,char* lname);
void initializeProgram(int segment);
void restoreDataSegment();
void setKernelDataSegment();
void yield();
void showProcesses();
int kill(int segment);
void sleep(int seconds);
