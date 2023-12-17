#pragma once
#include <string>

// cond.paint
#define NOT_PAINT 0
#define PAINT_BUTTON 1
#define PAINT_FIELD 2
#define PAINT_BUTTON_AND_FIELD 3
#define PAINT_ALL 10

//cond.pressed_button
#define BUTTON_PLAY 0
#define BUTTON_MAPS 1
#define BUTTON_DIFFICULTY 2
#define BUTTON_TOOLS 3
#define BUTTON_HELP 4

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

const int window_start_x = 300, window_start_y = 100, window_start_width = 1005 + 18, window_start_height = 705 + 38;

const int field_x = 40, field_y = 160;

const size_t playing_field_height = 101, playing_field_width = 185;

const int button_width = 60, button_height = 60, buttons_coord_y = 20,
buttons_coord_x[5] = { 1005 / 2 - 30, 20, 100, 1005 - 160, 1005 - 80 };

const std::string button_file_names[7][2][2] = { 
	{ { "button_play_lite_up.bmp", "button_play_lite_down.bmp" }, { "button_play_dark_up.bmp", "button_play_dark_down.bmp" } },
	{ { "button_maps_lite_up.bmp", "button_maps_lite_down.bmp" }, { "button_maps_dark_up.bmp", "button_maps_dark_down.bmp" } },
	{ { "button_difficulty_lite_up.bmp", "button_difficulty_lite_down.bmp" }, { "button_difficulty_dark_up.bmp", "button_difficulty_dark_down.bmp" } },
	{ { "button_tools_lite_up.bmp", "button_tools_lite_down.bmp" }, { "button_tools_dark_up.bmp", "button_tools_dark_down.bmp" } },
	{ { "button_help_lite_up.bmp", "button_help_lite_down.bmp" }, { "button_help_dark_up.bmp", "button_help_dark_down.bmp" } },
	{ { "button_back_lite_up.bmp", "button_back_lite_down.bmp" }, { "button_back_dark_up.bmp", "button_back_dark_down.bmp" } },
	{ { "button_pause_lite_up.bmp", "button_pause_lite_down.bmp" }, { "button_pause_dark_up.bmp", "button_pause_dark_down.bmp" } },
};