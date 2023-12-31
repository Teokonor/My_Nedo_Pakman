#pragma once
#include "Map_info.h"

#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
class Player {
	int x_ = start_player_coords[X_coord], y_ = start_player_coords[Y_coord], lastX = x_, lastY = y_, direction = UP;
	size_t speed/*cells per second*/, cells_passed = 0;
	clock_t	millisec_in_cell, start_time = 0;
public:
	Player() : speed(player_speed[0]), millisec_in_cell(1000 / speed) {}
	Player(Player& other) = delete;
	Player& operator=(Player& other) = delete;

	int x() { return x_; }
	int y() { return y_; }
	int last_x() { return lastX; }
	int last_y() { return lastY; }
	void start(clock_t current_time);
	bool change_direction(int new_dir);
	bool move(Walls_map& walls, clock_t current_time);
	void change_difficulty(int difficulty);
	void resume_after_pause(clock_t time_shift) {
		start_time += time_shift;
	}
};

class Enemy {
	int x_, y_, lastX, lastY, num = 0;
	clock_t start_time;
	double speed, millisec_in_cell = 0., cells_passed = 0.;
public:
	int x() { return x_; }
	int y() { return y_; }
	int last_x() { return lastX; }
	int last_y() { return lastY; }
	void init(int number, int difficulty);
	void start(clock_t current_time);
	bool see_player(Walls_map& walls, int player_x, int player_y);
	bool move(Walls_map& walls, int player_x, int player_y, clock_t current_time);
	bool catch_player(int player_x, int player_y);
	void resume_after_pause(clock_t time_shift) {
		start_time += time_shift;
	}
};