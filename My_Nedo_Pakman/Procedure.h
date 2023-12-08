#pragma once
#include <Windows.h>

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);
LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
