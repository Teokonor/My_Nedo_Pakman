#pragma once
#include "Walls_map.h"
#include <iostream>
#include <array>
#include <Windows.h>

class Condition {
public:
	WNDCLASS window_class;
	HWND hWnd;
	HWND text_vidget = 0;
	int window_height = window_start_height, window_width = window_start_width;
	int status = 20, map, difficulty;
	int paint = PAINT_ALL, pressed_button = BUTTON_PLAY;
	bool theme_is_dark, button_is_pressed = false;
	COLORREF BG_color, field_color, walls_color, text_color;
	Walls_map walls_map;
	std::array<std::string, textures_quantity> Textures;

	Condition();
	void init_condition(std::istream& input);
	void init_condition(const char file_name[]);
	void init_textures();
	void init_colors();
	Condition(Condition& other) = delete;
	Condition& operator=(Condition& other) = delete;
	void save_condition(std::ostream& output);
	void save_condition(const char file_name[]);
};

COLORREF get_color(unsigned long HEX_code);