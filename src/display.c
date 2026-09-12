#include "display.h"
#include "ludo.h"

#include <stdio.h>

void displayGame(const u32 fullMap[15][15]) {
  for (u32 y = 0; y < 15; y++) {
    for (u32 x = 0; x < 15; x++)
      if (IS(A, fullMap[y][x]))
        printf(" a ");
      else if (IS(B, fullMap[y][x]))
        printf(" b ");
      else if (IS(C, fullMap[y][x]))
        printf(" c ");
      else if (IS(D, fullMap[y][x]))
        printf(" d ");
      else if (IS(HOUSE, fullMap[y][x]))
        printf(" %c ", HOUSE_CHAR);
      else if (IS(MIDDLE_LINE, fullMap[y][x]))
        printf(" %c ", MIDDLE_LINE_CHAR);
      else if (IS(PIECE, fullMap[y][x]))
        printf(" %d ", fullMap[y][x] - PIECE);
      else
        printf(" - ");
    printf("\n");
  }
}
