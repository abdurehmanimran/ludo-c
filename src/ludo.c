#include "ludo.h"
#include "draw.h"
#include "piece.h"

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
  initMap();

  u8 currPlayer = 0;

  while (1) {
    drawMap(&main_game);
    playTurn(currPlayer, &main_game);

    currPlayer++;
    currPlayer %= 4;
  }

  return 0;
}
