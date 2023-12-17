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
	HFONT my_font = CreateFontA(40, 15, 0, 0, 551, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_DONTCARE, "MyFont");
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, cond.text_color);
	SelectObject(hdc, my_font);
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
		DrawTextW(hdc, difficulties_names[i].c_str(), -1, &text_rect, 0);
	}

}

void WinApi_painter::paint_tools_field(Condition& cond) {
	HFONT my_font = CreateFontA(40, 15, 0, 0, 551, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_DONTCARE, "MyFont");
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, cond.text_color);
	SelectObject(hdc, my_font);
	RECT field_rect = { field_x + 5, field_y + 5, field_x + 5 + tools_text_width, field_y + 5 + tools_text_height };
	DrawTextW(hdc, tools_text.c_str(), -1, &field_rect, 0);
}

void WinApi_painter::paint_help_field(Condition& cond) {
	/*HFONT my_font = CreateFontA(40, 15, 0, 0, FW_MEDIUM, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DECORATIVE, "MyFont");*/
	HFONT my_font = CreateFontA(24, 9, 0, 0, 551, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_DONTCARE, "MyFont");
	RECT field_rect = { field_x + 5, field_y + 5, field_x + field_width * 5 - 5, field_y + field_height * 5 - 5 };
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, cond.text_color);
	SelectObject(hdc, my_font);
	DrawTextW(hdc, help_text.c_str(), -1, &field_rect, 0);
}

void WinApi_painter::paint_all(Condition& cond) {
	RECT global_rect = { cond.window_width, 0, 0, cond.window_height };
	FillRect(hdc, &global_rect, CreateSolidBrush(cond.BG_color));
	for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
		cond.pressed_button = button_id;
		paint_button(cond);
	}
	paint_difficulty(cond);
	paint_field(cond);
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}