#include "Procedure.h"

Condition cond;

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	wnd.hIcon = icon;
	wnd.hCursor = cursor;
	wnd.hInstance = hInst;
	wnd.lpszClassName = name;
	//wnd.hbrBackground = BGColor;
	wnd.hbrBackground = CreateSolidBrush(cond.BG_color);
	wnd.lpfnWndProc = procedure;
}

LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rectangle = { 500, 10, 10, 200 };
		HBRUSH hbr = CreateSolidBrush(RGB(200, 200, 10));
		FillRect(ps.hdc, &rectangle, hbr);

		EndPaint(hWnd, &ps);
		break;
	}
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}