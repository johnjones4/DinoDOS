/*
 * This is a simple program to add out magic number to files. The magic number
 * is check for in the kernel to see if a program is executable. Our magic
 * number is the two characters "rj" for Russell and John.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 20, 2010
 */


#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE *source, *dest;

	//check the arguments
	if (argc<2) {
		printf("Error: Missing parameters.\n");
		printf("  Use: markExecutable 'file_name'\n");
		return;
	}

	//open the original file
	if ((source = fopen(argv[1], "rb")) == 0) {
		printf("File '%s' not found.\n", argv[1]);
		return;
	}

	//create the new file
	dest = fopen("tmp_file", "wb");

	//place magic number in ("rj" for Russell and John)
	fputc('r', dest);
	fputc('j', dest);

	//copy the file
	int c;
	//get the file char by char
	while ((c = fgetc(source)) != EOF) {
		//check for write errors as we go
		if(fputc(c, dest) == EOF) {
			printf("Error writing to file.");
			//close the file
			fclose(source);
			//delete the destintation file
			remove("tmp_file");
			return;
		}
	}

	//close the files
	fclose(source);
	fclose(dest);

	//delete the original file
	remove(argv[1]);
	//rename the new file to the original name
	rename("tmp_file", argv[1]);
}
