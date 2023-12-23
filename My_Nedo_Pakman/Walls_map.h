#pragma once
#include "Constants.h"
#include <array>
#include <istream>

class Walls_map {
	std::array<bool, field_height* field_width> walls;
public:
	Walls_map() {}
	Walls_map(std::istream& input) {
		read_walls(input);
	}
	Walls_map(std::string file_name) {
		read_walls(file_name);
	}
	void read_walls(std::istream& input);
	void read_walls(std::string file_name);
	bool wall_at_point(int x, int y) {
		return walls[y * field_width + x];
	}
};