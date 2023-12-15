#pragma once
#include "Condition.h"
#include <Windows.h>

class Painter {
public:
	virtual void paint(Condition& cond) = 0;
	virtual void paint_button(Condition& cond) = 0;
	virtual void paint_field(Condition& cond) = 0;
	virtual void paint_all(Condition& cond) = 0;
	virtual void paint_autentification_page(Condition& cond) = 0;
};

class WinApi_painter : public Painter {
	HWND hWnd = NULL;
	HDC hdc;
public:
	void init_hWnd(HWND hwnd) {
		hWnd = hwnd;
	}
	void init_hdc(PAINTSTRUCT& ps_) {
		hdc = ps_.hdc;
	}
	void paint(Condition& cond);
	void paint_button(Condition& cond);
	void paint_field(Condition& cond);
	void paint_all(Condition& cond);
	void paint_autentification_page(Condition& cond);
};