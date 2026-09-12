#include "piece.h"
#include "draw.h"
#include "ludo.h"

#include <stdio.h>
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

u32 getPlayerBits(u8 player) {
  u32 p = A;
  switch (player) {
  case 1:
    p = B;
    break;
  case 2:
    p = C;
    break;
  case 3:
    p = D;
    break;
  }

  return p;
}

// @params playerBits Who is going to eliminate others?
void eliminateOthers(u32 playerBits, u8 location, Game *game) {
  u8 player; // Who is there to be eliminated?

  switch (game->map[location]) {
  case A:
    if (IS(A, playerBits))
      return;
    player = 0;
    break;
  case B:
    if (IS(B, playerBits))
      return;
    player = 1;
    break;
  case C:
    if (IS(C, playerBits))
      return;
    player = 2;
    break;
  case D:
    if (IS(D, playerBits))
      return;
    player = 3;
    break;
  default:
    return;
    break;
  }

  // 1 -> Lock the pieces
  for (u8 i = 0; i < 4; i++) {
    if (game->players[player].locations[i] == location)
      game->players[player].locations[i] = LOCKED;
  }

  // 2 -> Remove from the map
  game->map[location] = 0;
}

void moveAhead(u8 player, u8 piece, u8 steps, Game *game) {
  u8 oldLoc = game->players[player].locations[piece];
  u8 newLoc = (oldLoc + steps) % 52;

  u32 p = getPlayerBits(player);

  // Remove that player from game's map if it is the sole one
  u8 sole = 1;

  for (u8 i = 0; i < 4; i++)
    if (i != piece && game->players[player].locations[i] ==
                      game->players[player].locations[piece]) {
      sole = 0;
      break;
    }

  if (sole)
    PICK(p, game->map[oldLoc]);

  // Change the location for that piece
  game->players[player].locations[piece] = newLoc;
  game->players[player].covered[piece] += steps;

  // When the piece has left the outer map
  if (game->players[player].covered[piece] > 50)
    return;

  // Placing the moved piece at new location
  if (!IS_PROTECTED(newLoc)) {
    eliminateOthers(p, newLoc, game);
  }

  PLACE(p, game->map[newLoc]);
}

void playTurn(u8 player, Game *game) {
  u8 unlockedCount     = 0;
  i8 unlockedPieces[4] = {-1, -1, -1, -1};

  for (u8 i = 0; i < 4; i++) {
    if (game->players[player].locations[i] != LOCKED)
      unlockedPieces[unlockedCount++] = i;
  }

  while (1) {
    u32 num = rolldice();
    printf("Player :: %u\tDice :: %u\n", player, num);

    if (num != 6 && unlockedCount == 0)
      break;

    if (num == 6 && unlockedCount < 4) {
      char ques = 'n';
      printf("Do you want to unlock any piece? [y/n] ");
      scanf(" %c", &ques);

      if (ques == 'y') {
        for (u8 i = 0; i < 4; i++) {
          if (game->players[player].locations[i] == LOCKED)
            printf(":: %u\t", i);
        }
        while (1) {
          u32 lockPiece;
          printf("\n-> ");
          scanf("%u", &lockPiece);

          if (game->players[player].locations[lockPiece] == LOCKED) {
            unlockPiece(player, lockPiece, game);
            unlockedPieces[unlockedCount++] = lockPiece;
            printf("added : %d\n", unlockedCount);
            break;
          }
        }
        drawMap(game);
        continue;
      }
    }

    if (unlockedCount == 1) {
      moveAhead(player, unlockedPieces[unlockedCount - 1], num, game);
    } else {
      printf("Which piece do you want to move?\n");
      for (u8 i = 0; i < unlockedCount; i++) {
        printf(":: %u\t", unlockedPieces[i]);
      }
      while (1) {
        u32 movePiece;
        u32 done = 0;
        printf("\n-> ");
        scanf(" %u", &movePiece);

        for (u8 i = 0; i < unlockedCount; i++) {
          if (unlockedPieces[i] == (i8)movePiece) {
            moveAhead(player, movePiece, num, game);
            done = 1;
            break;
          }
        }

        if (done)
          break;
      }
    }

    if (num != 6)
      return;

  nextTurn:
    drawMap(game);
    continue;
  }
}
