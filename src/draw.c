#include "draw.h"
#include "ludo.h"

#include <stdio.h>

static char fullMap[15][15];

static u8 houseCords[4][2] = {{0, 0}, {9, 0}, {0, 9}, {9, 9}};

#define HOUSE_CHAR ' ' // Clean

void drawHouse(u8 x, u8 y) {
  for (u32 i = y, j = x; j < x + 6; j++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u32 i = y + 5, j = x; j < x + 6; j++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u32 i = y + 1, j = x; i < y + 6; i++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u32 i = y + 1, j = x + 5; i < y + 6; i++)
    PLACE(HOUSE, fullMap[i][j]);
}

// TODO: rewrite using bit flags
void drawCenter() {
  fullMap[6][6] = HOUSE_CHAR;
  fullMap[6][8] = HOUSE_CHAR;
  fullMap[8][6] = HOUSE_CHAR;
  fullMap[8][8] = HOUSE_CHAR;

  fullMap[7][7] = HOUSE_CHAR;
}

// TODO: rewrite using bit flags
void drawMiddleLines() {
  for (u8 i = 1; i < 6; i++)
    if (IS_EMPTY(fullMap[7][i]))
      fullMap[7][i] = '/';

  for (u8 i = 9; i < 14; i++)
    if (IS_EMPTY(fullMap[7][i]))
      fullMap[7][i] = '/';

  for (u8 i = 1; i < 6; i++)
    if (IS_EMPTY(fullMap[i][7]))
      fullMap[i][7] = '/';

  for (u8 i = 9; i < 14; i++)
    if (IS_EMPTY(fullMap[i][7]))
      fullMap[i][7] = '/';
}

void initMap() {
  for (u8 i = 0; i < sizeof(houseCords) / sizeof(*houseCords); i++)
    drawHouse(houseCords[i][0], houseCords[i][1]);

  // drawCenter();
  // drawMiddleLines();
}

void setHousePieces(const Game *game) {
  for (u8 n = 0; n < sizeof(houseCords) / sizeof(*houseCords); n++) {
    for (u8 i = 0; i < 4; i++)
      if (game->players[n].locations[i] == LOCKED) {
        fullMap[houseCords[n][1] + 2 + i / 2][houseCords[n][0] + 2 + i % 2] =
        i + PIECE;
      }
  }
}

void placeMapPieces(const Game *game) {
  for (u8 i = 0; i < 6; i++)
    fullMap[6][i] = game->map[i];
}

void drawMap(const Game *game) {
  setHousePieces(game);
  placeMapPieces(game);
};

void displayGame() {
  for (u32 y = 0; y < sizeof(fullMap) / sizeof(*fullMap); y++) {
    for (u32 x = 0; x < sizeof(*fullMap) / sizeof(**fullMap); x++)
      if (IS(A, fullMap[y][x]))
        printf(" a ");
      else if (IS(HOUSE, fullMap[y][x]))
        printf(" %c ", HOUSE_CHAR);
      else if (IS(PIECE, fullMap[y][x]))
        printf(" %d ", fullMap[y][x] - PIECE);
      else if (fullMap[y][x])
        printf(" %c ", fullMap[y][x]);
      else
        printf(" - ");
    printf("\n");
  }
}
