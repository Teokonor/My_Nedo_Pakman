#pragma once
#include <array>
#include <istream>

const size_t playing_field_height = 101, playing_field_width = 185;

class Walls_map {
	std::array<bool, playing_field_height* playing_field_width> walls;
public:
	void read_walls(std::istream& input);
	bool wall_at_point(unsigned short x, unsigned short y) {
		return walls[y * playing_field_width + x];
	}
};