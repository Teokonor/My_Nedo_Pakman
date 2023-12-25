#include "Map_info.h"
#include <fstream>

void Walls_map::read_walls(std::istream& input) {
	unsigned short horisontal, vertical;
	input >> horisontal >> vertical;
	walls.fill(false);
	for (unsigned short wall_num = 0; wall_num < horisontal; wall_num++) {
		unsigned short start_x, finish_x, y;
		input >> start_x >> y >> finish_x >> y;
		for (unsigned short x = start_x; x <= finish_x; x++) {
			walls[y * field_width + x] = true;
		}
	}
	for (unsigned short wall_num = 0; wall_num < vertical; wall_num++) {
		unsigned short x, start_y, finish_y;
		input >> x >> start_y >> x >> finish_y;
		for (unsigned short y = start_y; y <= finish_y; y++) {
			walls[y * field_width + x] = true;
		}
	}
}

void Walls_map::read_walls(std::string file_name) {
	std::ifstream input_file(file_name);
	read_walls(input_file);
	input_file.close();
}

void read_particles(std::list<Particle>& shedule, std::istream& input) {
	std::list<Particle> adding, deleting;
	size_t quantity;
	input >> quantity;
	clock_t time; int type, x, y;
	while (!input.eof()) {
		input >> time >> type >> x >> y;
		Particle add(time, type, true, x, y), del(time + particles_life_length, type, false, x, y);
		adding.push_back(add);
		if (del.time < game_duration) {
			deleting.push_back(del);
		}
	}
	while (adding.size() + deleting.size() > 0) {
		if (adding.size() == 0) {
			shedule.push_back(deleting.front());
			deleting.pop_front();
		}
		else if (deleting.size() == 0) {
			shedule.push_back(adding.front());
			adding.pop_front();
		}
		else if (deleting.front().time < adding.front().time) {
			shedule.push_back(deleting.front());
			deleting.pop_front();
		}
		else {
			shedule.push_back(adding.front());
			adding.pop_front();
		}
	}
	int ab = 10;
}

void read_particles(std::list<Particle>& shedule, std::string file_name) {
	std::ifstream input_file(file_name);
	read_particles(shedule, input_file);
	input_file.close();
}