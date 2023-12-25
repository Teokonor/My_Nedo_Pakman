#pragma once
#include "Constants.h"
#include <array>
#include <istream>
#include <list>

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

struct Particle {
	clock_t time;
	int type;
	bool adding;
	int x, y;
	Particle(clock_t time_, int type_, bool adding_, int x_, int y_) : time(time_), type(type_), adding(adding_), x(x_), y(y_) {}
};

void read_particles(std::list<Particle>& shedule, std::istream& input);

void read_particles(std::list<Particle>& shedule, std::string file_name);