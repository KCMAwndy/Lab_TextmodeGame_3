#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}
void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y) {
	gotoxy(x, y);
	printf(" <-0-> ");
}
void draw_bullet(int x, int y) {
	gotoxy(x, y);
	printf("0");
}
void draw_star() {
	int sx = rand() % 61 + 10;
	int sy = rand() % 4 + 2;
	gotoxy(sx, sy);
	if (cursor(sx, sy) == '*') {
		draw_star();
	}
	else {
		printf("*");
	}
}
void clear_bullet(int x, int y) {
	gotoxy(x, y);
	printf(" ");
}
void clear_star(int x, int y) {
	gotoxy(x, y);
	printf(" ");
}
void updateScore(int* x) {
	gotoxy(0, 0);
	*x = *x + 1;
	printf("SCORE : %d", *x);
}
int main() {
	srand(time(NULL));
	char ch = ' ';
	int x = 38, y = 20, score = -1;
	int bx, by, i = 0;
	int bullet = 0;
	updateScore(&score);
	for (i = 1; i <= 20; i++) {
		draw_star();
	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) {
				//Beep(500, 500);
				draw_ship(--x, y);
			}
			if (ch == 'd' && x < 73) {
				//Beep(500, 500);
				draw_ship(++x, y);
			}
			if (bullet != 1 && ch == ' ') {
				//Beep(900, 500);
				bullet = 1;
				bx = x + 3;
				by = y - 1;
			}
			fflush(stdin);
		}
		if (bullet == 1) {
			clear_bullet(bx, by);
			if (by == 2) {
				bullet = 0;
			}
			else {
				if (cursor(bx, by - 1) == '*') {
					Beep(1000, 300);
					clear_star(bx, by - 1);
					clear_bullet(bx, by);
					draw_star();
					Sleep(500);
					updateScore(&score);
					bullet = 0;
				}
				else {
					draw_bullet(bx, --by);
				}
			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
