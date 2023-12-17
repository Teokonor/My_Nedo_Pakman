#include "Condition.h"
#include <fstream>

Condition::Condition() {
	init_condition("save_condition.txt");
}

void Condition::init_condition(std::istream& input) {
	input >> status >> map >> difficulty >> theme_is_dark;
	walls_map.read_walls("map0.txt");
	BG_color = get_color(0xFFF1CD);
	field_color = get_color(0xFFECBB);
	walls_color = get_color(0xBBA05B);
	Textures = { "button_play_lite_up.bmp", "button_maps_lite_up.bmp", "button_difficulty_lite_up.bmp", "button_tools_lite_up.bmp", 
		"button_help_lite_up.bmp", "", "" };
}

void Condition::init_condition(const char file_name[]) {
	std::ifstream input(file_name);
	init_condition(input);
	input.close();
}

COLORREF Condition::get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}