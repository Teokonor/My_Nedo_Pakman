#pragma once
#include "Condition.h"
#include <Windows.h>

class Painter {
public:
	virtual void paint_button(Condition& cond) = 0;
	virtual void paint_field(Condition& cond) = 0;
	virtual void paint_all(Condition& cond) = 0;
	virtual void paint_autentification_page(Condition& cond) = 0;
};

class WinApi_painter : public Painter {
	HWND hWnd = NULL;
	PAINTSTRUCT ps;
public:
	void init_hWnd(HWND hwnd);
	void paint_button(Condition& cond);
	void paint_field(Condition& cond);
	void paint_all(Condition& cond);
	void paint_autentification_page(Condition& cond);
};