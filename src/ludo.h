#ifndef LUDO_C_H
#define LUDO_C_H

#include <stdint.h>

// Some Helping Macros
#define LOCKED       -1
#define IS_INSIDE(x) x > 50
#define FINISHED(x)  x >= 56

#define FIRST_SPAWN  0
#define SECOND_SPAWN 13
#define THIRD_SPAWN  26
#define FOURTH_SPAWN 39

#define FIRST_STAR  8
#define SECOND_STAR 21
#define THIRD_STAR  31
#define FOURTH_STAR 44

#define IS_PROTECTED(x)                                                        \
  x == FIRST_SPAWN || x == SECOND_SPAWN || x == THIRD_SPAWN ||                 \
      x == FOURTH_SPAWN || x == FIRST_STAR || x == SECOND_STAR ||              \
      x == THIRD_STAR || x == FOURTH_STAR

typedef uint8_t u8;

typedef uint32_t u32;
typedef uint64_t u64;

typedef int32_t i32;
typedef int64_t i64;

typedef struct {
  u32 kills;
  i32 locations[4];
} Player; // 20 Bytes

typedef struct {
  u8     current_player;
  i32    map[52];
  Player players[4];
} Game;

#endif
