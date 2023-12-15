#pragma once
#include "Constants.h"
#include "Walls_map.h"
#include <istream>
#include <Windows.h>

class Condition {
public:
	size_t status, map, difficulty;
	bool theme_is_light;
	COLORREF BG_color, field_color, walls_color;
	Walls_map walls_map;

	Condition();
	void init_condition(std::istream& input);
	void init_condition(const char file_name[]);
	Condition(Condition& other) = delete;
	Condition& operator=(Condition& other) = delete;

	COLORREF get_color(unsigned long HEX_code);
};

class Textures {

};
