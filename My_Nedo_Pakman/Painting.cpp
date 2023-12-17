#include "Painting.h"

LPCWSTR stowchar(std::string str) {
	std::wstring wstr = std::wstring(str.begin(), str.end());
	return wstr.c_str();
}

void Painter::paint(Condition& cond) {
	switch (cond.paint)
	{
	case PAINT_BUTTON:
	{
		int pressed_button = cond.pressed_button;
		paint_button(cond);
		cond.pressed_button = BUTTON_PLAY;
		paint_button(cond);
		cond.pressed_button = pressed_button;
		break;
	}
	case PAINT_FIELD:
		paint_field(cond);
		break;
	case PAINT_BUTTON_AND_FIELD:
	{
		int pressed_button = cond.pressed_button;
		paint_button(cond);
		cond.pressed_button = BUTTON_PLAY;
		paint_button(cond);
		cond.pressed_button = pressed_button;
		paint_field(cond);
		break;
	}
	case PAINT_ALL:
		paint_all(cond);
		break;
	default:
		break;
	}
	cond.paint = NOT_PAINT;
}

void WinApi_painter::paint_button(Condition& cond) {
	HDC hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	LPCWSTR file_name = stowchar(cond.Textures[cond.pressed_button]);
	hBitmap = LoadImageW(NULL, file_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObjectW(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hdc);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	StretchBlt(hdc, buttons_coord_x[cond.pressed_button], buttons_coord_y, button_width, button_height,
		hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}

void WinApi_painter::paint_field(Condition& cond) {
	RECT field_rect = { field_x + playing_field_width * 5, field_y, field_x, field_y + playing_field_height * 5 };
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
	default:
		break;
	}
}

void WinApi_painter::paint_walls(Condition& cond, int thickness, int x0, int y0) {
	HBRUSH brush = CreateSolidBrush(cond.walls_color);
	for (size_t y = 0; y < playing_field_height; y++) {
		for (size_t x = 0; x < playing_field_width; x++) {
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
	char file_name[] = "mapN.txt";
	for (size_t i = 0; i < maps_quantity; i++) {
		file_name[3] = (char)(i + 48);
		cond.walls_map.read_walls(file_name);
		paint_walls(cond, 2, field_x + map0_x + (i % 2) * (maps_dist_x + playing_field_width * 2), 
			field_y + map0_y + (i / 2) * (maps_dist_y + playing_field_height * 2));
	}
	cond.walls_map = *old_map;
	delete(old_map);
}

void WinApi_painter::paint_difficulties_field(Condition& cond) {

}

void WinApi_painter::paint_tools_field(Condition& cond) {

}

void WinApi_painter::paint_help_field(Condition& cond) {

}

void WinApi_painter::paint_all(Condition& cond) {
	paint_field(cond);
	for (int button_id = BUTTON_PLAY; button_id <= BUTTON_HELP; button_id++) {
		cond.pressed_button = button_id;
		paint_button(cond);
	}
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}