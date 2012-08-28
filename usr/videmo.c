/*
 * This is a simple user program to print a table with the 256 possible colors
 * in VGA mode.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#include "lib/vga.h"

//void enableInterrupts();

//the size of each cell in the table in pixels (a size x size square)
int size = 12;

void showColors();
void showAnimation();

main() {
	enableInterrupts();
	//enable VGA mode
	setVGAMode();
	
	showColors();
	showAnimation();
	
	//switch back and terminate
	setTextMode();
	clear_scr();
	terminate();
}

void showColors()
{
	//counters
	int h, i, j, k, color=0;
	//print a 16x16 grid of size x size squares for each color
	for(h=0; h<16; h++) {
		for(i=0; i<size; i++) {
			for(j=0; j<16; j++) {
				for(k=0; k<size; k++) {
					plot(k+(size*j), i+(size*h), color);
				}
				color++;
			}
			color -= j;
		}
		color += 16;
	}
	//wait for user input to terminate
	getchar();
}

void showAnimation()
{
	char lastchar;
	int x = 100;
	int y = 100;
	int dx = 1;
	int dy = 1;
	int count = 0;
	setVGAMode();
	
	while (count < 500)
	{
		circle(x,y,10,15);
		x += dx;
		y += dy;
		if (x < 0)
			dx = 1;
		if (y < 0)
			dy = 1;
		if (x > 500)
			dx = -1;
		if (y > 100)
			dy = -1;
		count++;
		setVGAMode();
	}
}
