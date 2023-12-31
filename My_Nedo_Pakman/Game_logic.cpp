#include "Game_logic.h"

void Player::start(clock_t current_time) {
	start_time = current_time;
	cells_passed = 0;
	x_ = start_player_coords[X_coord];
	y_ = start_player_coords[Y_coord];
	lastX = x_; lastY = y_;
	direction = UP;
}

bool Player::change_direction(int new_dir) {
	if (new_dir >= UP && new_dir <= DOWN) {
		direction = new_dir;
		return true;
	}
	return false;
}

bool Player::move(Walls_map& walls, clock_t current_time) {
	if (current_time - start_time > cells_passed * millisec_in_cell) {
		cells_passed++;
		int x2 = x_ + ((direction == RIGHT) - (direction == LEFT)) * 2, y2 = y_ + ((direction == DOWN) - (direction == UP)) * 2,
			x1 = x2 - (direction == UP || direction == DOWN), y1 = y2 - (direction == RIGHT || direction == LEFT),
			x3 = x2 + (direction == UP || direction == DOWN), y3 = y2 + (direction == RIGHT || direction == LEFT);
		if (walls.wall_at_point(x1, y1) || walls.wall_at_point(x2, y2) || walls.wall_at_point(x3, y3)) {
			return false;
		}
		lastX = x_; lastY = y_;
		x_ = (x_ + x2) / 2; y_ = (y_ + y2) / 2;
		return true;
	}
	return false;
}

void Player::change_difficulty(int difficulty) {
	speed = player_speed[difficulty]; 
	millisec_in_cell = 1000 / speed;
}



void Enemy::init(int number, int difficulty) {
	num = number;
	x_ = start_enemy_coords[number][X_coord];
	y_ = start_enemy_coords[number][Y_coord];
	lastX = x_; lastY = y_;
	speed = enemy_speed[difficulty];
	millisec_in_cell = 1000. / speed;
}

void Enemy::start(clock_t current_time) {
	x_ = start_enemy_coords[num][X_coord];
	y_ = start_enemy_coords[num][Y_coord];
	lastX = x_; lastY = y_;
	start_time = current_time;
	cells_passed = 0;
}

bool Enemy::see_player(Walls_map& walls, int player_x, int player_y) {
	return false;
}

bool Enemy::move(Walls_map& walls, int player_x, int player_y, clock_t current_time) {
	double real_x = (double)x_ + 0.5, real_y = (double)y_ + 0.5, x0 = real_x, y0 = real_y,
		real_p_x = (double)player_x + 0.5, real_p_y = (double)player_y + 0.5;
	int int_x = x_, int_y = y_;
	int dir_x = player_x >= x_ ? 1 : -1, dir_y = player_y > y_ ? 1 : -1;
	double tg = player_x == x_ ? 1000. * (double)dir_y : (real_p_y - real_y) / (real_p_x - real_x);
	int next_x = (y0 + (real_x + 0.5 * (double)dir_x - x0) * tg) * (double)dir_y > (real_y + 0.5 * (double)dir_y) * (double)dir_y ? int_x : int_x + dir_x,
	 	next_y = (y0 + (real_x + 0.5 * (double)dir_x - x0) * tg) * (double)dir_y > (real_y + 0.5 * (double)dir_y) * (double)dir_y ? int_y + dir_y : int_y;
	double start_dist = sqrt(double((player_x - int_x) * (player_x - int_x) + (player_y - int_y) * (player_y - int_y))),
		next_dist = sqrt(double ((player_x - next_x) * (player_x - next_x) + (player_y - next_y) * (player_y - next_y)));
	if ((double)(current_time - start_time) <= cells_passed * millisec_in_cell) {
		return false;
	}
	cells_passed += (start_dist - next_dist);
	
	while (int_x != player_x || int_y != player_y) {
		if (walls.wall_at_point(int_x, int_y)) {
			return false;
		}
		if ((y0 + (real_x + 0.5 * (double)dir_x - x0) * tg) * (double)dir_y > (real_y + 0.5 * (double)dir_y) * (double)dir_y) {
			real_y += (double)dir_y;
			int_y += dir_y;
		}
		else {
			real_x += (double)dir_x;
			int_x += dir_x;
		}
	}
	/*if (y_ == next_y) {
		if ()
	}
	else {

	}*/
	if (y_ == next_y) {
		if (walls.wall_at_point(next_x + dir_x, y_ + 1) || walls.wall_at_point(next_x + dir_x, y_ - 1)) {
			return false;
		}
	}
	else {
		if (walls.wall_at_point(x_ + 1, next_y + dir_y) || walls.wall_at_point(x_ - 1, next_y + dir_y)) {
			return false;
		}
	}
	lastX = x_; lastY = y_;
	x_ = next_x; y_ = next_y;
	return true;
}

bool Enemy::catch_player(int player_x, int player_y) {
	return abs(player_x - x_) < 3 && abs(player_y - y_) < 3;
}