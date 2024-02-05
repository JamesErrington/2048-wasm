#ifndef JAMESE_WASM_TEST_H
#define JAMESE_WASM_TEST_H

#include <stdint.h>

#define STB_SPRINTF_IMPLEMENTATION
#include "lib/stb_sprintf.h"

typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t  i32;

#define TRUE  1
#define FALSE 0

static char log_buffer[4096] = {0};
#define LOGF(...) \
	do { \
	    stbsp_snprintf(log_buffer, sizeof(log_buffer), __VA_ARGS__); \
	    platform_log(log_buffer); \
	} while(0)

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

static u32 lcg_parkmiller(u32 *state) {
    return *state = (u64)*state * 48271 % 0x7fffffff;
}

static u32 rand() {
	static u32 state = 50022;
	return lcg_parkmiller(&state);
}

static inline u32 init_square_value() {
	return 2 << (rand() % 2);
}

#define ARROW_LEFT 37
#define ARROW_UP 38
#define ARROW_RIGHT 39
#define ARROW_DOWN 40

typedef struct Game {
	u32 score;
	u32 grid[16];
} Game;

typedef struct Square {
	u32 bg_color;
	u32 text_color;
	u32 text_size;
	const char *text;
} Square;

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

static Square square_info(u32 value) {
	Square square;
	switch (value) {
		case 2: {
			square.bg_color = VALUE_COLOR_2;
			square.text_color = TEXT_COLOR_1;
			square.text_size = TEXT_SIZE_1;
			square.text = "2";
		} break;
		case 4: {
			square.bg_color = VALUE_COLOR_4;
			square.text_color = TEXT_COLOR_1;
			square.text_size = TEXT_SIZE_1;
			square.text = "4";
		} break;
		case 8: {
			square.bg_color = VALUE_COLOR_8;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_1;
			square.text = "8";
		} break;
		case 16: {
			square.bg_color = VALUE_COLOR_16;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_1;
			square.text = "16";
		} break;
		case 32: {
			square.bg_color = VALUE_COLOR_32;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_1;
			square.text = "32";
		} break;
		case 64: {
			square.bg_color = VALUE_COLOR_64;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_1;
			square.text = "64";
		} break;
		case 128: {
			square.bg_color = VALUE_COLOR_128;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_2;
			square.text = "128";
		} break;
		case 256: {
			square.bg_color = VALUE_COLOR_256;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_2;
			square.text = "256";
		} break;
		case 512: {
			square.bg_color = VALUE_COLOR_512;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_2;
			square.text = "512";
		} break;
		case 1024: {
			square.bg_color = VALUE_COLOR_1024;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_3;
			square.text = "1024";
		} break;
		case 2048: {
			square.bg_color = VALUE_COLOR_2048;
			square.text_color = TEXT_COLOR_2;
			square.text_size = TEXT_SIZE_3;
			square.text = "2048";
		} break;
		default: {
			LOGF("PANIC! Invalid square value %d", value);
		} break;
	}

	return square;
}



#endif
