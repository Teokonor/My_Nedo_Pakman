#pragma once
#include "Game_logic.h"
#include <iostream>
#include <array>
#include <Windows.h>

class Condition {
public:
	bool active = true;
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
	std::array<std::array<short, 4>, maps_quantity> scores;
	short score = 0;
	Player pl;
	Enemy enemies[3];
	clock_t game_started = 0, game_time = game_duration, fuel_time = start_fuel_timer;
	bool change_game_timer = false, change_fuel_timer = false, change_player_pos = false, change_enemy_pos[3] = { false, false, false };
	unsigned int game_timer_value = game_duration / 1000, fuel_timer_value = start_fuel_timer / 1000;

	Condition();
	void init_condition(std::istream& input);
	void init_condition(const char file_name[]);
	void init_textures();
	void init_colors();
	void init_difficulties();
	Condition(Condition& other) = delete;
	Condition& operator=(Condition& other) = delete;
	void save_condition(std::ostream& output);
	void save_condition(const char file_name[]);
	void start_game();
	void process_game();
	void pause_game();
	void resume_game();
	void stop_game();
};

COLORREF get_color(unsigned long HEX_code);