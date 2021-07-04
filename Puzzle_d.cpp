#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8
#define DROP_TYPE_MAX 7

enum {
	TYPE_NONE,
	TYPE_DROP_0,
	TYPE_DROP_1,
	TYPE_DROP_2,
	TYPE_DROP_3,
	TYPE_DROP_4,
	TYPE_DROP_5,
	TYPE_DROP_6,
	TYPE_MAX
};

char cTypes[][2 + 1] = {
	"　", // TYPE_NONE,
	"〇", // TYPE_DROP_0,
	"◎", // TYPE_DROP_1,
	"□", // TYPE_DROP_2,
	"☆", // TYPE_DROP_3,
	"◇", // TYPE_DROP_4
	"●", // TYPE_DROP_5,
	"△", // TYPE_DROP_6,
};

int nField[FIELD_WIDTH][FIELD_HEIGHT];
int nCursorX, nCursorY;

void display() {
	system("cls");
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if ((x == nCursorX) && (y == nCursorY))
				printf("  ");
			else
				printf("%s", cTypes[nField[x][y]]);
		}
		printf("\n");
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++)
			nField[x][y] = TYPE_DROP_0 + rand() % DROP_TYPE_MAX;

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