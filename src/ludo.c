#include "ludo.h"

#include <stdlib.h>
#include <time.h>

void init_game(Game *game) {
  game->current_player = 0;

  for (int i = 0; i < sizeof(game->players) / sizeof(*game->players); i++) {
    game->players[i].kills = 0;

    for (int l = 0; l < sizeof(game->players[i].locations) /
                            sizeof(*game->players[i].locations);
         l++)
      game->players[i].locations[l] = LOCKED;
  }
};

u32 rolldice() { return (rand() % 6) + 1; }

int main() {
  srand(time(NULL));

  Game main_game;
  init_game(&main_game);

  return 0;
}
