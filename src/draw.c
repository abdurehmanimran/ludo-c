#include "draw.h"
#include "ludo.h"

#include <stdio.h>

static char fullMap[15][15];

static u8 houseCords[4][2] = {{0, 0}, {9, 0}, {0, 9}, {9, 9}};

#define HOUSE_CHAR '#'

void drawHouse(u8 x, u8 y) {
  for (u32 i = y, j = x; j < x + 6; j++)
    fullMap[i][j] = HOUSE_CHAR;

  for (u32 i = y + 5, j = x; j < x + 6; j++)
    fullMap[i][j] = HOUSE_CHAR;

  for (u32 i = y + 1, j = x; i < y + 6; i++)
    fullMap[i][j] = HOUSE_CHAR;

  for (u32 i = y + 1, j = x + 5; i < y + 6; i++)
    fullMap[i][j] = HOUSE_CHAR;
}

void initMap() {
  for (u8 i = 0; i < sizeof(houseCords) / sizeof(*houseCords); i++)
    drawHouse(houseCords[i][0], houseCords[i][1]);
}

void setHousePieces(const Game *game) {
  for (u8 n = 0; n < sizeof(houseCords) / sizeof(*houseCords); n++) {
    for (u8 i = 0; i < 4; i++)
      if (game->players[n].locations[i] == LOCKED) {
        fullMap[houseCords[n][1] + 2 + i / 2][houseCords[n][0] + 2 + i % 2] =
        48 + i;
      }
  }
}

void drawMap(const Game *game) { setHousePieces(game); };

void displayGame() {
  for (u32 y = 0; y < sizeof(fullMap) / sizeof(*fullMap); y++) {
    for (u32 x = 0; x < sizeof(*fullMap) / sizeof(**fullMap); x++)
      if (fullMap[y][x])
        printf(" %c ", fullMap[y][x]);
      else
        printf(" - ");
    printf("\n");
  }
}
