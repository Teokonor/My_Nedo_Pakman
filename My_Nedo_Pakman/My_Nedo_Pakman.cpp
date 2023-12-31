#include "Clicks.h"
#include "Painting.h"
#include <windowsx.h>

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

Condition cond;
WinApi_painter painter;

//���� ������� ��� ����� ��� ����:            MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	cond.window_class = { 0 };
	InitWndClass(cond.window_class, (HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", Procedure);
	if (!RegisterClassW(&cond.window_class)) {
		return -1;
	}
	cond.hWnd = CreateWindowExW(0, L"MainWndClass", L"My Nedo Pakman", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		window_start_x, window_start_y, window_start_width , window_start_height, NULL, NULL, NULL, NULL);

	painter.init_hWnd(cond.hWnd);
	
	MSG main_msg;
	while (cond.active) {
		cond.process_game();
		GetMessageW(&main_msg, NULL, NULL, NULL);
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
		cond.stop_game();
		cond.save_condition("save_condition.txt");
		cond.active = false;
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		left_button_down(cond, GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case WM_LBUTTONUP:
		left_button_up(cond, GET_X_LPARAM(lp), GET_Y_LPARAM(lp));
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case WM_KEYDOWN:
		keydown(cond, wp);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		painter.init_hdc(ps);
		painter.paint(cond);
		EndPaint(hWnd, &ps);
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