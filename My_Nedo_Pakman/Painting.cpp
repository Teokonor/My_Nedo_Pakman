#include "Painting.h"

void WinApi_painter::init_hWnd(HWND hwnd) {
	hWnd = hwnd;
}

void WinApi_painter::paint_button() {
	

	HDC hDC, hCompatibleDC;
	PAINTSTRUCT PaintStruct;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	hDC = BeginPaint(hWnd, &PaintStruct);
	hBitmap = LoadImage(NULL, L"button_maps_lite_up.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObjectW(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	StretchBlt(hDC, 20, 20, 60, 60, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
	EndPaint(hWnd, &PaintStruct);
}

void WinApi_painter::paint_field() {

}

void WinApi_painter::paint_all() {

}

void WinApi_painter::paint_autentification_page() {

}