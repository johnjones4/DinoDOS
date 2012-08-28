/*
 * A simple program to dump the disk directory to the screen. 
 *
 * Authors: John Jones and Russell Toris
 * Version: 'March. 28, 2010
 */

#include "ddump.h"
#include "lib/sys.h"
#include "lib/stdio.h"


void printHex(byte b);

int main()
{
	struct directory diskDir;
	int i;
	enableInterrupts();
	read_sect((byte *)&diskDir, 2);	
	
	for(i = 0; i < 16; i++) {
		int k;
		if (diskDir.entries[i].name[0] != '\0') {
			char curName[8];
			int j;
			for(j = 0; j < 6; j++) {
				if (diskDir.entries[i].name[j] != '\0') {
					curName[j] = diskDir.entries[i].name[j];
				} else {
					curName[j] = ' ';
				}

			}
			curName[6] = '\t';
			curName[7] = '\0';
			dino_print(curName);
		} else {
			dino_print("EMPTY \t\0");
		}
			
		for (k=0; k < 26; k++) {
			dino_print(" \0");
			dino_printint(diskDir.entries[i].sector[k]);
		}
		dino_print("\n\0");
	}
	
	
	terminate();
}

void printHex(byte b) {
	byte ch = b;
    int i = 0; 
	char out[3];
	
	char pseudo[17];
	pseudo[0] = '0';
	pseudo[1] = '1';
	pseudo[2] = '2';
	pseudo[3] = '3';
	pseudo[4] = '4';
	pseudo[5] = '5';
	pseudo[6] = '6';
	pseudo[7] = '7';
	pseudo[8] = '8';
	pseudo[9] = '9';
	pseudo[10] = 'A';
	pseudo[11] = 'B';
	pseudo[12] = 'C';
	pseudo[13] = 'D';
	pseudo[14] = 'D';
	pseudo[15] = 'E';
	pseudo[16] = 'F';
	
	//char pseudo[] = {'0', '1', '2',
	//	'3', '4', '5', '6', '7', '8',
	//	'9', 'A', 'B', 'C', 'D', 'E',
	//	'F'};
	
	//high nibble
	
	ch = (ch >> 4);
	// shift the bits down
	
	ch = (byte) (ch & 0x0F);    
	// must do this is high order bit is on!
	
	out[0] = pseudo[(int) ch];
	
	ch = (byte) (b & 0x0F); // Strip off
	
	out[1] = pseudo[(int) ch];
	
	out[2] = '\0';
	dino_print(out);
}
