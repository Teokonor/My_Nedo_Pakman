#pragma once
#include "Condition.h"
#include <Windows.h>

class Painter {
public:
	void paint(Condition& cond);
	virtual void paint_button(Condition& cond) = 0;
	virtual void paint_field(Condition& cond) = 0;
	virtual void paint_playing_field(Condition& cond) = 0;
	virtual void paint_maps_field(Condition& cond) = 0;
	virtual void paint_difficulties_field(Condition& cond) = 0;
	virtual void paint_tools_field(Condition& cond) = 0;
	virtual void paint_help_field(Condition& cond) = 0;
	virtual void paint_all(Condition& cond) = 0;
	virtual void paint_autentification_page(Condition& cond) = 0;
};

class WinApi_painter : public Painter {
	HWND hWnd = NULL;
	HDC hdc = NULL;
	void paint_walls(Condition& cond, int thickness, int x0, int y0);
public:
	void init_hWnd(HWND hwnd) {
		hWnd = hwnd;
	}
	void init_hdc(PAINTSTRUCT& ps_) {
		hdc = ps_.hdc;
	}
	void paint_button(Condition& cond);
	void paint_field(Condition& cond);
	void paint_playing_field(Condition& cond);
	void paint_maps_field(Condition& cond);
	void paint_difficulties_field(Condition& cond);
	void paint_tools_field(Condition& cond);
	void paint_help_field(Condition& cond);
	void paint_all(Condition& cond);
	void paint_autentification_page(Condition& cond);
};