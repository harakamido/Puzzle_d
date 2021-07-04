#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int nCheck[FIELD_WIDTH][FIELD_HEIGHT];
int nCursorX, nCursorY;
int nSelectX = -1, nSelectY = -1;
bool bLocked = true;

int getDropCount(int x, int y, int type, int count) {
	if ((x < 0) || (x >= FIELD_WIDTH)
		|| (y < 0) || (y >= FIELD_HEIGHT)
		|| nCheck[x][y] || (nField[x][y] == TYPE_NONE) || (nField[x][y] != type))
		return count;

	count++;
	nCheck[x][y] = true;

	count = getDropCount(x, y - 1, type, count);
	count = getDropCount(x - 1, y, type, count);
	count = getDropCount(x, y + 1, type, count);
	count = getDropCount(x + 1, y, type, count);

	return count;
}

void deleteDrop(int x, int y, int type) {
	if ((x < 0) || (x >= FIELD_WIDTH)
		|| (y < 0) || (y >= FIELD_HEIGHT)
		|| (nField[x][y] == TYPE_NONE) || (nField[x][y] != type))
		return;

	nField[x][y] = TYPE_NONE;

	deleteDrop(x, y - 1, type);
	deleteDrop(x - 1, y, type);
	deleteDrop(x, y + 1, type);
	deleteDrop(x + 1, y, type);
}

void deleteDropAll() {
	memset(nCheck, 0, sizeof(nCheck));

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			int n = getDropCount(x, y, nField[x][y], 0);
			if (n >= 3) {
				deleteDrop(x, y, nField[x][y]);
				bLocked = true;
			}
		}
	}
}

void display() {
	system("cls");
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if ((x == nCursorX) && (y == nCursorY) && (!bLocked))
				printf("  ");
			else
				printf("%s", cTypes[nField[x][y]]);
		}
		if (y == nSelectY)
			printf("←");
		printf("\n");
	}
	for (int x = 0; x < FIELD_WIDTH; x++)
		printf("%s", (x == nSelectX) ? "↑" : "  ");
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

			if (bLocked) {
				bLocked = false;
				for (int y = FIELD_HEIGHT - 2; y >= 0; y--) {
					for (int x = 0; x < FIELD_WIDTH; x++) {
						if ((nField[x][y] != TYPE_NONE) && (nField[x][y + 1] == TYPE_NONE)) {
							nField[x][y + 1] = nField[x][y];
							nField[x][y] = TYPE_NONE;
							bLocked = true;
						}
					}
				}

				if (!bLocked)
					deleteDropAll();
			}
			display();
		}

		if (_kbhit()) {
			if (bLocked) {
				_getch();
			}
			else {
				switch (_getch()) {
				case 'w': nCursorY--; break;
				case 's': nCursorY++; break;
				case 'a': nCursorX--; break;
				case 'd': nCursorX++; break;
				default:
					if (nSelectX < 0) {
						nSelectX = nCursorX;
						nSelectY = nCursorY;
					}
					else {
						int temp = nField[nCursorX][nCursorY];
						nField[nCursorX][nCursorY] = nField[nSelectX][nSelectY];
						nField[nSelectX][nSelectY] = temp;

						deleteDropAll();

						nSelectX = nSelectY = -1;
						bLocked = true;
					}
					break;
				}
				display();
			}
		}
	}
}