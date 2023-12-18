#pragma once
#include <string>

// cond.paint
#define NOT_PAINT 0
#define PAINT_BUTTON 1
#define PAINT_FIELD 2
#define PAINT_BUTTON_AND_FIELD 3
#define PAINT_DIFFICULTY 4
#define PAINT_ALL 10

//cond.pressed_button
#define BUTTON_PLAY 0
#define BUTTON_MAPS 1
#define BUTTON_DIFFICULTY 2
#define BUTTON_TOOLS 3
#define BUTTON_HELP 4
#define BUTTON_BACK 5
#define BUTTON_PAUSE 6
#define TEXTURE_DIFFICULTY 5

// cond.Textures[index]
// index
const size_t textures_quantity = 7;
//#define TEXTURE_BUTTON_PLAY 2
//#define TEXTURE_BUTTON_MAPS 3
//#define TEXTURE_BUTTON_DIFFICULTY 4
//#define TEXTURE_BUTTON_TOOLS 5
//#define TEXTURE_BUTTON_HELP 6

const size_t maps_quantity = 3;
const int map0_x = 61, map0_y = 33, maps_dist_x = 63, maps_dist_y = 35;
const std::string map_file_names[maps_quantity] = { "map0.txt", "map1.txt", "map2.txt" };

const int window_start_x = 300, window_start_y = 100, window_start_width = 1005 + 18, window_start_height = 705 + 38;

const int field_x = 40, field_y = 160;
const size_t field_height = 101, field_width = 185;

const int button_width = 60, button_height = 60, buttons_coord_y = 20,
buttons_coord_x[] = { 1005 / 2 - 30, 20, 100, 1005 - 160, 1005 - 80 };
const std::string button_file_names[7][2][2] = { 
	{ { "button_play_lite_up.bmp", "button_play_lite_down.bmp" }, { "button_play_dark_up.bmp", "button_play_dark_down.bmp" } },
	{ { "button_maps_lite_up.bmp", "button_maps_lite_down.bmp" }, { "button_maps_dark_up.bmp", "button_maps_dark_down.bmp" } },
	{ { "button_difficulty_lite_up.bmp", "button_difficulty_lite_down.bmp" }, { "button_difficulty_dark_up.bmp", "button_difficulty_dark_down.bmp" } },
	{ { "button_tools_lite_up.bmp", "button_tools_lite_down.bmp" }, { "button_tools_dark_up.bmp", "button_tools_dark_down.bmp" } },
	{ { "button_help_lite_up.bmp", "button_help_lite_down.bmp" }, { "button_help_dark_up.bmp", "button_help_dark_down.bmp" } },
	{ { "button_back_lite_up.bmp", "button_back_lite_down.bmp" }, { "button_back_dark_up.bmp", "button_back_dark_down.bmp" } },
	{ { "button_pause_lite_up.bmp", "button_pause_lite_down.bmp" }, { "button_pause_dark_up.bmp", "button_pause_dark_down.bmp" } },
};

#define FUEL_TIMER 0
#define SCORE_COUNTER 1
#define GAME_TIMER 2
#define DIFFICULTY 3
#define STARS 4
#define SCORE_RECORD 5
#define X_coord 0
#define Y_coord 1
#define WIDTH 2
#define HEIGHT 3
const int icons[6][4] = { { 40, 100, 72, 40 }, { 132, 102, 40, 36 }, { 1005 / 2 - 36, 100, 72, 40 }, 
	{ 600, 100, 40, 40 }, { 0, 100, 0, 40 }, { 1005 - 40 - 40, 102, 40, 36 } };
//const std::string icons_file_names[6][2][2] = {
//	{ { "", "" }, { "", "" } },
//	{ { "", "" }, { "", "" } },
//	{ { "", "" }, { "", "" } },
//	{ { "", "" }, { "", "" } },
//	{ { "", "" }, { "", "" } },
//	{ { "", "" }, { "", "" } }, 
//};

const std::string difficulty_file_names[4][2] = { 
	{ "difficulty0_lite.bmp", "difficulty0_dark.bmp" }, { "difficulty1_lite.bmp", "difficulty1_dark.bmp" }, 
	{ "difficulty2_lite.bmp", "difficulty2_dark.bmp" }, { "difficulty3_lite.bmp", "difficulty3_dark.bmp" } 
};
const int difficulties_dist = 10, dificulties_text_width = 140;
const std::wstring difficulties_names [4] = { L"лёгкая", L"средняя", L"сложная", L"молния" };

const std::wstring tools_text = L"Сменить тему";
const int tools_text_width = 250, tools_text_height = 40;

const size_t BG_colors[2] = { /*0xFFF1CD*/0xF8EACD, 0x202020 }, field_colors[2] = { 0xFFECBB, 0x303030 }, 
walls_colors[2] = { 0xBBA05B, 0x101010 }, text_colors[2] = { 0x101010, 0xAAAAAA };
const size_t timer_BG_color = 0xAAAAAA, timer_time_color = 0x444444, timer_border_color = 0x666666;
const size_t score_color[2] = { 0x057D9F, 0x39AECF };

const std::wstring help_text = L"Здесь инфа \nОп новая строка\n0:\n1:\n2:\n3:\n4:\n5:\n6:\n7:\n8:\n9:";