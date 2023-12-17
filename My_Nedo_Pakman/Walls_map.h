#pragma once
#include "Constants.h"
#include <array>
#include <istream>

class Walls_map {
	std::array<bool, playing_field_height* playing_field_width> walls;
public:
	Walls_map() {}
	Walls_map(std::istream& input) {
		read_walls(input);
	}
	Walls_map(const char file_name[]) {
		read_walls(file_name);
	}
	void read_walls(std::istream& input);
	void read_walls(const char file_name[]);
	bool wall_at_point(unsigned short x, unsigned short y) {
		return walls[y * playing_field_width + x];
	}
};