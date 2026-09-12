#include "draw.h"
#include "display.h"
#include "ludo.h"

static u32 fullMap[15][15];

static u8 houseCords[4][2] = {{0, 0}, {9, 0}, {0, 9}, {9, 9}};

void drawHouse(u8 x, u8 y) {
  for (u8 i = y, j = x; j < x + 6; j++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u8 i = y + 5, j = x; j < x + 6; j++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u8 i = y + 1, j = x; i < y + 6; i++)
    PLACE(HOUSE, fullMap[i][j]);

  for (u8 i = y + 1, j = x + 5; i < y + 6; i++)
    PLACE(HOUSE, fullMap[i][j]);
}

void drawCenter() {
  PLACE(HOUSE, fullMap[6][6]);
  PLACE(HOUSE, fullMap[6][8]);
  PLACE(HOUSE, fullMap[8][6]);
  PLACE(HOUSE, fullMap[8][8]);

  PLACE(HOUSE, fullMap[7][7]);
}

void drawMiddleLines() {
  for (u8 i = 1; i < 6; i++)
    PLACE(MIDDLE_LINE, fullMap[7][i]);

  for (u8 i = 9; i < 14; i++)
    PLACE(MIDDLE_LINE, fullMap[7][i]);

  for (u8 i = 1; i < 6; i++)
    PLACE(MIDDLE_LINE, fullMap[i][7]);

  for (u8 i = 9; i < 14; i++)
    PLACE(MIDDLE_LINE, fullMap[i][7]);
}

void initMap() {
  for (u8 i = 0; i < sizeof(houseCords) / sizeof(*houseCords); i++)
    drawHouse(houseCords[i][0], houseCords[i][1]);

  drawCenter();
  drawMiddleLines();
}

void setHousePieces(const Game *game) {
  for (u8 n = 0; n < sizeof(houseCords) / sizeof(*houseCords); n++) {
    for (u8 i = 0; i < 4; i++)
      if (game->players[n].locations[i] == LOCKED)
        fullMap[houseCords[n][1] + 2 + i / 2][houseCords[n][0] + 2 + i % 2] =
        i + PIECE;
      else // Remove the piece from house when it is unlocked
        PICK(
        PIECE,
        fullMap[houseCords[n][1] + 2 + i / 2][houseCords[n][0] + 2 + i % 2]);
  }
}

// Maps the linear game map arr to the fullMap
void placeMapPieces(const Game *game) {
  u32 mapIter = 0;

  for (u8 x = 0; x < 6; x++)
    fullMap[6][x] = game->map[mapIter++];

  for (i8 y = 5; y >= 0; y--)
    fullMap[y][6] = game->map[mapIter++];

  fullMap[0][7] = game->map[mapIter++];

  for (u8 y = 0; y < 6; y++)
    fullMap[y][8] = game->map[mapIter++];

  for (u8 x = 9; x < 15; x++)
    fullMap[6][x] = game->map[mapIter++];

  fullMap[7][14] = game->map[mapIter++];

  for (u8 x = 14; x >= 9; x--)
    fullMap[8][x] = game->map[mapIter++];

  for (u8 y = 9; y < 15; y++)
    fullMap[y][8] = game->map[mapIter++];

  fullMap[14][14] = game->map[mapIter++];

  for (u8 y = 14; y >= 9; y--)
    fullMap[y][6] = game->map[mapIter++];

  for (u8 x = 0; x < 6; x++)
    fullMap[8][x] = game->map[mapIter++];

  fullMap[0][0] = game->map[mapIter++];
}

void drawMap(const Game *game) {
  setHousePieces(game);
  placeMapPieces(game);

  // Also display to the screen
  displayGame(fullMap);
};
