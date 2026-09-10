#ifndef LUDO_C_H
#define LUDO_C_H

#include <stdint.h>

// Some Helping Macros
#define LOCKED       -1
#define IS_INSIDE(x) x > 50
#define FINISHED(x)  x >= 56

#define SPAWN_A 0
#define SPAWN_B 13
#define SPAWN_C 26
#define SPAWN_D 39

#define STAR_A 8
#define STAR_B 21
#define STAR_C 31
#define STAR_D 44

#define IS_PROTECTED(x)                                                        \
  x == SPAWN_A || x == SPAWN_B || x == SPAWN_C || x == SPAWN_D ||              \
  x == STAR_A || x == STAR_B || x == STAR_C || x == STAR_D

#define A 1
#define B 1 << 1
#define C 1 << 2
#define D 1 << 3

#define PLACE_A(x) x |= A
#define PLACE_B(x) x |= B
#define PLACE_C(x) x |= C
#define PLACE_D(x) x |= D

#define IS_A(x) x &A
#define IS_B(x) x &B
#define IS_C(x) x &C
#define IS_D(x) x &D

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
  u8     map[52];
  Player players[4];
} Game; // 136 Bytes

#endif
