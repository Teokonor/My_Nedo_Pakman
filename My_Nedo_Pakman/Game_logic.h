#pragma once
#include "Walls_map.h"

#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
class Player {
	int x_ = start_player_coords[X_coord], y_ = start_player_coords[Y_coord], direction = UP;
	size_t speed/*cells per second*/, cells_passed = 0;
	clock_t	millisec_in_cell, start_time = 0;
public:
	Player() : speed(player_speed[0]), millisec_in_cell(1000 / speed) {}
	Player(Player& other) = delete;
	Player& operator=(Player& other) = delete;

	int x() { return x_; }
	int y() { return y_; }
	void start(clock_t current_time);
	bool change_direction(int new_dir);
	bool move(Walls_map& walls, clock_t current_time);
	void change_difficulty(int difficulty);
};

class Enemy {
	int x_, y_, speed, num = 0;
	clock_t start_time;
public:
	int x() { return x_; }
	int y() { return y_; }
	void init(int number, int difficulty);
	void start(clock_t current_time);
	bool see_player(Walls_map& walls, int player_x, int player_y);
	bool move(Walls_map& walls, int player_x, int player_y, clock_t current_time);
	bool catch_player(int player_x, int player_y);
};