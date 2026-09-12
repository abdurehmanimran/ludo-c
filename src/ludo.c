#include "ludo.h"
#include "draw.h"
#include "piece.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void init_game(Game *game) {
  game->current_player = 0;
  memset(game->map, 0, sizeof(game->map));

  for (u32 i = 0; i < sizeof(game->players) / sizeof(*game->players); i++) {
    game->players[i].kills = 0;

    for (u32 l = 0; l < sizeof(game->players[i].locations) /
                        sizeof(*game->players[i].locations);
         l++)
      game->players[i].locations[l] = LOCKED;
  }
};

int main() {
  srand(time(NULL));

  Game main_game;
  init_game(&main_game);

  unlockPiece(1, 0, &main_game);
  unlockPiece(2, 2, &main_game);
  unlockPiece(3, 3, &main_game);

  initMap();

  while (1) {
    drawMap(&main_game);

    sleep(2);
    printf("\n");
    unlockPiece(0, 0, &main_game);
  }

  return 0;
}
