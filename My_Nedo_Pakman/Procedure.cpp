#include "Procedure.h"

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	wnd.hIcon = icon;
	wnd.hCursor = cursor;
	wnd.hInstance = hInst;
	wnd.lpszClassName = name;
	wnd.hbrBackground = BGColor;
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
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}