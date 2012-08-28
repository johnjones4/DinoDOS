/*
 * A dinoDOS library for VGA graphics routines.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 31, 2010
 */

#include "vga.h"

/*
 * Enable VGA video mode.
 */
void setVGAMode()
{
	//enable VGA mode
	interrupt(0x10,0x0013,0,0,0);
}

/*
 * Enable teletype video mode. Should be called at the end of any program which
 * enables VGA mode.
 */
void setTextMode()
{
	//sets video to teletype mode
	interrupt(0x10,0x0003,0,0,0);
	//call a clear screen to reset color scheme
	interrupt(0x21,0xA1,0,0,0);
}

/*
 * Set the pixel with the x and y coordinates to the specifed color. See the
 * header file for valid colors. VGA mode should be enabled first before
 * using this function.
 */ 
void plot(int x, int y, int color)
{
	//get the actual AX value for the color (uses 0x0c00 as a base)
	int actualColor = 0x0C00 + color;
	//call int 10 to set a pixel in VGA mode.
	interrupt(0x10,actualColor,0,x,y);
}

/*
 * Plots a line from (x0, y0) to (x1, y1) with the given color.
 */
void line(int x0,int y0,int x1,int y1, int color)
{
	/*
	 * Line is drawn based on the Bresenham's line drawing algorithm.
	 * Implementation is a modification using the information from the
	 * University of North Carolina.
	 * http://www.cs.unc.edu/~mcmillan/comp136/Lecture6/Lines.html
	 */


	//we will use 2 * the difference to avoid needing the use of fractions
	int y_diff = 2 * (y1 - y0);
        int x_diff = 2 * (x1 - x0);
        int stepx = 1, stepy = 1;
	//our epsilon value
	int eps;

	//we always want to deal with the absolute vales of y_diff and x_diff
        if (y_diff < 0) { 
		//chage which way we are plotting
		stepy = -1;
		y_diff = -y_diff;
	}
        if (x_diff < 0) {
		//chage which way we are plotting
		stepx = -1;
		x_diff = -x_diff;
	}

	//plot our initial point
	plot(x0, y0, color);
	//two cases need to plot negative slopes
        if (x_diff > y_diff) {
		//update epsilon based on x_diff and y_diff are scaled by 2
		eps = 2*y_diff - x_diff;
		//go until our x's meet
		while (x0 != x1) {
			//check if its time to update our y cord
			if (eps >= 0) {
				//step y
				y0 += stepy;
				//update epsilon
		        	eps -= x_diff;
		        }
			//step x
		        x0 += stepx;
			//update epsilon
		        eps += y_diff;

			//plot our current point
		        plot(x0, y0, color);
		}
	} else {
		//update epsilon based on x_diff and y_diff are scaled by 2
		eps = 2*x_diff - y_diff;
		//go until our y's meet
		while (y0 != y1) {
			//check if its time to update our x cord
                	if (eps >= 0) {
				//step x
                    		x0 += stepx;	
				//update epsilon
                    		eps -= y_diff;
                	}
			//step y
                	y0 += stepy;
			//update epsilon
                	eps += x_diff;

			//plot our current point
		        plot(x0, y0, color);
            	}
        }
}

void rect(int x,int y,int width,int height, int color)
{
	line(x,y,x+width,y,color);
	line(x,y,x,y+height,color);
	line(x+width,y,x+width,y+height,color);
	line(x,y+height,x+width,y+height,color);
}

void circle(int x0, int y0, int radius, int color)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  plot(x0, y0 + radius, color);
  plot(x0, y0 - radius, color);
  plot(x0 + radius, y0, color);
  plot(x0 - radius, y0, color);
 
  while(x < y)
  {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    plot(x0 + x, y0 + y, color);
    plot(x0 - x, y0 + y, color);
    plot(x0 + x, y0 - y, color);
    plot(x0 - x, y0 - y, color);
    plot(x0 + y, y0 + x, color);
    plot(x0 - y, y0 + x, color);
    plot(x0 + y, y0 - x, color);
    plot(x0 - y, y0 - x, color);
  }
}
