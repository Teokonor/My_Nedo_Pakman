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

void WinApi_painter::paint_all(Condition& cond) {
	RECT global_rect = { cond.window_width, 0, 0, cond.window_height };
	FillRect(hdc, &global_rect, CreateSolidBrush(cond.BG_color));
	for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
		cond.pressed_button = button_id;
		paint_button(cond);
	}
	paint_difficulty(cond);
	paint_timer(cond, icons[FUEL_TIMER][X_coord], icons[FUEL_TIMER][Y_coord], 20);
	paint_timer(cond, icons[GAME_TIMER][X_coord], icons[GAME_TIMER][Y_coord], 120);
	paint_score(cond, icons[SCORE_COUNTER][X_coord], icons[SCORE_COUNTER][Y_coord], 0);
	paint_score(cond, icons[SCORE_RECORD][X_coord], icons[SCORE_RECORD][Y_coord], cond.scores[cond.map][cond.difficulty]);
	paint_field(cond);
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}