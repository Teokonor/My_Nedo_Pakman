#include "Condition.h"
#include <fstream>

Condition::Condition() {
	init_condition("save_condition.txt");
}

void Condition::init_condition(std::istream& input) {
	input >> map >> difficulty >> theme_is_dark;
	for (size_t cur_map = 0; cur_map < maps_quantity; cur_map++) {
		for (size_t cur_diff = 0; cur_diff < 4; cur_diff++) {
			input >> scores[cur_map][cur_diff];
		}
	}
	walls_map.read_walls(map_file_names[map]);
	init_colors();
	Textures.fill("");
	init_textures();
	init_difficulties();
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
	text_color = get_color(text_colors[theme_is_dark]);
}

void Condition::init_difficulties() {
	pl.change_difficulty(difficulty);
	for (size_t i = 0; i < 3; i++) {
		enemies[i].init(i, difficulty);
	}
}

COLORREF get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}

void Condition::save_condition(std::ostream& output) {
	output << map << ' ' << difficulty << ' ' << theme_is_dark << '\n';
	for (size_t cur_map = 0; cur_map < maps_quantity; cur_map++) {
		for (size_t cur_diff = 0; cur_diff < 4; cur_diff++) {
			output << scores[cur_map][cur_diff] << ' ';
		}
		output << '\n';
	}
}

void Condition::save_condition(const char file_name[]) {
	std::ofstream output(file_name);
	save_condition(output);
	output.close();
}

void Condition::start_game() {
	game_started = std::clock();
	pl.start(game_started);
	for (Enemy& en : enemies) {
		en.start(game_started);
	}
}

void Condition::process_game() {
	if (status != 21) {
		return;
	}
	pl.move(walls_map, std::clock());
	for (size_t i = 0; i < 3; i ++) {
		change_enemy_pos[i] = enemies[i].move(walls_map, pl.x(), pl.y(), std::clock());
		if (enemies[i].catch_player(pl.x(), pl.y())) {
			stop_game();
			return;
		}
	}
	if (std::clock() - game_started > game_time || std::clock() - game_started > fuel_time) {
		stop_game();
	}
	if (game_timer_value != (game_time + game_started - std::clock()) / 1000) {
		game_timer_value = (game_time + game_started - std::clock()) / 1000;
		change_game_timer = true;
		//MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);
	}
	if (fuel_timer_value != (fuel_time + game_started - std::clock()) / 1000) {
		fuel_timer_value = (fuel_time + game_started - std::clock()) / 1000;
		change_fuel_timer = true;
		//MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);
	}
	/*change_game_timer = (game_timer_value != (game_time + game_started - std::clock()) / 1000);
	game_timer_value = (game_time + game_started - std::clock()) / 1000;
	change_fuel_timer = (fuel_timer_value != (fuel_time + game_started - std::clock()) / 1000);
	fuel_timer_value = (fuel_time + game_started - std::clock()) / 1000;*/
	paint = PAINT_GAME_ELEMS;
	//UpdateWindow(hWnd);
	RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
}

void Condition::pause_game() {

}
void Condition::resume_game() {

}
void Condition::stop_game() {
	status = 20;
}