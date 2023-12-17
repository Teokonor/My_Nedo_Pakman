#include "Clicks.h"

void left_button_down(Condition& cond, int x, int y) {
	if (y >= buttons_coord_y && y <= buttons_coord_y + button_height) {
		for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
			if (x >= buttons_coord_x[button_id] && x <= buttons_coord_x[button_id] + button_width) {
				cond.pressed_button = button_id;
				cond.button_is_pressed = true;
				cond.paint = PAINT_BUTTON;
				cond.Textures[button_id] = button_file_names[button_id][cond.theme_is_dark][cond.button_is_pressed];
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
	if (cond.pressed_button == BUTTON_MAPS) {
		cond.status = 30;
		cond.paint = PAINT_BUTTON_AND_FIELD;
	}
}

void field_click(Condition& cond, int x, int y) {
	switch (cond.status / 10) {
	case 3:
		choosing_map(cond, x, y);
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

void choosing_map(Condition& cond, int x, int y) {
	for (size_t i = 0; i < maps_quantity; i++) {

	}
}