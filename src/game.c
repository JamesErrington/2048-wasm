#include "game.h"

static Game game = {0};

void init(int seed) {
	srand(seed);

	for (int i = 0; i < NUM_GRID_SQUARES; i++) {
		int x = itox(i), y = itoy(i);

		game.state.x[i] = GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE);
		game.state.y[i] = GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE);
		game.state.width[i] = BOX_SIZE;
		game.state.height[i] = BOX_SIZE;

		game.state.value[i] = 0;
		game.state.bg_color[i] = BOX_COLOR;
		game.state.text_color[i] = TEXT_COLOR_1;
		game.state.text_size[i] = TEXT_SIZE_1;
		game.state.text[i] = "";
	}

	spawn_tiles(&game, 2);
	render();
}

void render() {
	platform_fill_rect(GRID_OFFSET_X, GRID_OFFSET_Y, GRID_SIZE, GRID_SIZE, GRID_COLOR);

	for (int i = 0; i < NUM_GRID_SQUARES; i++) {
		platform_fill_rect(game.state.x[i], game.state.y[i], game.state.width[i], game.state.height[i], game.state.bg_color[i]);

		if (game.state.value[i] > 0) {
			int x = itox(i), y = itoy(i);
			int x_offset = GRID_OFFSET_X + ((x + 1) * GRID_PADDING) + (x * BOX_SIZE) + (BOX_SIZE / 2);
			int y_offset = GRID_OFFSET_Y + ((y + 1) * GRID_PADDING) + (y * BOX_SIZE) + (BOX_SIZE / 2);
			platform_fill_text(x_offset, y_offset, game.state.text[i], game.state.text_size[i], game.state.text_color[i]);
		}
	}
}

int handle_key(int key) {
	int moved = FALSE;

	switch (key) {
		case ARROW_LEFT: {
			int order[NUM_GRID_SQUARES - NUM_ROW_SQUARES] = {13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3};
			for (int n = 0; n < NUM_GRID_SQUARES - NUM_ROW_SQUARES; n++) {
				int i = order[n];

				if (game.state.value[i] == 0) continue;

				int j = i - 1;
				int x = itox(j), y = itoy(j);
				while (x > 0 && game.state.value[j] == 0) {
					x--;
					j = xytoi(x, y);
				}

				if (game.state.value[j] == 0) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
					continue;
				} else if (game.state.value[j] == game.state.value[i]) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i] * 2);
					set_tile_value(&game, i, 0);
					continue;
				}

				j++;
				if ((j % NUM_ROW_SQUARES != 3) && i != j) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
				}
			}
		} break;
		case ARROW_UP: {
			int order[NUM_GRID_SQUARES - NUM_ROW_SQUARES] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
			for (int n = 0; n < NUM_GRID_SQUARES - NUM_ROW_SQUARES; n++) {
				int i = order[n];

				if (game.state.value[i] == 0) continue;

				int j = i - NUM_ROW_SQUARES;
				int x = itox(j), y = itoy(j);
				while (y > 0 && game.state.value[j] == 0) {
					y--;
					j = xytoi(x, y);
				}

				if (game.state.value[j] == 0) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
					continue;
				} else if (game.state.value[j] == game.state.value[i]) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i] * 2);
					set_tile_value(&game, i, 0);
					continue;
				}

				j += NUM_ROW_SQUARES;
				if (j < NUM_GRID_SQUARES - 1 && j != i) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
				}
			}
		} break;
		case ARROW_RIGHT: {
			int order[NUM_GRID_SQUARES - NUM_ROW_SQUARES] = {2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12};
			for (int n = 0; n < NUM_GRID_SQUARES - NUM_ROW_SQUARES; n++) {
				int i = order[n];

				if (game.state.value[i] == 0) continue;

				int j = i + 1;
				int x = itox(j), y = itoy(j);
				while (x < NUM_ROW_SQUARES - 1 && game.state.value[j] == 0) {
					x++;
					j = xytoi(x, y);
				}

				if (game.state.value[j] == 0) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
					continue;
				} else if (game.state.value[j] == game.state.value[i]) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i] * 2);
					set_tile_value(&game, i, 0);
					continue;
				}

				j--;
				if ((j % NUM_ROW_SQUARES != 0) && i != j) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
				}
			}
		} break;
		case ARROW_DOWN: {
			int order[NUM_GRID_SQUARES - NUM_ROW_SQUARES] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
			for (int n = 0; n < NUM_GRID_SQUARES - NUM_ROW_SQUARES; n++) {
				int i = order[n];

				if (game.state.value[i] == 0) continue;

				int j = i + NUM_ROW_SQUARES;
				int x = itox(j), y = itoy(j);
				while (y < NUM_ROW_SQUARES - 1 && game.state.value[j] == 0) {
					y++;
					j = xytoi(x, y);
				}

				if (game.state.value[j] == 0) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
					continue;
				} else if (game.state.value[j] == game.state.value[i]) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i] * 2);
					set_tile_value(&game, i, 0);
					continue;
				}

				j -= NUM_ROW_SQUARES;
				if (j > 0 && j != i) {
					moved = TRUE;
					set_tile_value(&game, j, game.state.value[i]);
					set_tile_value(&game, i, 0);
				}
			}
		} break;
	}

	if (moved) {
		spawn_tiles(&game, 1);
		render();
	}

	for (int i = 0; i < NUM_GRID_SQUARES; i++) {
		if (game.state.value[i] == WINNING_VALUE) {
			return 1;
		}
	}

	return 0;
}

static void set_tile_value(Game *game, int i, u32 value) {
	game->state.value[i] = value;

	switch (value) {
		case 0: {
			game->state.bg_color[i] = BOX_COLOR;
			game->state.text_color[i] = TEXT_COLOR_1;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "";
		} break;
		case 2: {
			game->state.bg_color[i] = VALUE_COLOR_2;
			game->state.text_color[i] = TEXT_COLOR_1;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "2";
		} break;
	 	case 4: {
			game->state.bg_color[i] = VALUE_COLOR_4;
			game->state.text_color[i] = TEXT_COLOR_1;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "4";
		} break;
		case 8: {
			game->state.bg_color[i] = VALUE_COLOR_8;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "8";
		} break;
		case 16: {
			game->state.bg_color[i] = VALUE_COLOR_16;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "16";
		} break;
		case 32: {
			game->state.bg_color[i] = VALUE_COLOR_32;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "32";
		} break;
		case 64: {
			game->state.bg_color[i] = VALUE_COLOR_64;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_1;
			game->state.text[i] = "64";
		} break;
		case 128: {
			game->state.bg_color[i] = VALUE_COLOR_128;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_2;
			game->state.text[i] = "128";
		} break;
		case 256: {
			game->state.bg_color[i] = VALUE_COLOR_256;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_2;
			game->state.text[i] = "256";
		} break;
		case 512: {
			game->state.bg_color[i] = VALUE_COLOR_512;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_2;
			game->state.text[i] = "512";
		} break;
		case 1024: {
			game->state.bg_color[i] = VALUE_COLOR_1024;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_3;
			game->state.text[i] = "1024";
		} break;
		case 2048: {
			game->state.bg_color[i] = VALUE_COLOR_2048;
			game->state.text_color[i] = TEXT_COLOR_2;
			game->state.text_size[i] = TEXT_SIZE_3;
			game->state.text[i] = "2048";
		} break;
	}
}

static void spawn_tiles(Game *game, int num) {
	int spawned = 0;
	while (spawned < num) {
		u32 i = rand() % 16;
		if (game->state.value[i] == 0) {
			spawned++;

			set_tile_value(game, i, init_tile_value());
		}
	}
}
