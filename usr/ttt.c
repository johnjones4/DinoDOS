/*
 * This is a VGA tic-tac-toe version for dinoDOS. Instructions can found in
 * the ingame help menu.
 *
 * Authors: John Jones and Russell Toris
 * Version: March. 28, 2010
 */

#include "lib/vga.h"
#include "lib/string.h"
#include "lib/stdio.h"
#include "lib/sys.h"
#include "ttt.h"

//padding used the the table cells
int padding = 5;
//size in pixels of the board width
int gridSize = 30;
//color of the board lines
int board_color = WHITE;
//the game board
char grid[3][3];

main() {
	enableInterrupts();
	begining:
	//display the welcome message and menu
	welcome();
	//enable VGA mode
	setVGAMode();
	//start the game play
	play();
	//go back to the main menu
	setTextMode();
	goto begining;

	//end of the game
	terminate();
}

/*
 * Prings the welcome information when the game starts. This will have a basic
 * texted based menu system.
 */
void welcome()
{
	int i; //counter
	char c; //holds current character
	begin_welcome:
	//clear the screen
	clear_scr();
	dino_print("Windows 1.0 may have had Reversi, but dinoDOS has...\n\n\0");
	//center the next line (pad with spaces)
	for(i=0; i<34; i++) {
		dino_print(" \0");
	}
	dino_print("+-----------+\n\0");
	for(i=0; i<34; i++) {
		dino_print(" \0");
	}
	dino_print("|TIC-TAC-TOE|\n\0");
	for(i=0; i<34; i++) {
		dino_print(" \0");
	}
	dino_print("+-----------+\n\0");

	//print the menu
	dino_print("\nMain Menu:\n\0");
	dino_print("(h) - Help and Instructions\n\0");
	dino_print("(s) - Start the Game\n\0");
	dino_print("(q) - Quit\n\0");
	//wait for a correct key
	c = getchar();
	while(c != 'q' && c != 's' && c != 'h') {
		c = getchar();
	}

	//check which key was entered
	if (c == 'q') {
		//clear the screen
		clear_scr();
		//quit
		terminate();
	} else if (c == 'h') {
		//clear the screen
		clear_scr();
		//print the help screen
		printHelp();
		dino_print("\nPress any key to continue...\0");
		//wait for a key to be pressed
		getchar();
		//reprint the welcome screen
		goto begin_welcome;
	}
	//otherwise c == s so just continue onto the game!
}

/*
 * Prints the help menu for the game. This has basic instructions on how to play
 * the game.
 */
void printHelp()
{
	//print the help menu
	dino_print("- Tic-Tac-Toe Help and Instructions -\n\n\0");
	dino_print("Welcome to dinoDOS Tic-Tac-Toe.\nWhen playing the game, \0");
	dino_print("use the following keys to mark the desired cell:\n\n\0");
	//draw out the table for key mappings
	dino_print(" q | w | e\n\0");
	dino_print("---+---+---\n\0");
	dino_print(" a | s | d\n\0");
	dino_print("---+---+---\n\0");
	dino_print(" z | x | c\n\0");
	dino_print("\nBe the first player to get 3 in a row and you win!\n\0");
}

/*
 * Start the game play. This function is terminated when the board is filled, or
 * when a player has won.
 */
void play()
{
	//X goes first
	char turn = 'X';
	//current number of moves
	int moves = 0;
	
	//draw the board
	initializeGame();
	//go until we find a winner or the board is filled
	while(!winner() && moves < 9) {
		//the current user input
		char c;
		int row, col;
		//wait until we get a valid charter
		while(!validChar(c = getchar()));
		
		//map the character to a row and column
		if(c == 'q' || c == 'w' || c == 'e') {
			//first row
			row = 0;
		} else if(c == 'a' || c == 's' || c == 'd') {
			//second row
			row = 1;
		} else {
			//third row
			row = 2;
		}
		//column check
		if(c == 'q' || c == 'a' || c == 'z') {
			//first col
			col = 0;
		} else if(c == 'w' || c == 's' || c == 'x') {
			//second col
			col = 1;
		} else {
			//third col
			col = 2;
		}
		
		//check if that space is free, otherwise loop goes again
		if (grid[row][col] == '\0') {
			//mark that spot
			grid[row][col] = turn;
			//draw it an change turns
			if (turn == 'X') {
				drawX(row,col);
				turn = 'O';
			} else if (turn == 'O') {
				drawO(row,col);
				turn = 'X';
			}
			//add the the move count
			moves++;
		}
	}
	//after the game is over, wait for the user to press any key to end
	getchar();
}

/*
 * Initializes the game board and draws the grid to the screen
 */
void initializeGame() {
	int r, c;
	//actual size of the board in pixels
	int gridTotal = (gridSize+(2*padding));
	//initilize the array to nulls
	for(r=0;r<3;r++) {
		for(c=0;c<3;c++) {
			grid[r][c] = '\0';
		}
	}
	//draw out the board
	line(padding,padding+gridTotal,padding+gridTotal*3,
		padding+gridTotal,board_color);
	line(padding,padding+gridTotal*2,padding+gridTotal*3,
		padding+gridTotal*2,board_color);
	line(padding+gridTotal,padding,padding+gridTotal,
		padding+gridTotal*3,board_color);
	line(padding+gridTotal*2,padding,padding+gridTotal*2,
		padding+gridTotal*3,board_color);
}

/*
 * Checks if the key entered is a valid key for the game. Returns 1 if it is, or
 * 0 if it is not.
 */
int validChar(char c)
{
	//check if it is q,w,e,a,s,d,z,x,or c
	return (c=='q'||c=='w'||c=='e'||c=='a'||c=='s'||
		c=='d'||c=='z'||c=='x'||c=='c');
}

/*
 * Draw an X in the cell with the given row and column.
 */
void drawX(int r,int c)
{
	//actual size of the board in pixels
	int gridTotal = (gridSize+(2*padding));
	int x = padding + gridTotal * c;
	int y = padding + gridTotal * r;
	x+= padding;
	y+= padding;
	//draw out the X
	line(x,y,x+gridSize,y+gridSize,BLUE);	
	line(x,y+gridSize,x+gridSize,y,BLUE);
}

/*
 * Draw an O in the cell with the given row and column.
 */
void drawO(int r,int c)
{
	//actual size of the board in pixels
	int gridTotal = (gridSize+(2*padding));
	int x = padding + gridTotal * c;
	int y = padding + gridTotal * r;
	x += padding + (gridSize / 2);
	y += padding + (gridSize / 2);
	//draw the circle
	circle(x,y,gridSize/2,GREEN);
}

/*
 * Checks if there is a winner get using the standard tic-tac-toe rules. Returns
 * 1 if a winner was found, and 0 if not.
 */
int winner()
{
	int i,j;
	//check rows and cols first
	for(i=0;i<3;i++) {
		//check the rows then the columns
		if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] 
		     && grid[i][0] != '\0') {
			//draw the winning line
			drawWinner(0,i,2,i);
			return 1;
		} else if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] 
		     && grid[0][i] != '\0') {
			//draw the winning line
			drawWinner(i,0,i,2);
			return 1;
		}
	}
	//now check the diagonals
	if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] 
	     && grid[0][0] != '\0') {
		//draw the winning line
		drawWinner(0,0,2,2);
		return 1;
	} else if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] 
	     && grid[1][1] != '\0') {
		//draw the winning line
		drawWinner(2,0,0,2);
		return 1;
	}
	
	//no winner found
	return 0;
}

/*
 * Draws a line connecting the cells with the given rows and columns.
 */
void drawWinner(int r0,int c0,int r1,int c1)
{
	//actual size of the board in pixels
	int gridTotal = (gridSize+(2*padding));
	int x = padding + gridTotal * r0;
	int y = padding + gridTotal * c0;
	int x1 = padding + gridTotal * r1;
	int y1 = padding + gridTotal * c1;
	x+= padding + (gridSize / 2);
	y+= padding + (gridSize / 2);
	x1+= padding + (gridSize / 2);
	y1+= padding + (gridSize / 2);
	line(x,y,x1,y1, RED);
}
