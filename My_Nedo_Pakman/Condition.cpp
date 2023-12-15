#include "Condition.h"
#include <fstream>

Condition::Condition() {
	std::ifstream input("save_condition.txt");
	init_condition(input);
	input.close();
}

void Condition::init_condition(std::istream& input) {
	input >> status >> map >> difficulty >> theme_is_light;
	BG_color = get_color(0xFFF1CD);
}

COLORREF Condition::get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}