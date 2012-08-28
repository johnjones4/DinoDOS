/*
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

typedef char byte;

struct dirEntry {
	char name[6];
	byte sector[26];
};

struct directory {
	struct dirEntry entries[16];
};

void printHex(byte b);
void enableInterrupts();
