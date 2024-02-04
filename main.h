#ifndef JAMESE_WASM_TEST_H
#define JAMESE_WASM_TEST_H

#include <stdint.h>

typedef uint8_t  u8;
typedef int32_t  i32;
typedef uint32_t u32;

typedef struct Rect {
	float x, y, w, h;
} Rect;

void platform_fill_rect(i32 x, i32 y, i32 w, i32 h, u32 c);

void init();

static inline u32 RGBA(u8 r, u8 g, u8 b, u8 a) {
	return (a<<3*8) | (b<<2*8) | (g<<1*8) | (r<<0*8);
}

#endif
