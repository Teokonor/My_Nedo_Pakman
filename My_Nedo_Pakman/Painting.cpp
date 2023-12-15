#include "Painting.h"

void WinApi_painter::init_hWnd(HWND hwnd) {
	hWnd = hwnd;
}

void WinApi_painter::paint_button(Condition& cond) {
	HDC hDC, hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	hDC = ps.hdc;
	hBitmap = LoadImage(NULL, L"button_maps_lite_up.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObjectW(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	StretchBlt(hDC, 20, 20, 60, 60, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}

void WinApi_painter::paint_field(Condition& cond) {
	HBRUSH brush = CreateSolidBrush(cond.walls_color);
	HDC hDC = ps.hdc;
	for (size_t y = 0; y < playing_field_height; y++) {
		for (size_t x = 0; x < playing_field_width; x++) {
			if (cond.walls_map.wall_at_point(x, y)) {
				//MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);
				RECT rect = { field_x + (x + 1) * 5, field_y + y * 5, field_x + x * 5, field_y + (y + 1) * 5 };
				FillRect(hDC, &rect, brush);
			}
		}
	}
}

void WinApi_painter::paint_all(Condition& cond) {
	BeginPaint(hWnd, &ps);
	paint_field(cond);
	paint_button(cond);
	EndPaint(hWnd, &ps);
}

void WinApi_painter::paint_autentification_page(Condition& cond) {

}