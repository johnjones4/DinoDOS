/*
 * This is an extension of the shell allows the creation of users as well as
 * validates users.
 *
 * Authors: John Jones and Russell Toris
 * Version: April. 28, 2010
 */

#include "shell_users.h"

char *usr_file = "usrs\0";

void create_user(char *usr, char *pwd)
{
	int i,j;
	struct user users[32]; //user directory
	//try and load the user file
	if (fopen(usr_file, users, 512) == -1) {
		//file does not exist, set entire buffer to 0x01
		for(i=0; i<32; i++) {
			for(j=0; j<8; j++) {
				users[i].usr[j] = 0x01;
				users[i].pwd[j] = 0x01;
			}
		}
	}

	//try to find a free spot in the user directory
	for(i=0; i<32; i++) {
		//check if it is empty
		if(users[i].usr[0] == 0x01) {
			int ret;
			//encrypt the password
			encrypt(usr, pwd);
			//copy the name and password
			strcpy(users[i].usr, usr);
			strcpy(users[i].pwd, pwd);
			//remove the null terminator
			users[i].usr[strlen(users[i].usr)] = 0x01;
			users[i].pwd[strlen(users[i].pwd)] = 0x01;
			//write the file back
			ret = fwrite(usr_file, users, 1);
			//check if it was successful
			if (ret == -2) {
				dino_print("Error: disk is full.\n\0");
			} else if (ret == -1) {
				dino_print("Error: disk directory is full.\n\0");
			}
			return;
		}
	}
}

bool validate()
{
	char usr[9];
	char pwd[9];
	struct user users[32]; //user directory
	//ask for a username and password
	dino_print("username: \0");
	read_line(usr, 8);
	dino_print("\npassword: \0");
	read_line(pwd, 8);
	dino_print("\n\0");

	//try and load the user file
	if (fopen(usr_file, users, 512) == -1) {
		//file does not exist
		dino_print("ERROR: NO USERS FILE FOUND ON SYSTEM.\0");
		dino_print(" CONTACT SYSTEM ADMINISTRATOR.\n\0");
		return FALSE;
	} else {
		int i,j;
		//check for matches
		for(i=0; i<32; i++) {
			//replace 0x01 with NULL
			for(j=0; j<8; j++) {
				if(users[i].pwd[j] == 0x01) {
					users[i].pwd[j] = 0x00;
				}
				if(users[i].usr[j] == 0x01) {
					users[i].usr[j] = 0x00;
				}
			}
			//decrypt the password
			decrypt(users[i].usr, users[i].pwd);
			//check for a match
			if(strcmp(users[i].usr, usr) == 0 && strcmp(users[i].pwd, pwd) == 0) {
				return TRUE;
			}
		}
		//never found a match
		return FALSE;
	}
}

void encrypt(char *usr, char *pwd)
{
	int i;
	//change all the ASCII values
	for(i=0; i<strlen(pwd); i++) {
		pwd[i] += 3;
	}
}

void decrypt(char *usr, char *pwd)
{
	int i;
	//change all the ASCII values back
	for(i=0; i<strlen(pwd); i++) {
		pwd[i] -= 3;
	}
}
