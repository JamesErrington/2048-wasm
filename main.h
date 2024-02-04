#ifndef JAMESE_WASM_TEST_H
#define JAMESE_WASM_TEST_H

#include <stdint.h>

typedef uint8_t  u8;
typedef int32_t  i32;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct Rect {
	float x, y, w, h;
} Rect;

void platform_fill_rect(i32 x, i32 y, i32 w, i32 h, u32 c);
void platform_fill_text(i32 x, i32 y, const char *text, u32 size, u32 color);
void platform_log(const char *message);

void init();
void handle_key(int key);

static inline u32 RGBA(u8 r, u8 g, u8 b, u8 a) {
	return (a<<3*8) | (b<<2*8) | (g<<1*8) | (r<<0*8);
}

static inline u32 RGB(u8 r, u8 g, u8 b) {
	return RGBA(r, g, b, 0xFF);
}

#define RAND_A 6364136223846793005ULL
#define RAND_C 1442695040888963407ULL

static u32 rand() {
	static u64 state = 0;
	state = state * RAND_A + RAND_C;
	return (state >> 32) & 0xFFFFFFFF;
}

static inline u32 init_square_value() {
	return 2 << (rand() % 2);
}

#define TWO_COLOR RGB(238, 228, 218)
#define TWO_TEXT_COLOR RGB(119, 110, 101)
#define FOUR_COLOR RGB(238, 225, 201)
#define FOUR_TEXT_COLOR RGB(119, 110, 101)

static inline u32 square_color(u32 value) {
	switch (value) {
		case 2:
			return TWO_COLOR;
		case 4:
			return FOUR_COLOR;
		default:
			return RGB(0xFF, 0, 0);
	}
}

static inline const char *square_text(u32 value) {
	switch (value) {
		case 2:
			return "2";
		case 4:
			return "4";
		default:
			return "?";
	}
}

#define ARROW_LEFT 37
#define ARROW_UP 38
#define ARROW_RIGHT 39
#define ARROW_DOWN 40

typedef struct Game {
	u32 score;
	u32 grid[16];
} Game;

#endif
