#ifndef LUDO_C_H
#define LUDO_C_H

#include <stdint.h>

// Some Helping Macros
#define LOCKED       -1
#define IS_INSIDE(x) x > 50
#define FINISHED(x)  x >= 56

#define SPAWN_A 1
#define SPAWN_B 14
#define SPAWN_C 27
#define SPAWN_D 40

#define STAR_A 9
#define STAR_B 22
#define STAR_C 32
#define STAR_D 45

#define IS_PROTECTED(x)                                                        \
  x == SPAWN_A || x == SPAWN_B || x == SPAWN_C || x == SPAWN_D ||              \
  x == STAR_A || x == STAR_B || x == STAR_C || x == STAR_D

// Bit Fields/Flags for different things
#define PIECE (1 << 3)
#define HOUSE (1 << 4)

#define A (1 << 5)
#define B (1 << 6)
#define C (1 << 7)
#define D (1 << 8)

// Place x on y e.g A on x
#define PLACE(x, y) (y |= x)

// Is y x or x y?
#define IS(x, y) (x & y)

#define IS_EMPTY(x) !IS(x, A) && !IS(x, B) && !IS(x, C) && !IS(x, D)

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
