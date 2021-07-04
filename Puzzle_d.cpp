#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8

int nField[FIELD_WIDTH][FIELD_HEIGHT];
int nCursorX, nCursorY;

void display() {
	system("cls");
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if ((x == nCursorX) && (y == nCursorY))
				printf("　");
			else
				printf("〇");
		}
		printf("\n");
	}
}

int main()
{
	time_t t = time(NULL);

	while (1) {
		if (t < time(NULL)) {
			t = time(NULL);

			display();
		}

		if (_kbhit()) {
			switch (_getch()) {
			case 'w': nCursorY--; break;
			case 's': nCursorY++; break;
			case 'a': nCursorX--; break;
			case 'd': nCursorX++; break;
			}
			display();
		}
	}
}
