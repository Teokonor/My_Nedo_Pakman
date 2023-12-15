#include "Condition.h"
#include "Painting.h"

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

Condition cond;
WinApi_painter painter;

//Пока оставлю это здесь для себя:            MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASS main_wind = { 0 };
	InitWndClass(main_wind, (HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", Procedure);
	if (!RegisterClassW(&main_wind)) {
		return -1;
	}
	HWND hWnd = CreateWindowExW(0, L"MainWndClass", L"My Nedo Pakman", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		300, 100, 1005, 705, NULL, NULL, NULL, NULL);

	painter.init_hWnd(hWnd);
	
	MSG main_msg;
	while (GetMessage(&main_msg, NULL, NULL, NULL)) {
		TranslateMessage(&main_msg);
		DispatchMessageW(&main_msg);
	}

	return 0;
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
		painter.paint_button();
		break;
	}
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}




void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	wnd.hIcon = icon;
	wnd.hCursor = cursor;
	wnd.hInstance = hInst;
	wnd.lpszClassName = name;
	wnd.hbrBackground = CreateSolidBrush(cond.BG_color);
	wnd.lpfnWndProc = procedure;
}