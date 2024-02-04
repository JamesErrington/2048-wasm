#include "./main.h"

static void fill_rect(Rect rect, u32 color) {
	platform_fill_rect(rect.x, rect.y, rect.w, rect.h, color);
}

void init() {
	Rect rect = {.x = 10, .y = 10, .w = 100, .h = 100 };
	fill_rect(rect, RGBA(255, 0, 0, 255));
}
