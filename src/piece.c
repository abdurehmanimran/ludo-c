#include "piece.h"

#include <stdlib.h>

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
