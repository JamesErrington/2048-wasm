#ifndef JAMESE_2048_GAME_H
#define JAMESE_2048_GAME_H

#include "util.h"

void platform_fill_rect(i32 x, i32 y, i32 w, i32 h, u32 c);
void platform_fill_text(i32 x, i32 y, const char *text, u32 size, u32 color);
void platform_log(const char *message);

void init(int seed);
int handle_key(int key);
void render();

static inline u32 RGBA(u8 r, u8 g, u8 b, u8 a) {
	return (a<<3*8) | (b<<2*8) | (g<<1*8) | (r<<0*8);
}

static inline u32 RGB(u8 r, u8 g, u8 b) {
	return RGBA(r, g, b, 0xFF);
}

static inline u32 init_tile_value() {
	return 2 << (rand() % 2);
}

#define ARROW_LEFT 37
#define ARROW_UP 38
#define ARROW_RIGHT 39
#define ARROW_DOWN 40

#define WINNING_VALUE 2048
#define NUM_ROW_SQUARES 4
#define NUM_GRID_SQUARES (NUM_ROW_SQUARES * NUM_ROW_SQUARES)

#define GRID_OFFSET_X 0
#define GRID_OFFSET_Y 0
#define GRID_SIZE 470
#define GRID_PADDING 15
#define GRID_COLOR RGB(187, 173, 160)

#define BOX_SIZE ((GRID_SIZE - (5 * GRID_PADDING)) / NUM_ROW_SQUARES)
#define BOX_COLOR RGBA(238, 228, 218, 0.35 * 255)

#define VALUE_COLOR_2 RGB(0xee, 0xe4, 0xda)
#define VALUE_COLOR_4 RGB(0xee, 0xe1, 0xc9)
#define VALUE_COLOR_8 RGB(0xf3, 0xb2, 0x7a)
#define VALUE_COLOR_16 RGB(0xf6, 0x96, 0x64)
#define VALUE_COLOR_32 RGB(0xf7, 0x7c, 0x5f)
#define VALUE_COLOR_64 RGB(0xf7, 0x5f, 0x3b)
#define VALUE_COLOR_128 RGB(0xed, 0xd0, 0x73)
#define VALUE_COLOR_256 RGB(0xed, 0xcc, 0x62)
#define VALUE_COLOR_512 RGB(0xed, 0xc9, 0x50)
#define VALUE_COLOR_1024 RGB(0xed, 0xc5, 0x3f)
#define VALUE_COLOR_2048 RGB(0xed, 0xc2, 0x2e)

#define TEXT_COLOR_1 RGB(119, 110, 101)
#define TEXT_COLOR_2 RGB(0xf9, 0xf6, 0xf2)

#define TEXT_SIZE_1 55
#define TEXT_SIZE_2 45
#define TEXT_SIZE_3 35

typedef struct GridState {
	u32 x[NUM_GRID_SQUARES];
	u32 y[NUM_GRID_SQUARES];
	u32 width[NUM_GRID_SQUARES];
	u32 height[NUM_GRID_SQUARES];
	u32 value[NUM_GRID_SQUARES];
	u32 bg_color[NUM_GRID_SQUARES];
	u32 text_color[NUM_GRID_SQUARES];
	u32 text_size[NUM_GRID_SQUARES];
	const char *text[NUM_GRID_SQUARES];
} GridState;

typedef struct Game {
	GridState state;
} Game;

static inline int itox(int i) {
	return i % NUM_ROW_SQUARES;
}

static inline int itoy(int i) {
	return i / NUM_ROW_SQUARES;
}

static inline int xytoi(int x, int y) {
	return y * NUM_ROW_SQUARES + x;
}

static void set_tile_value(Game *game, int i, u32 value);

static void spawn_tiles(Game *game, int num);

#endif
