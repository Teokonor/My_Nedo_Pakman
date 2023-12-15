#pragma once
#include <istream>
#include <Windows.h>

class Condition {
public:
	size_t status, map, difficulty;
	bool theme_is_light;
	COLORREF BG_color;

	Condition();
	void init_condition(std::istream& input);
	Condition(Condition& other) = delete;
	Condition& operator=(Condition& other) = delete;

	COLORREF get_color(unsigned long HEX_code);
};

class Textures {

};
