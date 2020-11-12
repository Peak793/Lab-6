#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("0");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_enemy(int x, int y)
{
	gotoxy(x, y); printf("*");
}
void updatescore(long long score)
{
	gotoxy(0, 0); printf("                                                      ");
	gotoxy(0, 0); printf("Score = %lld",score);
}
int main()
{
	srand(time(NULL));
	setcursor(false);
	int color = 0;
	int n = 0;
	int ex = 0, ey = 0;
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	unsigned long long score = 0;
	printf("Score = %lld",score);
	draw_ship(x, y);
	do {
		if (n < 20)
		{
			for (int i = 0; i < 20 - n; i++)
			{
				do
				{
					color = rand() & 15;
				} while (color == 0);
				setcolor(color, 0);
				do {
					ex = rand()%71;
				} while (ex < 10);
				do {
					ey = rand() % 6;
				} while (ey<2);
				draw_enemy(ex, ey);
				n++;
			}
		}
		setcolor(15,0);
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { Beep(4000, 100); bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}

		if (bullet == 1) {

			clear_bullet(bx, by);
			if (by <= 2) { bullet = 0; clear_bullet(bx, by-1); }
			else if (cursor(bx, by - 1) !='*'){ draw_bullet(bx, --by); }
			else {
				bullet = 0;
				n--;
				Beep(700, 100);
				clear_bullet(bx, by);
				clear_bullet(bx, by-1);
				score += 100;
				updatescore(score);
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
