/*
 * A C header that functions as a wrapper for dinoDOS system calls.
 *
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 3, 2010
 */

int interrupt(int number, int ax, int bx, int cx, int dx);
int dino_print(char *str);
int dino_printint(int n);
int read_line(char *buf, int max);
int read_sect(char *buf, int sector);
int write_sect(char *buf, int sectors);
int fopen(char *filename, char *buf, int max);
int fdelete(char *fname);
int fwrite(char *fname, char *file, int sectors);
int fcopy(char *src, char *dest);
int getchar();
int link(char *fname, char *lname);
