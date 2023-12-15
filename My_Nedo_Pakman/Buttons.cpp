#include "Buttons.h"

void left_button_down(Condition& cond, int x, int y) {
	if (y >= buttons_coord_y && y <= buttons_coord_y + button_height) {
		for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
			if (x >= buttons_coord_x[button_id] && x <= buttons_coord_x[button_id] + button_width) {
				cond.pressed_button = button_id;
				cond.button_is_pressed = true;
				cond.paint = PAINT_BUTTON;
				cond.Textures[button_id].erase(cond.Textures[button_id].size() - 6, 6);
				cond.Textures[button_id] += "down.bmp";
				break;
			}
		}
	}
}

void left_button_up(Condition& cond, int x, int y) {
	if (cond.button_is_pressed) {
		cond.button_is_pressed = true;
		cond.Textures[cond.pressed_button].erase(cond.Textures[cond.pressed_button].size() - 8, 8);
		cond.Textures[cond.pressed_button] += "up.bmp";
		if (x >= buttons_coord_x[cond.pressed_button] && x <= buttons_coord_x[cond.pressed_button] + button_width
			&& y >= buttons_coord_y && y <= buttons_coord_y + button_height) {
			// Здесь произошёл факт нажатия, а значит должно было измениться состояние
			cond.paint = PAINT_BUTTON;
		}
		else {
			cond.paint = PAINT_BUTTON;
		}
	}
}