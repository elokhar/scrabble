#include<stdio.h>
#include<cstdlib>
#include"conio2.h"

#define LEGENDX 2
#define LEGENDY 2
#define BOARDX 40
#define BOARDY 10
#define BOARDSIZE 15
#define BOARDCOLOR LIGHTCYAN
#define TILECOLOR YELLOW
#define DEAFULTTEXT WHITE 
#define GAMEBACKGROUND BLACK
#define RIGHT 0
#define DOWN 1


/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

struct board_t {
	char color;
	char bonustype;
	char bonusvalue;
	char letter;
};

struct word_t {
	char letter;
	bool onRack;
};

struct tile_t {
	char letter;
	bool used = 0;
};

void move(int *xp, int *yp, int xlength, int ylength);

void cleanboard(struct board_t board[BOARDSIZE][BOARDSIZE]);

int displaylegend(int zero, int zn, int x, int y);

void displaygameinfo(int gamex, int gamey, const tile_t *tile, int tiles)
{
	//sprintf_s(txt, "Your tiles: %c %c %c %c %c %c %c", tile[0].letter, tile[1].letter, tile[2].letter, tile[3].letter, tile[4].letter, tile[5].letter, tile[6].letter);
	gotoxy(gamex, gamey);
	cputs("Your tiles: ");
	for (int i = 0; i < tiles; i++)
		if (tile[i].used == 0)
		{
			putch(tile[i].letter);
			putch(' ');
		}
			
}

void displayboard(struct board_t board[BOARDSIZE][BOARDSIZE]);

void enterword(tile_t tile[], int tiles, board_t board[BOARDSIZE][BOARDSIZE]);

bool canPlace(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength);

void putword(word_t word[], tile_t tile[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength);

bool canPlaceRight(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength, int x, int y);

bool canPlaceDown(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength, int x, int y);

void placeword(word_t word[], tile_t tile[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength, int orientation, int x, int y)
{
	if (orientation == RIGHT)
		for (int j = 0; j < wordlength; j++)
		{
			board[x + j][y].letter = word[j].letter;
			board[x + j][y].color = TILECOLOR;
		}
	else
		for (int j = 0; j < wordlength; j++)
		{
			board[x][y + j].letter = word[j].letter;
			board[x][y + j].color = TILECOLOR;
		}
	//for (int i = 0; i < wordlength; i++)
		//if (tile[i].used = 1) tile[i].letter = ' ';
}

int main() {
	int zn = 'n', letter = 0,  x = BOARDX + BOARDSIZE / 2, y = BOARDY + BOARDSIZE / 2, attr = BLACK, back = BOARDCOLOR, zero = 0;
	char stile[] = { 'a','a','o','c','d','g','t' }; //represents player's starting tiles
	const int tiles = sizeof(stile);
	tile_t tile[tiles];						//represents player's current tiles
	struct board_t board[BOARDSIZE][BOARDSIZE];

	
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Piotr Wojciechowski 175757");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	do {
		
		textbackground(GAMEBACKGROUND);		
		clrscr();
		
				
		if (zn == 'n')
		{
			for (int i = 0; i < tiles; i++)
				tile[i].letter = stile[i];
			cleanboard(board);
		}
			
		int gamey = displaylegend(zero, zn, x, y);

		displaygameinfo(LEGENDX, gamey + 2, tile, tiles);

		displayboard(board);

		gotoxy(x, y);

		if (zn == 'i')
			enterword(tile, tiles, board);
		

		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		putch('*');

		// we wait for key press and get its code
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if(zn == 0) {
			zero = 1;							
			move(&x, &y, 1, 1);
		} else if(zn == ' ') attr = (attr + 1) % 16;
		else if(zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends
	return 0;
}

void move(int *xp, int *yp, int xlength, int ylength)
{

	int zn = getch();
	if (zn == 72 && *yp > BOARDY) (*yp)--;
	else if (zn == 0x50 && *yp < BOARDY + BOARDSIZE - ylength) (*yp)++;
	else if (zn == 0x4b && *xp > BOARDX) (*xp)--;
	else if (zn == 0x4d && *xp < BOARDX + BOARDSIZE - xlength) (*xp)++;
}

void cleanboard(struct board_t board[BOARDSIZE][BOARDSIZE])
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			board[j][i].letter = ' ';
			board[j][i].color = BOARDCOLOR;
		}
}

void displayboard(struct board_t board[BOARDSIZE][BOARDSIZE])
{
	textcolor(BLACK);
	for (int i = 0; i < BOARDSIZE; i++) 
		for (int j = 0; j < BOARDSIZE; j++)
		{
			textbackground(board[j][i].color);
			gotoxy(BOARDX + j, BOARDY + i);
			putch(board[j][i].letter);
		}

	textbackground(DARKGRAY);
	for (int i = BOARDY - 1; i <= BOARDY + BOARDSIZE; i++)
	{
		gotoxy(BOARDX - 1, i);
		putch(' ');
		gotoxy(BOARDX + BOARDSIZE, i);
		putch(' ');
	}

	for (int i = BOARDX; i <= BOARDX + BOARDSIZE - 1; i++)
	{
		gotoxy(i, BOARDY - 1);
		putch(' ');
		gotoxy(i, BOARDY + BOARDSIZE);
		putch(' ');
	}
}


int displaylegend(int zero, int zn, int x, int y)
{
	char txt[32];
	textcolor(DEAFULTTEXT);
	int row = LEGENDY;
	gotoxy(LEGENDX, row++);
	cputs("Piotr Wojciechoski 175757 a b c d e");
	row++;
	gotoxy(LEGENDX, row++);
	cputs("q       = exit");
	gotoxy(LEGENDX, row++);
	cputs("cursors = moving");
	gotoxy(LEGENDX, row++);
	cputs("space   = change color");
	gotoxy(LEGENDX, row++);
	cputs("enter   = change background color");
	gotoxy(LEGENDX, row++);
	cputs("i       = put tile");
	gotoxy(LEGENDX, row++);
	cputs("n       = new game");
	gotoxy(LEGENDX, row++);
	cputs("o       = rotate word");
	gotoxy(LEGENDX, row++);
	// print out the code of the last key pressed
	if (zero) sprintf_s(txt, "key code: 0x00 0x%02x", zn);
	else sprintf_s(txt, "key code: 0x%02x", zn);
	row++;
	gotoxy(LEGENDX, row++);
	cputs(txt);
	// print out the coursor position
	sprintf_s(txt, "position: %c %d", 'A' + x - BOARDX, y - BOARDY + 1);	
	gotoxy(LEGENDX, row++);
	cputs(txt);
	return row;
}

void enterword(tile_t tile[], int tiles, board_t board[BOARDSIZE][BOARDSIZE])
{
	int zn, i = 0, k = 0;
	bool placed = 0;
	struct word_t word[BOARDSIZE];

	textbackground(GAMEBACKGROUND);
	textcolor(DEAFULTTEXT);
	gotoxy(LEGENDX, LEGENDY + 16);
	cputs("Enter a word: \n ");
	zn = getch();	  

	 
	for (int k = 0; k < BOARDSIZE; k++)
			word[k].onRack = 0;
	
	for (int k = 0; k < tiles; k++)
		tile[k].used = 0;

	while (zn != '\r')
	{		
		if (zn == '\b' && wherex() > 2)
		{
			textbackground(GAMEBACKGROUND);					
			putch('\b');
			putch(' ');
			putch('\b');
			i--;
			if (word[i].onRack)
			{
				for (int k = 0; k < tiles; k++)
				{
					if (tile[k].used == 1 && word[i].letter == tile[k].letter)
					{
						word[i].onRack = 0;						tile[k].used = 0;
					}
					if (word[i].onRack = 0) break;
				}
			}

		}
		if (zn >= 'a' && zn <= 'z' && i < BOARDSIZE)
		{
			word[i].letter = zn;
			for (int k = 0; k < tiles; k++)
			{
				if (tile[k].used == 0 && zn == tile[k].letter)
				{
					word[i].onRack = 1;
					tile[k].used = 1;
				}
				if (word[i].onRack) break;
			}
			if (word[i].onRack)
				textbackground(GREEN);
			else
				textbackground(RED);
			putch((char)word[i].letter);
			i++;
		}
		zn = getch();
	}	
	  if (canPlace(word,board,i))
		putword(word, tile, board, i);
}


bool canPlace(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength)
{
	int missing = 0;
	bool result = true;
	for (int j = 0; j < wordlength; j++)
	{
		if (word[j].onRack == 0)
		{
			missing++;

		}
	}
	if (board[BOARDSIZE / 2][BOARDSIZE / 2].letter == ' ' && missing == 0) return true;
	else
		for (int i = 0; i < BOARDSIZE; i++)  //szukamy pola zawieraj¹cego jedn¹ z liter
			for (int j = 0; j < BOARDSIZE; j++)
			{
				if (board[j][i].letter != ' ')
					for (int k = 0; k < wordlength; k++)  
						if (word[k].letter == board[j][i].letter) 
						{
							//sprawdzamy czy s³owo mo¿e przchodziæ przez to pole
							if (canPlaceRight(word, board, wordlength, j - k, i)) return true;
							if (canPlaceDown(word, board, wordlength, j, i - k)) return true;
						}																																			
			}
	return false;

	
}

void putword(word_t word[], tile_t tile[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength)
{
	int x = BOARDX + BOARDSIZE / 2;
	int y = BOARDY + BOARDSIZE / 2;
	int orientation = RIGHT;
	int xlength, ylength;
	int zn;
	bool canPlaceLetters = 1;
	do
	{
		canPlaceLetters = 1;
		displayboard(board);
		textbackground(TILECOLOR);
		if (orientation == RIGHT)
		{
			xlength = wordlength;
			ylength = 1;
			for (int j = 0; j < wordlength; j++)
			{
				gotoxy(x + j, y);
				if (board[x + j - BOARDX][y - BOARDY].letter == ' ' || board[x + j - BOARDX][y - BOARDY].letter == word[j].letter)
					textbackground(LIGHTGREEN);
				else
				{
					textbackground(RED);
					canPlaceLetters = 0;
				}
				putch(word[j].letter);
			}
		}
		else
		{
			xlength = 1;
			ylength = wordlength;
			for (int j = 0; j < wordlength; j++)
			{
				gotoxy(x, y + j);
				if (board[x - BOARDX][y + j - BOARDY].letter == ' ' || board[x - BOARDX][y + j - BOARDY].letter == word[j].letter)
					textbackground(LIGHTGREEN);
				else
				{
					textbackground(RED);
					canPlaceLetters = 0;
				}

				putch(word[j].letter);
			}
		}
		zn = getch();

		if (zn == 27) return;

		if (zn == 'o')
			orientation = (orientation + 1) % 2;

		if (zn == 0)
		{
			move(&x, &y, xlength, ylength);
		}
	} while (zn != '\r');
	if (orientation==RIGHT && canPlaceRight(word, board, wordlength, x-BOARDX, y-BOARDY))
		placeword(word, tile, board, wordlength, orientation, x - BOARDX, y - BOARDY);
	else if (orientation==DOWN && canPlaceDown(word, board, wordlength, x - BOARDX, y - BOARDY))
		placeword(word, tile, board, wordlength, orientation, x - BOARDX, y - BOARDY);


}

bool canPlaceRight(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength, int x, int y)
{
	bool letterOnBoard = 0;
	bool newLetter = 0;
	if (board[BOARDSIZE / 2][BOARDSIZE / 2].letter == ' ') //if this is the first move
	{
		if (y != BOARDSIZE / 2) return false;
		for (int i = 0; i < wordlength; i++)
			if (x + i == BOARDSIZE / 2) return true;
		return false;
			
	}
	else
	for (int l = 0; l < wordlength; l++) 
	{
		if (board[x + l][y].letter != ' ' && board[x + l][y].letter != word[l].letter)
			return false;
		if (board[x + l][y].letter == word[l].letter) letterOnBoard = 1;
		else newLetter = 1;
	}
	if (letterOnBoard && newLetter) return true;
	return false;
	
}

bool canPlaceDown(word_t word[], board_t board[BOARDSIZE][BOARDSIZE], int wordlength, int x, int y)
{
	bool letterOnBoard = 0;
	bool newLetter = 0;
	if (board[BOARDSIZE / 2][BOARDSIZE / 2].letter == ' ')
	{
		if (x != BOARDSIZE / 2) return false;
		for (int i = 0; i < wordlength; i++)
			if (y + i == BOARDSIZE / 2) return true;
		return false;

	}
	else
		for (int l = 0; l < wordlength; l++)
		{
			if (board[x][y+l].letter != ' ' && board[x][y+l].letter != word[l].letter)
				return false;
			if (board[x][y+l].letter == word[l].letter) letterOnBoard = 1;
			else newLetter = 1;
		}
	if (letterOnBoard && newLetter) return true;
	return false;
}