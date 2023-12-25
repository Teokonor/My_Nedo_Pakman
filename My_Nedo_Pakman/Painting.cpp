#include "Painting.h"

LPCWSTR stowchar(std::string str) {
	std::wstring* wstr = new std::wstring;
	*wstr = std::wstring(str.begin(), str.end());
	return wstr->c_str();
}

void Painter::paint(Condition& cond) {
	switch (cond.paint)
	{
	case PAINT_BUTTON:
		paint_button(cond);
		break;
	case PAINT_FIELD:
		paint_field(cond);
		break;
	case PAINT_BUTTON_AND_FIELD:
		paint_button(cond);
		paint_field(cond);
		break;
	case PAINT_DIFFICULTY:
		paint_difficulty(cond);
		break;
	case PAINT_GAME_ELEMS:
		paint_game_elems(cond);
		break;
	case PAINT_BUTTON_AND_GAME_ELEMS:
		paint_button(cond);
		paint_game_elems(cond);
		break;
	case PAINT_RECORD:
		paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
		paint_stars(cond);
		break;
	case PAINT_BUTTON_AND_RECORD:
		paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
		paint_stars(cond);
		paint_button(cond);
		break;
	case PAINT_BUTTON_AND_FIELD_AND_RECORD:
		paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
		paint_stars(cond);
		paint_button(cond);
		paint_field(cond);
		break;
	case PAINT_ALL:
		paint_all(cond);
		break;
	default:
		break;
	}
	cond.paint = NOT_PAINT;
}

void WinApi_painter::paint_icon(int x, int y, int width, int height, std::string file_name) {
	HDC hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	hBitmap = LoadImageW(NULL, stowchar(file_name), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObjectW(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hdc);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	StretchBlt(hdc, x, y, width, height, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}

void WinApi_painter::paint_text(RECT rect, int letter_height, int letter_width, COLORREF color, LPCWSTR text) {
	/*HFONT my_font = CreateFontA(40, 15, 0, 0, FW_MEDIUM, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DECORATIVE, "MyFont");*/
	HFONT my_font = CreateFontA(letter_height, letter_width, 0, 0, 551, 0, 0, 0, 
		DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_DONTCARE, "MyFont");
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	SelectObject(hdc, my_font);
	DrawTextW(hdc, text, -1, &rect, 0);
}

void WinApi_painter::paint_button(Condition& cond) {
	int pressed_button = cond.pressed_button;
	paint_icon(buttons_coord_x[cond.pressed_button], buttons_coord_y, button_width, button_height, cond.Textures[cond.pressed_button]);
	cond.pressed_button = BUTTON_PLAY;
	paint_icon(buttons_coord_x[cond.pressed_button], buttons_coord_y, button_width, button_height, cond.Textures[cond.pressed_button]);
	cond.pressed_button = pressed_button;
}

void WinApi_painter::paint_difficulty(Condition& cond) {
	paint_icon(icons[DIFFICULTY][X_coord], icons[DIFFICULTY][Y_coord], icons[DIFFICULTY][WIDTH], icons[DIFFICULTY][HEIGHT],
		cond.Textures[TEXTURE_DIFFICULTY]);
	paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
	paint_stars(cond);
}



void WinApi_painter::paint_timer(Condition& cond, int x, int y, int seconds) {
	RECT border_rect = { x, y, x + icons[FUEL_TIMER][WIDTH], y + icons[FUEL_TIMER][HEIGHT] };
	FillRect(hdc, &border_rect, CreateSolidBrush(get_color(timer_border_color)));
	RECT timer_rect = { x + 2, y + 2, x + icons[FUEL_TIMER][WIDTH] - 2, y + icons[FUEL_TIMER][HEIGHT] - 2 };
	FillRect(hdc, &timer_rect, CreateSolidBrush(get_color(timer_BG_color)));
	RECT time_rect = { x + 6, y + 2, x + icons[FUEL_TIMER][WIDTH] - 6, y + icons[FUEL_TIMER][HEIGHT] - 2 };
	int minutes = seconds / 60; seconds %= 60;
	wchar_t time[] = L"0:00";
	time[0] = (wchar_t)(minutes + 48); time[2] = (wchar_t)(seconds / 10 + 48); time[3] = (wchar_t)(seconds % 10 + 48);
	paint_text(time_rect, 36, 13, get_color(timer_time_color), time);
}

void WinApi_painter::paint_score(Condition& cond, int x, int y, int score_) {
	RECT score_rect = { x, y, x + icons[SCORE_COUNTER][WIDTH], y + icons[SCORE_COUNTER][HEIGHT]};
	FillRect(hdc, &score_rect, CreateSolidBrush(cond.BG_color));
	wchar_t text_score[] = L"00";
	text_score[0] = (wchar_t)(score_ / 10 + 48); text_score[1] = (wchar_t)(score_ % 10 + 48);
	paint_text(score_rect, 36, 13, get_color(score_color[cond.theme_is_dark]), text_score);
}

void WinApi_painter::paint_stars(Condition& cond) {
	RECT stars_rect = { icons[STARS][X_coord], icons[STARS][Y_coord], 
		icons[STARS][X_coord] + icons[STARS][WIDTH], icons[STARS][Y_coord] + icons[STARS][HEIGHT] };
	FillRect(hdc, &stars_rect, CreateSolidBrush(cond.BG_color));
	int x = icons[STARS][X_coord] + icons[STARS][HEIGHT] * 4; 
	short score = cond.scores[cond.map][cond.difficulty];
	for (short score_to_star = 10; score_to_star <= 50; score_to_star += 10) {
		paint_icon(x, icons[STARS][Y_coord], icons[STARS][HEIGHT], icons[STARS][HEIGHT], 
			star_file_names[cond.theme_is_dark][score / score_to_star != 0]);
		x -= icons[STARS][HEIGHT];
	}
}

void WinApi_painter::paint_field(Condition& cond) {
	RECT field_rect = { field_x + field_width * 5, field_y, field_x, field_y + field_height * 5 };
	FillRect(hdc, &field_rect, CreateSolidBrush(cond.field_color));
	Walls_map* old_map = new Walls_map(cond.walls_map);
	cond.walls_map.read_walls("map_empty.txt");
	paint_walls(cond, 5, field_x, field_y);
	cond.walls_map = *old_map;
	delete(old_map);
	switch (cond.status / 10) {
	case 2:
		paint_playing_field(cond);
		break;
	case 3:
		paint_maps_field(cond);
		break;
	case 4:
		paint_difficulties_field(cond);
		break;
	case 5:
		paint_tools_field(cond);
		break;
	case 6:
		paint_help_field(cond);
		break;
	default:
		break;
	}
}

void WinApi_painter::paint_walls(Condition& cond, int thickness, int x0, int y0) {
	HBRUSH brush = CreateSolidBrush(cond.walls_color);
	for (size_t y = 0; y < field_height; y++) {
		for (size_t x = 0; x < field_width; x++) {
			if (cond.walls_map.wall_at_point(x, y)) {
				RECT rect = { x0 + (x + 1) * thickness, y0 + y * thickness, x0 + x * thickness, y0 + (y + 1) * thickness };
				FillRect(hdc, &rect, brush);
			}
		}
	}
}

void WinApi_painter::paint_playing_field(Condition& cond) {
	paint_walls(cond, 5, field_x, field_y);
	paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
	paint_stars(cond);
	paint_player(cond);
	for (size_t i = 0; i < 3; i++) {
		paint_enemy(cond, i);
	}
}

void WinApi_painter::paint_maps_field(Condition& cond) {
	Walls_map* old_map = new Walls_map(cond.walls_map);
	for (size_t i = 0; i < maps_quantity; i++) {
		cond.walls_map.read_walls(map_file_names[i]);
		paint_walls(cond, 2, field_x + map0_x + (i % 2) * (maps_dist_x + field_width * 2), 
			field_y + map0_y + (i / 2) * (maps_dist_y + field_height * 2));
	}
	cond.walls_map = *old_map;
	delete(old_map);
}

void WinApi_painter::paint_difficulties_field(Condition& cond) {
	RECT field_rect = { field_x + field_width * 5 - 5, field_y + 5, field_x + 5, field_y + field_height * 5 - 5 };
	FillRect(hdc, &field_rect, CreateSolidBrush(cond.BG_color));
	for (size_t i = 0; i < 4; i++) {
		paint_icon(field_x + difficulties_dist, field_y + difficulties_dist + (icons[DIFFICULTY][HEIGHT] + difficulties_dist) * i,
			icons[DIFFICULTY][WIDTH], icons[DIFFICULTY][HEIGHT], difficulty_file_names[i][cond.theme_is_dark]);
		RECT text_rect = { 
			field_x + difficulties_dist * 2 + icons[DIFFICULTY][WIDTH],
			field_y + difficulties_dist + (icons[DIFFICULTY][HEIGHT] + difficulties_dist) * i, 
			field_x + difficulties_dist * 2 + icons[DIFFICULTY][WIDTH] + dificulties_text_width, 
			field_y + (icons[DIFFICULTY][HEIGHT] + difficulties_dist) * (i + 1) 
		};
		paint_text(text_rect, 40, 15, cond.text_color, difficulties_names[i].c_str());
	}
}

void WinApi_painter::paint_tools_field(Condition& cond) {
	RECT field_rect = { field_x + 15, field_y + 15, field_x + 15 + tools_text_width, field_y + 15 + tools_text_height };
	paint_text(field_rect, 40, 15, cond.text_color, tools_text.c_str());
}

void WinApi_painter::paint_help_field(Condition& cond) {
	RECT field_rect = { field_x + 15, field_y + 15, field_x + field_width * 5 - 5, field_y + field_height * 5 - 5 };
	paint_text(field_rect, 24, 9, cond.text_color, help_text.c_str());
}

void WinApi_painter::paint_player(Condition& cond) {
	RECT old_rect = { field_x + (cond.pl.last_x() - 1) * 5, field_y + (cond.pl.last_y() - 1) * 5,
		field_x + (cond.pl.last_x() + 2) * 5, field_y + (cond.pl.last_y() + 2) * 5 };
	FillRect(hdc, &old_rect, CreateSolidBrush(cond.field_color));
	paint_icon(field_x + (cond.pl.x() - 1) * 5, field_y + (cond.pl.y() - 1) * 5, 15, 15, cond.Textures[TEXTURE_PLAYER]);
}

void WinApi_painter::paint_enemy(Condition& cond, int num) {
	Enemy& en = cond.enemies[num];
	RECT old_rect = { field_x + (en.last_x() - 1) * 5, field_y + (en.last_y() - 1) * 5,
		field_x + (en.last_x() + 2) * 5, field_y + (en.last_y() + 2) * 5 };
	FillRect(hdc, &old_rect, CreateSolidBrush(cond.field_color));
	paint_icon(field_x + (en.x() - 1) * 5, field_y + (en.y() - 1) * 5, 15, 15, cond.Textures[TEXTURE_ENEMY]);
	if (en.last_x() != en.x()) {
		int x = en.last_x() + (en.last_x() - en.x());
		for (int y = en.y() - 1; y <= en.y() + 1; y++) {
			auto iter = cond.particles_map.find({ x, y });
			if (iter != cond.particles_map.end()) {
				paint_icon(field_x + x * 5, field_y + y * 5, 5, 5, particles_textures_file_names[iter->second][cond.theme_is_dark]);
			}
		}
	}
	else if (en.last_y() != en.y()) {
		int y = en.last_y() + (en.last_y() - en.y());
		for (int x = en.x() - 1; x <= en.x() + 1; x++) {
			auto iter = cond.particles_map.find({ x, y });
			if (iter != cond.particles_map.end()) {
				paint_icon(field_x + x * 5, field_y + y * 5, 5, 5, particles_textures_file_names[iter->second][cond.theme_is_dark]);
			}
		}
	}
}

void WinApi_painter::paint_particles(Condition& cond) {
	while (cond.deleting_particles.size() > 0) {
		coords& co = cond.deleting_particles.front();
		RECT rect = { field_x + co.x * 5, field_y + co.y * 5, field_x + (co.x + 1) * 5, field_y + (co.y + 1) * 5 };
		FillRect(hdc, &rect, CreateSolidBrush(cond.field_color));
		cond.deleting_particles.pop_front();
	}
	for (const std::pair<coords, int>& p : cond.particles_map) {
		paint_icon(field_x + p.first.x * 5, field_y + p.first.y * 5, 5, 5, particles_textures_file_names[p.second][cond.theme_is_dark]);
	}
}

void WinApi_painter::paint_game_elems(Condition& cond) {
	if (cond.change_game_timer) {
		paint_timer(cond, icons[GAME_TIMER][X_coord], icons[GAME_TIMER][Y_coord], cond.game_timer_value);
		cond.change_game_timer = false;
	}
	if (cond.change_fuel_timer) {
		paint_timer(cond, icons[FUEL_TIMER][X_coord], icons[FUEL_TIMER][Y_coord], cond.fuel_timer_value);
		cond.change_fuel_timer = false;
	}
	if (cond.change_score) {
		paint_score(cond, icons[SCORE_COUNTER][X_coord], icons[SCORE_COUNTER][Y_coord], cond.score);
		cond.change_score = false;
	}
	paint_particles(cond);
	if (cond.change_player_pos) {
		paint_player(cond);
		cond.change_player_pos = false;
	}
	for (size_t i = 0; i < 3; i++) {
		if (cond.change_enemy_pos[i]) {
			paint_enemy(cond, i);
			cond.change_enemy_pos[i] = false;
		}
	}
}

void WinApi_painter::paint_all(Condition& cond) {
	RECT global_rect = { cond.window_width, 0, 0, cond.window_height };
	FillRect(hdc, &global_rect, CreateSolidBrush(cond.BG_color));
	for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
		cond.pressed_button = button_id;
		paint_button(cond);
	}
	paint_difficulty(cond);
	paint_timer(cond, icons[FUEL_TIMER][X_coord], icons[FUEL_TIMER][Y_coord], cond.fuel_timer_value);
	paint_score(cond, icons[SCORE_COUNTER][X_coord], icons[SCORE_COUNTER][Y_coord], 0);
	paint_timer(cond, icons[GAME_TIMER][X_coord], icons[GAME_TIMER][Y_coord], cond.game_timer_value);
	paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
	paint_stars(cond);
	paint_field(cond);
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}