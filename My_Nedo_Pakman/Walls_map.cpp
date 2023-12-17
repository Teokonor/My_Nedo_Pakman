#include "Walls_map.h"
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