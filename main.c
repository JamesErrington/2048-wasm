#include "./main.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "lib/stb_sprintf.h"

#define NUM_ROW_SQUARES 4
#define NUM_GRID_SQUARES NUM_ROW_SQUARES * NUM_ROW_SQUARES

#define GRID_OFFSET_X 10
#define GRID_OFFSET_Y 10
#define GRID_SIZE 470
#define GRID_PADDING 15
#define GRID_COLOR RGB(187, 173, 160)

#define BOX_SIZE (GRID_SIZE - (5 * GRID_PADDING)) / NUM_ROW_SQUARES
#define BOX_COLOR RGBA(238, 228, 218, 0.35 * 255)
#define BOX_FONT_SIZE 55

static char log_buffer[4096] = {0};
#define LOGF(...) \
	do { \
	    stbsp_snprintf(log_buffer, sizeof(log_buffer), __VA_ARGS__); \
	    platform_log(log_buffer); \
	} while(0)

static Game game = {0};

static void fill_rect(Rect rect, u32 color) {
	platform_fill_rect(rect.x, rect.y, rect.w, rect.h, color);
}

static void draw_boxes() {
	for (int i = 0; i < NUM_GRID_SQUARES; i++) {
		u32 square = game.grid[i];
		if (square == 0) continue;

		int x = i / NUM_ROW_SQUARES, y = i % NUM_ROW_SQUARES;
		Rect box = {
			.x = GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE),
			.y = GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE),
			.w = BOX_SIZE,
			.h = BOX_SIZE,
		};
		fill_rect(box, square_color(square));
		platform_fill_text(
			GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE) + (BOX_SIZE / 2),
			GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE) + (BOX_SIZE / 2),
			square_text(square),
			BOX_FONT_SIZE,
			TWO_TEXT_COLOR
		);
	}
}

void init() {
	Rect rect = {.x = GRID_OFFSET_X, .y = GRID_OFFSET_Y, .w = GRID_SIZE, .h = GRID_SIZE };
	fill_rect(rect, GRID_COLOR);

	for (int y = 0; y < NUM_ROW_SQUARES; y++) {
		for (int x = 0; x < NUM_ROW_SQUARES; x++) {
			Rect box = {
				.x = GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE),
				.y = GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE),
				.w = BOX_SIZE,
				.h = BOX_SIZE,
			};
			fill_rect(box, BOX_COLOR);
		}
	}

	int inited = 0;
	while (inited < 2) {
		u32 i = rand() % NUM_GRID_SQUARES;
		if (game.grid[i] == 0) {
			game.grid[i] = init_square_value();
			inited++;
		}
	}

	draw_boxes();
}

void handle_key(int key) {
	switch (key) {
		case ARROW_DOWN:
			for (int i = NUM_GRID_SQUARES - NUM_ROW_SQUARES - 1; i >= 0; i--) {
				// @TODO implement
			}

			draw_boxes();

			break;
	}
}
