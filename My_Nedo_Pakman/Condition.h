#pragma once
#include "Constants.h"
#include "Walls_map.h"
#include <istream>
#include <string>
#include <array>
#include <Windows.h>

class Condition {
public:
	HWND hWnd;
	size_t status, map, difficulty;
	int paint = PAINT_ALL, pressed_button = BUTTON_PLAY;
	bool theme_is_light, button_is_pressed = false;
	COLORREF BG_color, field_color, walls_color;
	Walls_map walls_map;
	std::array<std::string, textures_quantity> Textures;

	Condition();
	void init_condition(std::istream& input);
	void init_condition(const char file_name[]);
	Condition(Condition& other) = delete;
	Condition& operator=(Condition& other) = delete;

	COLORREF get_color(unsigned long HEX_code);
};
