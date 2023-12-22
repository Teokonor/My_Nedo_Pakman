#include "Game_logic.h"

void Player::start(clock_t current_time) {
	start_time = current_time;
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
		int new_x = x_ + (direction == RIGHT) - (direction == LEFT), new_y = y_ + (direction == DOWN) - (direction == UP);
		if (!walls.wall_at_point(new_x, new_y)) {
			x_ = new_x; y_ = new_y;
			return true;
		}
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
	speed = enemy_speed[difficulty];
}

void Enemy::start(clock_t current_time) {
	x_ = start_enemy_coords[num][X_coord];
	y_ = start_enemy_coords[num][Y_coord];
	start_time = current_time;
}

bool Enemy::see_player(Walls_map& walls, int player_x, int player_y) {
	double real_x = (double)x_ + 0.5, real_y = (double)y_ + 0.5, x0 = real_x, y0 = real_y,
		real_p_x = (double)player_x + 0.5, real_p_y = (double)player_y + 0.5;
	int int_x = x_, int_y = y_;
	int dir_x = player_x > x_ ? 1 : -1, dir_y = player_y > y_ ? 1 : -1;
	double tg = player_x == x_ ? 1000. : (real_p_y - real_y) / (real_p_x = real_x);
	while (int_x != player_x || int_y != player_y) {
		if (walls.wall_at_point(int_x, int_y)) {
			return false;
		}
		if (y0 + (real_x + 0.5 * (double)dir_x - x0) * tg > real_y + 0.5 * (double)dir_y) {
			real_y += (double)dir_y;
			int_y += dir_y;
		}
		else {
			real_x += (double)dir_x;
			int_x += dir_x;
		}
	}
	return true;
}

bool Enemy::move(Walls_map& walls, int player_x, int player_y, clock_t current_time) {
	return false;
}

bool Enemy::catch_player(int player_x, int player_y) {
	return abs(player_x - x_) < 3 && abs(player_y - y_) < 3;
}