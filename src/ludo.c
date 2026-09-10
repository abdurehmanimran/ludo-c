#include "ludo.h"
#include "draw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void init_game(Game *game) {
  game->current_player = 0;
  memset(game->map, 0, sizeof(game->map));

  for (int i = 0; i < sizeof(game->players) / sizeof(*game->players); i++) {
    game->players[i].kills = 0;

    for (int l = 0; l < sizeof(game->players[i].locations) /
                        sizeof(*game->players[i].locations);
         l++)
      game->players[i].locations[l] = LOCKED;
  }
};

u32 rolldice() { return (rand() % 6) + 1; }

void placePiece(u8 player, u8 piece, u32 loc, Game *game) {
  game->players[player].locations[piece] = loc;

  switch (player) {
  case 0:
    PLACE(A, game->map[loc]);
    break;
  case 1:
    PLACE(B, game->map[loc]);
    break;
  case 2:
    PLACE(C, game->map[loc]);
    break;
  case 3:
    PLACE(D, game->map[loc]);
    break;
  }
}

void unlockPiece(u8 player, u8 piece, Game *game) {
  switch (player) {
  case 0:
    placePiece(player, piece, SPAWN_A, game);
    break;
  case 1:
    placePiece(player, piece, SPAWN_B, game);
    break;
  case 2:
    placePiece(player, piece, SPAWN_C, game);
    break;
  case 3:
    placePiece(player, piece, SPAWN_D, game);
    break;
  }
}

int main() {
  srand(time(NULL));

  Game main_game;
  init_game(&main_game);

  unlockPiece(0, 0, &main_game);
  unlockPiece(1, 0, &main_game);
  unlockPiece(2, 2, &main_game);
  unlockPiece(3, 3, &main_game);

  initMap();
  drawMap(&main_game);
  displayGame();

  return 0;
}
