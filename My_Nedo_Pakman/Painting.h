#pragma once
#include <Windows.h>

class Painter {
public:
	virtual void paint_button() = 0;
	virtual void paint_field() = 0;
	virtual void paint_all() = 0;
	virtual void paint_autentification_page() = 0;
};

class WinApi_painter : public Painter {
	HWND hWnd = NULL;
public:
	void init_hWnd(HWND hwnd);
	void paint_button();
	void paint_field();
	void paint_all();
	void paint_autentification_page();
};