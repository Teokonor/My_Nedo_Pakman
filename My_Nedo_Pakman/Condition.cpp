#include "Condition.h"
#include <fstream>

Condition::Condition() {
	init_condition("save_condition.txt");
}

void Condition::init_condition(std::istream& input) {
	input >> map >> difficulty >> theme_is_dark;
	walls_map.read_walls(map_file_names[map]);
	init_colors();
	Textures.fill("");
	init_textures();
}

void Condition::init_condition(const char file_name[]) {
	std::ifstream input(file_name);
	init_condition(input);
	input.close();
}

void Condition::init_textures() {
	for (size_t button_num = 0; button_num <= BUTTON_HELP; button_num++) {
		Textures[button_num] = button_file_names[button_num][theme_is_dark][button_is_pressed];
	}
	Textures[TEXTURE_DIFFICULTY] = difficulty_file_names[difficulty][theme_is_dark];
}

void Condition::init_colors() {
	BG_color = get_color(BG_colors[theme_is_dark]);
	field_color = get_color(field_colors[theme_is_dark]);
	walls_color = get_color(walls_colors[theme_is_dark]);
}

COLORREF Condition::get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}

void Condition::save_condition(std::ostream& output) {
	output << map << ' ' << difficulty << ' ' << theme_is_dark;
}

void Condition::save_condition(const char file_name[]) {
	std::ofstream output(file_name);
	save_condition(output);
	output.close();
}