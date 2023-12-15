#include "Condition.h"
#include <fstream>

Condition::Condition() {
	init_condition("save_condition");
}

void Condition::init_condition(std::istream& input) {
	input >> status >> map >> difficulty >> theme_is_light;
	walls_map.read_walls("first_walls_map.txt");
	BG_color = get_color(0xFFF1CD);
	field_color = get_color(0xFFECBB);
	walls_color = get_color(0xBBA05B);
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