#include "Procedure.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASS main_wind = { 0 };
	InitWndClass(main_wind, (HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", Procedure);
	if (!RegisterClassW(&main_wind)) {
		return -1;
	}
	CreateWindowExW(0, L"MainWndClass", L"My Nedo Pakman", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 100, 1005, 705, NULL, NULL, NULL, NULL);
	
	MSG main_msg;
	while (GetMessage(&main_msg, NULL, NULL, NULL)) {
		TranslateMessage(&main_msg);
		DispatchMessage(&main_msg);
	}

	return 0;
}