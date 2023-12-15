#pragma once
// cond.paint
#define NOT_PAINT 0
#define PAINT_BUTTON 1
#define PAINT_FIELD 2
#define PAINT_ALL 10

//cond.pressed_button
#define BUTTON_PLAY 2
#define BUTTON_MAPS 3
#define BUTTON_DIFFICULTY 4
#define BUTTON_TOOLS 5
#define BUTTON_HELP 6

// cond.Textures[index]
// index
const size_t textures_quantity = 7;
#define TEXTURE_BUTTON_PLAY 2
#define TEXTURE_BUTTON_MAPS 3
#define TEXTURE_BUTTON_DIFFICULTY 4
#define TEXTURE_BUTTON_TOOLS 5
#define TEXTURE_BUTTON_HELP 6

const int window_start_x = 300, window_start_y = 100, window_start_width = 1005 + 17, window_start_height = 705 + 38;

const int field_x = 40, field_y = 160;

const size_t playing_field_height = 101, playing_field_width = 185;
