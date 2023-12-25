#include "Condition.h"
#include <fstream>

Condition::Condition() {
	init_condition("save_condition.txt");
}

void Condition::init_condition(std::istream& input) {
	input >> map >> difficulty >> theme_is_dark;
	for (size_t cur_map = 0; cur_map < maps_quantity; cur_map++) {
		for (size_t cur_diff = 0; cur_diff < 4; cur_diff++) {
			input >> scores[cur_map][cur_diff];
		}
	}
	walls_map.read_walls(map_file_names[map]);
	read_particles(shedule_of_particles, particles_file_names[map][difficulty]);
	init_colors();
	Textures.fill("");
	init_textures();
	init_difficulties();
}

void Condition::init_condition(const char file_name[]) {
	std::ifstream input(file_name);
	init_condition(input);
	input.close();
}

void Condition::init_textures() {
	for (size_t button_num = 0; button_num <= BUTTON_HELP; button_num++) {
		Textures[button_num] = button_file_names[button_num][theme_is_dark][button_is_pressed];
	}
	Textures[TEXTURE_DIFFICULTY] = difficulty_file_names[difficulty][theme_is_dark];
	Textures[TEXTURE_PLAYER] = player_file_names[theme_is_dark];
	Textures[TEXTURE_ENEMY] = enemy_file_names[theme_is_dark];
}

void Condition::init_colors() {
	BG_color = get_color(BG_colors[theme_is_dark]);
	field_color = get_color(field_colors[theme_is_dark]);
	walls_color = get_color(walls_colors[theme_is_dark]);
	text_color = get_color(text_colors[theme_is_dark]);
}

void Condition::init_difficulties() {
	pl.change_difficulty(difficulty);
	for (size_t i = 0; i < 3; i++) {
		enemies[i].init(i, difficulty);
	}
}

COLORREF get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}

void Condition::save_condition(std::ostream& output) {
	output << map << ' ' << difficulty << ' ' << theme_is_dark << '\n';
	for (size_t cur_map = 0; cur_map < maps_quantity; cur_map++) {
		for (size_t cur_diff = 0; cur_diff < 4; cur_diff++) {
			output << scores[cur_map][cur_diff] << ' ';
		}
		output << '\n';
	}
}

void Condition::save_condition(const char file_name[]) {
	std::ofstream output(file_name);
	save_condition(output);
	output.close();
}

void Condition::start_game() {
	status = 26;
	particles_map.clear();
	score = 0;
	game_time = game_duration;
	fuel_time = start_fuel_timer;
	read_particles(shedule_of_particles, particles_file_names[map][difficulty]);
	game_started = std::clock();
	pl.start(game_started);
	for (Enemy& en : enemies) {
		en.start(game_started);
	}
	for (size_t i = 0; i < 3; i++) {
		enemies[i].start(game_started);
	}
}

void Condition::process_game() {
	// process_game постоянно вызывается в главном цикле, но выполняться должен только в случае если игра идёт, так что проверка статуса
	// status == 26 нужен в момент запуска игры, чтобы один раз обработалось WM_PAINT с флагом PAINT_BUTTON_AND_FIELD
	if (status != 21) {
		if (status == 26) {
			status = 21;
		}
		return;
	}
	// Фиксируем время текущего момента
	clock_t now = std::clock();
	// Смотрим расписание частиц. Обрабатываем все его элементы, чьё время меньше либо равно текущему
	while (shedule_of_particles.size() > 0) {
		Particle particle = shedule_of_particles.front();
		if (particle.time > now - game_started) {
			break;
		}
		if (particle.adding) {
			coords co = { particle.x, particle.y };
			particles_map.insert({ co , particle.type });
		}
		else /*if (particles_map.find({ particle.x, particle.y }) != particles_map.end())*/ {
			particles_map.erase({ particle.x, particle.y });
			deleting_particles.push_back({ particle.x, particle.y });
		}
		shedule_of_particles.pop_front();
	}
	// Вызываем метод движения игрока. Тот уже сам определяет, двинется игрок или нет
	change_player_pos = pl.move(walls_map, now);
	// Осматриваем текущий + предыдущий хитбокс игрока. Если в нём есть частица, съедаем её
	for (int x = (pl.x() < pl.last_x() ? pl.x() : pl.last_x()) - 1; x <= (pl.x() > pl.last_x() ? pl.x() : pl.last_x()) + 1; x++) {
		for (int y = (pl.y() < pl.last_y() ? pl.y() : pl.last_y()) - 1; y <= (pl.y() > pl.last_y() ? pl.y() : pl.last_y()) + 1; y++) {
	/*for (int x = min(pl.x(), pl.last_x()) - 1; x <= max(pl.x(), pl.last_x()) + 1; x++) {
		for (int y = min(pl.y(), pl.last_y()) - 1; y <= max(pl.y(), pl.last_y()) + 1; y++) {*/
			auto elem = particles_map.find({ x, y });
			if (elem != particles_map.end()) {
				take_particle(elem->second);
				particles_map.erase(elem);
			}
		}
	}
	// Вызываем методы движения врагов. Также, проверяем, не поймал ли один из них игрока
	for (size_t i = 0; i < 3; i ++) {
		change_enemy_pos[i] = enemies[i].move(walls_map, pl.x(), pl.y(), now);
		if (enemies[i].catch_player(pl.x(), pl.y())) {
			stop_game();
			return;
		}
	}
	// Проверяем, не закончилось ли время на таймерах
	if (now - game_started > game_time || now - game_started > fuel_time) {
		stop_game();
	}
	// Пересчитываем видимые значения таймеров и отмечаем, что их нужно перерисовать, если эти значения изменились
	if (game_timer_value != (game_time + game_started - now - 1) / 1000 + 1) {
		game_timer_value = (game_time + game_started - now - 1) / 1000 + 1;
		change_game_timer = true;
	}
	if (fuel_timer_value != (fuel_time + game_started - now - 1) / 1000 + 1) {
		fuel_timer_value = (fuel_time + game_started - now - 1) / 1000 + 1;
		change_fuel_timer = true;
	}
	// Ставим нужный paint фраг и вызываем событие WM_PAINT
	paint = PAINT_GAME_ELEMS;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
}

void Condition::pause_game() {
	status = 22;
	game_paused = std::clock();
}

void Condition::resume_game() {
	status = 26;
	clock_t time_shift = std::clock() - game_paused;
	game_started += time_shift;
	pl.resume_after_pause(time_shift);
	for (size_t i = 0; i < 3; i++) {
		enemies[i].resume_after_pause(time_shift);
	}
}

void Condition::stop_game() {
	if (status != 21 && status != 22) {
		return;
	}
	status = 20;
	scores[map][difficulty] = score > scores[map][difficulty] ? score : scores[map][difficulty];
	paint = PAINT_RECORD;
}

void Condition::take_particle(int type) {
	switch (type)
	{
	case FUEL_TYPE:
		fuel_time += fuel_timer_rising;
		break;
	case SCORE_TYPE:
		score++;
		change_score = true;
		break;
	default:
		break;
	}
}