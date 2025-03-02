#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"

void printboard(char tab[99][99], int a, const int x, const int y) //printing of the board
{
	gotoxy(x, y);

	if (tab[0][0] != ' ')
	{
		putch(tab[0][0]);
	}
	else
	{
		putch(218);
	}
	
	for (int i = 1; i < a-1; i++)
	{
		if (tab[0][i] != ' ')
		{
			putch(tab[0][i]);
		}
		else
		{
			putch(194);
		}
	}

	if (tab[0][a-1] != ' ')
	{
		putch(tab[0][a-1]);
	}
	else
	{
		putch(191);
	}

	for (int i = 1; i < a-1; i++)
	{
		gotoxy(x, y + i);	//gotoxy(column, row)
		if (tab[i][0] != ' ')	// tab[row][column]
		{
			putch(tab[i][0]);
		}
		else
		{
			putch(195);
		}
		for (int j = 1; j < a-1; j++)
		{
			if (tab[i][j] != ' ')
			{
				putch(tab[i][j]);
			}
			else
			{
				putch(197);
			}
		}
		if (tab[i][a-1] != ' ')
		{
			putch(tab[i][a-1]);
		}
		else
		{
			putch(180);
		}
	}
	gotoxy(x, y - 1 + a);
	if (tab[a-1][0] != ' ')
	{
		putch(tab[a-1][0]);
	}
	else
	{
		putch(192);
	}
	for (int i = 1; i < a-1; i++)
	{
		if (tab[a-1][i] != ' ')
		{
			putch(tab[a-1][i]);
		}
		else
		{
			putch(193);
		}
	}
	
	if (tab[a-1][a-1] != ' ')
	{
		putch(tab[a-1][a-1]);
	}
	else
	{
		putch(217);
	}
}

bool breath(char tab[99][99], const char s, int rows, int cols, int size, bool pos[99][99]) //counting amount of breaths for stones
{
	pos[rows][cols] = true;
	if (rows > 0)
	{
		if (tab[rows - 1][cols] == ' ')
		{
			return true;
		}
		if (tab[rows - 1][cols] == s && pos[rows - 1][cols] == false)
		{
			if (breath(tab, s, rows - 1, cols, size, pos) == true)
			{
				return true;
			}
		}
	}

	if (cols > 0)
	{
		if (tab[rows][cols - 1] == ' ')
		{
			return true;
		}
		if (tab[rows][cols - 1] == s && pos[rows][cols - 1] == false)
		{
			if (breath(tab, s, rows, cols -1, size, pos) == true)
			{
				return true;
			}
		}
	}

	if (rows < size -1)
	{
		if (tab[rows + 1][cols] == ' ')
		{
			return true;
		}

		if (tab[rows + 1][cols] == s && pos[rows + 1][cols] == false)
		{
			if (breath(tab, s, rows + 1, cols, size, pos) == true)
			{
				return true;
			}
		}
	}

	if (cols < size - 1)
	{
		if (tab[rows][cols + 1] == ' ')
		{
			return true;
		}

		if (tab[rows][cols + 1] == s && pos[rows][cols + 1] == false)
		{
			if (breath(tab, s, rows, cols + 1, size, pos) == true)
			{
				return true;
			}
		}
	}
	return false;
}

char boardsize() //choosing size of the board
{
	char ch;
	gotoxy(20, 10);
	cputs("Choose the size of the board: ");
	gotoxy(20, 11);
	cputs("a  =  9x9");
	gotoxy(20, 12);
	cputs("b  =  13x13");
	gotoxy(20, 13);
	cputs("c  =  19x19");
	gotoxy(20, 14);
	cputs("d  =  custom");
	ch = getch();
	return ch;
}

bool put(bool turn_b, char board[99][99], const char b, const char w, int size, bool visited[99][99], int rows, int cols) //checking if putting a stone is possible and putting
{
	
	if (turn_b == true)
	{
		if (board[rows][cols] == ' ' && breath(board, b, rows, cols, size, visited))
		{
			board[rows][cols] = b;
			return true;
		}
	}
	else if (board[rows][cols] == ' ' && breath(board, w, rows, cols, size, visited))
	{
		board[rows][cols] = w;
		return true;
	}
	return false;
}

void clear_board(const int x, const int y, int a) //clearing the board
{
	for (int i = 0; i < a - 1; i++)
	{
		gotoxy(x, y+i);
		clreol();
	}
}

void removing(int size, char board[99][99], bool visited_remove[99][99], bool remove[99][99], int* score_b, int* score_w, const char b, const char w) // stones removing
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == w)
			{
				if (breath(board, w, i, j, size, visited_remove) == false)
				{
					remove[i][j] = true;
					(*score_b)++;
				}
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						visited_remove[i][j] = false;
					}
				}
			}
			else if (board[i][j] == b)
			{
				if (breath(board, b, i, j, size, visited_remove) == false)
				{
					remove[i][j] = true;
					(*score_w)++;
				}
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						visited_remove[i][j] = false;
					}
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (remove[i][j] == true)
			{
				remove[i][j] = false;
				board[i][j] = ' ';
			}
		}
	}
}

void size_coice(char choice, int* size) //setting the chosen size of the board
{
	if (choice == 'a')
	{
		*size = 9;
	}
	else if (choice == 'b')
	{
		*size = 13;
	}
	else if (choice == 'c')
	{
		*size = 19;
	}
	else if (choice == 'd')
	{
		clrscr();
		gotoxy(20, 10);
		cputs("input custom size (include 0 at numbers from 1 to 9, max 99): ");
		choice = getche();
		*size = choice - '0';
		choice = getche();
		*size = *size * 10 + choice - '0';
	}
}

void setting(int size, char board[99][99])//making a board full of spaces
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void newgame(bool* turn_b, int size, char board[99][99], int* score_b, int* score_w)//clearing the board and filling it with spaces
{
	*turn_b = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = ' ';
		}
	}
	*score_b = 0;
	*score_w = 0;
}

int main() {
	int zn = 0, x = 80, y = 7, attr = 7, back = 0, zero = 0;
	char txt[32];
	bool visited[99][99] = { false };
	int size = 1;
	int a = 20;
	int c = 10;
	const int boardx = x, boardy = y;
	char board[99][99];
	const char b = '$';
	const char w = '#';
	bool turn_b = true; 
	bool handicap_mode = false;
	char file_name[100];
	bool remove[99][99] = { false };
	bool visited_remove[99][99] = { false };
	char choice;
	int score_b = 0;
	int score_w = 0;
	int rows, cols;
	int choice_put;

	choice = boardsize();
	size_coice(choice, &size);
	setting(size, board);

#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Lukasz, Kornacki, 195613");
	_setcursortype(_NOCURSOR);
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		gotoxy(a, c);
		cputs("q       = exit");
		gotoxy(a, c + 1);
		cputs("cursors = moving");
		gotoxy(a, c + 2);
		cputs("space   = change color");
		gotoxy(a, c + 3);
		cputs("enter   = change background color");
		gotoxy(a, c + 5);
		cputs("n       = new game");
		gotoxy(a, c + 6);
		cputs("h       = handicap mode");
		gotoxy(a, c + 7);
		cputs("score of black: ");
		putch(score_b / 10 + '0');
		putch(score_b % 10 + '0');
		gotoxy(a, c + 8);
		cputs("score of white: ");
		putch(score_w / 10 + '0');
		putch(score_w % 10 + '0');
		gotoxy(a, c + 9);
		cols = x - boardx;
		rows = y - boardy;
		cputs("cursor cords: ");
		putch(rows / 10 + '0');
		putch(rows % 10 + '0');
		putch(' ');
		putch(cols / 10 + '0');
		putch(cols % 10 + '0');
		gotoxy(a, c + 10);
		cputs("$ - black, # - white");

		if (zero) sprintf(txt, "key code: 0x00 0x%02x", zn);
		else sprintf(txt, "key code: 0x%02x", zn);
		gotoxy(a, c + 4);
		cputs(txt);

		removing(size, board, visited_remove, remove, &score_b, &score_w, b, w);
		printboard(board, size, boardx, boardy);

		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);		
		putch('*');
		
		zero = 0;
		zn = getch();
		
		if (zn == 0) {
			zero = 1;		
			zn = getch();		
			if ((zn == 0x48) && (y > boardy)) y--;
			else if ((zn == 0x50) && (y < size - 1 + boardy)) y++;
			else if ((zn == 0x4b) && (x > boardx)) x--;
			else if (zn == 0x4d && x < size - 1 + boardx) x++;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16; 
		else if (zn == 'i')
		{
			if (put(turn_b, board, b, w, size, visited, rows, cols) == true)
			{
				clear_board(boardx, boardy, size);
				printboard(board, size, boardx, boardy);
				while (true)
				{
					choice_put = getch();
					if (choice_put == 0x1b) //esc
					{
						board[rows][cols] = ' ';
						break;
					}
					else if (choice_put == 0x0d) //enter
					{
						if (handicap_mode == false)
						{
							turn_b = !turn_b; // change of turn
						}
						break;
					}
					choice_put = 0;
				}
			}
		}
		else if (zn == 'n')
		{
			newgame(&turn_b, size, board, &score_b, &score_w);
		}
		else if (zn == 'h')
		{
			handicap_mode = !handicap_mode;
		}

	} while (zn != 'q');
	
	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be visible after the program ends
	return 0;
}