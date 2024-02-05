#ifndef JAMESE_2048_UTIL_H
#define JAMESE_2048_UTIL_H

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

static u32 lcg_parkmiller(u32 *state) {
    return *state = (u64)*state * 48271 % 0x7fffffff;
}

static u32 state = 50022;

static void srand(u32 seed) {
	state = seed;
}

static u32 rand() {
	return lcg_parkmiller(&state);
}

#endif
