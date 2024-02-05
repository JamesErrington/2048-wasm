#include "./main.h"

#define NUM_ROW_SQUARES 4
#define NUM_GRID_SQUARES (NUM_ROW_SQUARES * NUM_ROW_SQUARES)

#define GRID_OFFSET_X 10
#define GRID_OFFSET_Y 10
#define GRID_SIZE 470
#define GRID_PADDING 15
#define GRID_COLOR RGB(187, 173, 160)

#define BOX_SIZE ((GRID_SIZE - (5 * GRID_PADDING)) / NUM_ROW_SQUARES)
#define BOX_COLOR RGBA(238, 228, 218, 0.35 * 255)
#define BOX_FONT_SIZE 55

static Game game = {0};

static void fill_rect(Rect rect, u32 color) {
	platform_fill_rect(rect.x, rect.y, rect.w, rect.h, color);
}

static void draw_grid() {
	Rect rect = {.x = GRID_OFFSET_X, .y = GRID_OFFSET_Y, .w = GRID_SIZE, .h = GRID_SIZE };
	fill_rect(rect, GRID_COLOR);

	for (int i = 0; i < NUM_GRID_SQUARES; i++) {
		int x = i % NUM_ROW_SQUARES, y = i / NUM_ROW_SQUARES;
		Rect box = {
			.x = GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE),
			.y = GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE),
			.w = BOX_SIZE,
			.h = BOX_SIZE,
		};
		fill_rect(box, BOX_COLOR);

		u32 value = game.grid[i];
		if (value > 0) {
			Square square = square_info(value);
			fill_rect(box, square.bg_color);
			platform_fill_text(
				GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE) + (BOX_SIZE / 2),
				GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE) + (BOX_SIZE / 2),
				square.text,
				BOX_FONT_SIZE,
				square.text_color
			);
		}
	}
}

void init() {
	int inited = 0;
	while (inited < 2) {
		u32 i = rand() % 16;
		if (game.grid[i] == 0) {
			game.grid[i] = init_square_value();
			inited++;
		}
	}

	draw_grid();
}

void handle_key(int key) {
	int moved = FALSE;

	switch (key) {
		case ARROW_DOWN: {
			for (int i = NUM_GRID_SQUARES - NUM_ROW_SQUARES - 1; i >= 0; i--) {
				if (game.grid[i] == 0) continue;

				int j = i + NUM_ROW_SQUARES;
				for (; (j < NUM_GRID_SQUARES - NUM_ROW_SQUARES) && game.grid[j] == 0; j += NUM_ROW_SQUARES) {}

				if (game.grid[j] == 0) {
					moved = TRUE;
					game.grid[j] = game.grid[i];
					game.grid[i] = 0;

					continue;
				} else if (game.grid[j] == game.grid[i]) {
					moved = TRUE;
					game.grid[j] = game.grid[i] * 2;
					game.grid[i] = 0;

					continue;
				}

				j -= NUM_ROW_SQUARES;
				if (j > 0 && j != i) {
					moved = TRUE;
					game.grid[j] = game.grid[i];
					game.grid[i] = 0;
				}
			}
		} break;
		case ARROW_RIGHT: {
			int order[NUM_GRID_SQUARES] = {3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12};
			for (int n = 0; n < NUM_GRID_SQUARES; n++) {
				int i = order[n];

				if (game.grid[i] == 0 || (i % NUM_ROW_SQUARES == 3)) continue;

				int j = i + 1;
				int x = j % NUM_ROW_SQUARES, y = j / NUM_ROW_SQUARES;
				for (; x < NUM_ROW_SQUARES && game.grid[j] == 0; x++) {
					j = y * NUM_ROW_SQUARES + x;
				}

				if (game.grid[j] == 0) {
					moved = TRUE;
					game.grid[j] = game.grid[i];
					game.grid[i] = 0;

					continue;
				} else if (game.grid[j] == game.grid[i]) {
					moved = TRUE;
					game.grid[j] = game.grid[i] * 2;
					game.grid[i] = 0;

					continue;
				}

				j -= 1;
				if ((j % NUM_ROW_SQUARES != 0) && i != j) {
					moved = TRUE;
					game.grid[j] = game.grid[i];
					game.grid[i] = 0;
				}
			}
		} break;
	}

	if (moved) {
		int inited = 0;
		while (inited < 1) {
			u32 i = rand() % NUM_GRID_SQUARES;
			if (game.grid[i] == 0) {
				game.grid[i] = init_square_value();
				inited++;
			}
		}
	}

	draw_grid();
}
