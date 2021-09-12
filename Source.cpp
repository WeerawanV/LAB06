#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<conio.h>

void gotoxy(int x, int y) {
	COORD c = { x,y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(3, 7);
	printf(" <-0-> ");
}

void draw_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(7, 0);
	printf("^");
}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}

void erase_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

int main() {
	int x = 38, y = 20; //ship(x,y)
	int bx[5], by[5], i; //bullet(x,y)
	int bulletStatus[5] = { 0,0,0,0,0 };
	char ch = ' ';
	int direction = 0;
	int status = 0; // 1 = on , 0 = off
	setcursor(0);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				direction = 1; //left
			}
			if (ch == 'd') {
				direction = 2; //right
			}
			if (ch == 's') {
				direction = 0; //stop
			}
			if (ch == ' ' && bulletStatus[status] == 0) {
				bulletStatus[status] = 1;
				bx[status] = x + 3; //setting default value
				by[status] = y - 1;
				status++; //declare every index
				status %= 5; //reset status ==> 0 ; for aim 5 bullets again
			}
			fflush(stdin);
		}
		Sleep(100);
		if (direction == 1 && x >= 1) {
			erase_ship(x, y);
			draw_ship(--x, y);
			Sleep(250);
		}
		if (direction == 2 && x <= 80) {
			erase_ship(x, y);
			draw_ship(++x, y);
			Sleep(250);
		}
		for (i = 0; i < 5; i++) { //to aim 5 bullets per 1 screen
			if (bulletStatus[i] == 1) {
				erase_bullet(bx[i], by[i]);
				if (by[i] < 1) { 
					bulletStatus[i] = 0;
				}
				else {
					draw_bullet(bx[i], --by[i]);
				}
			}
		}
	} while (ch != 'x');
	return 0;
}