#include "Clicks.h"

void left_button_down(Condition& cond, int x, int y) {
	if (y >= buttons_coord_y && y <= buttons_coord_y + button_height) {
		for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
			if (x >= buttons_coord_x[button_id] && x <= buttons_coord_x[button_id] + button_width) {
				cond.pressed_button = button_id;
				cond.button_is_pressed = true;
				cond.paint = PAINT_BUTTON;
				cond.Textures[button_id] = button_file_names[button_id][cond.theme_is_dark][cond.button_is_pressed];
				if (button_id == BUTTON_PLAY) {
					if (cond.status / 10 != 2) {
						cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_BACK][cond.theme_is_dark][cond.button_is_pressed];
					}
					else if (cond.status == 25) {
						cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_PAUSE][cond.theme_is_dark][cond.button_is_pressed];
					}
				}
				break;
			}
		}
	}
	if (x >= field_x && x <= field_x + field_width * 5 && y >= field_y && y <= field_y + field_height * 5) {
		field_click(cond, x, y);
	}
}

void left_button_up(Condition& cond, int x, int y) {
	if (cond.button_is_pressed) {
		cond.button_is_pressed = false;
		cond.Textures[cond.pressed_button] = button_file_names[cond.pressed_button][cond.theme_is_dark][cond.button_is_pressed];
		if (x >= buttons_coord_x[cond.pressed_button] && x <= buttons_coord_x[cond.pressed_button] + button_width
			&& y >= buttons_coord_y && y <= buttons_coord_y + button_height) {
			change_status_by_button_click(cond);
		}
		else {
			cond.paint = PAINT_BUTTON;
		}
	}
}

void change_status_by_button_click(Condition& cond) {
	if (cond.status / 10 - 2 == cond.pressed_button && cond.pressed_button != BUTTON_PLAY
		|| cond.status / 10 != 2 && cond.pressed_button == BUTTON_PLAY) {
		cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_PLAY][cond.theme_is_dark][cond.button_is_pressed];
		cond.status = 20;
		cond.paint = PAINT_BUTTON_AND_FIELD;
		return;
	}
	if (cond.pressed_button != BUTTON_PLAY) {
		cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_BACK][cond.theme_is_dark][cond.button_is_pressed];
		cond.status = (cond.pressed_button + 2) * 10;
		cond.paint = PAINT_BUTTON_AND_FIELD;
	}
}

void field_click(Condition& cond, int x, int y) {
	switch (cond.status / 10) {
	case 3:
		choosing_map(cond, x, y);
		break;
	case 4:
		choosing_difficulty(cond, x, y);
		break;
	case 5:
		choosing_theme(cond, x, y);
		break;
	default:
		break;
	}
}

void choosing_map(Condition& cond, int x, int y) {
	x -= (int)field_x + map0_x; y -= (int)field_y + map0_y;
	int map_num = x / (field_width * 2 + maps_dist_x) + (y / (field_height * 2 + maps_dist_y)) * 2;
	x %= (field_width * 2 + maps_dist_x), y %= (field_height * 2 + maps_dist_y);
	if (map_num < maps_quantity && x >= 0 && x <= field_width * 2 && y >= 0 && y <= field_height * 2) {
		cond.status = 20;
		cond.map = map_num;
		cond.walls_map.read_walls(map_file_names[map_num]);
		cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_PLAY][cond.theme_is_dark][cond.button_is_pressed];
		cond.paint = PAINT_BUTTON_AND_FIELD;
	}
}

void choosing_difficulty(Condition& cond, int x, int y) {
	x -= field_x + difficulties_dist; y -= field_y + difficulties_dist;
	int diff_num = y / (icons[DIFFICULTY][HEIGHT] + difficulties_dist);
	/*if (y < 0) {
		return;
	}*/
	y %= icons[DIFFICULTY][HEIGHT] + difficulties_dist;
	if (diff_num < 4 && x >= 0 && x <= icons[DIFFICULTY][WIDTH] + difficulties_dist + dificulties_text_width
		&& y >= 0 && y <= icons[DIFFICULTY][HEIGHT]) {
		cond.difficulty = diff_num;
		cond.Textures[TEXTURE_DIFFICULTY] = difficulty_file_names[diff_num][cond.theme_is_dark];
		cond.paint = PAINT_DIFFICULTY;
	}
}

void choosing_theme(Condition& cond, int x, int y) {
	if (x >= field_x + 5 && x <= field_x + 5 + tools_text_width && y >= field_y + 5 && y <= field_y + 5 + tools_text_height) {
		cond.theme_is_dark = !cond.theme_is_dark;
		cond.init_colors();
		cond.init_textures();
		cond.Textures[BUTTON_PLAY] = button_file_names[BUTTON_BACK][cond.theme_is_dark][cond.button_is_pressed];
		cond.paint = PAINT_ALL;
	}
}