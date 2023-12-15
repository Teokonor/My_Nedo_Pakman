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
	StretchBlt(hdc, 20, 20, 60, 60, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}

void WinApi_painter::paint_field(Condition& cond) {
	HBRUSH brush = CreateSolidBrush(cond.walls_color);
	RECT rectangle = { field_x + playing_field_width * 5, field_y, field_x, field_y + playing_field_height * 5 };
	FillRect(hdc, &rectangle, CreateSolidBrush(cond.field_color));
	for (size_t y = 0; y < playing_field_height; y++) {
		for (size_t x = 0; x < playing_field_width; x++) {
			if (cond.walls_map.wall_at_point(x, y)) {
				RECT rect = { field_x + (x + 1) * 5, field_y + y * 5, field_x + x * 5, field_y + (y + 1) * 5 };
				FillRect(hdc, &rect, brush);
			}
		}
	}
}

void WinApi_painter::paint_all(Condition& cond) {
	paint_field(cond);
	paint_button(cond);
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}