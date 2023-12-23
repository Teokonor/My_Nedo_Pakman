#pragma once
#include "Condition.h"
#include <Windows.h>

class Painter {
public:
	void paint(Condition& cond);

	virtual void paint_button(Condition& cond) = 0;
	virtual void paint_difficulty(Condition& cond) = 0;
	virtual void paint_timer(Condition& cond, int x, int y, int seconds) = 0;
	virtual void paint_score(Condition& cond, int x, int y, int score_) = 0;
	virtual void paint_stars(Condition& cond) = 0;

	virtual void paint_field(Condition& cond) = 0;
	virtual void paint_playing_field(Condition& cond) = 0;
	virtual void paint_maps_field(Condition& cond) = 0;
	virtual void paint_difficulties_field(Condition& cond) = 0;
	virtual void paint_tools_field(Condition& cond) = 0;
	virtual void paint_help_field(Condition& cond) = 0;

	virtual void paint_player(Condition& cond) = 0;
	virtual void paint_enemy(Condition& cond, int num) = 0;
	virtual void paint_game_elems(Condition& cond) = 0;

	virtual void paint_all(Condition& cond) = 0;
	virtual void paint_autentification_page(Condition& cond) = 0;
};

class WinApi_painter : public Painter {
	HWND hWnd = NULL;
	HDC hdc = NULL;
	void paint_walls(Condition& cond, int thickness, int x0, int y0);
	void paint_icon(int x, int y, int width, int height, std::string file_name);
	void paint_text(RECT rect, int letter_height, int letter_width, COLORREF color, LPCWSTR text);
public:
	void init_hWnd(HWND hwnd) {
		hWnd = hwnd;
	}
	void init_hdc(PAINTSTRUCT& ps_) {
		hdc = ps_.hdc;
	}

	void paint_button(Condition& cond);
	void paint_difficulty(Condition& cond);
	void paint_timer(Condition& cond, int x, int y, int seconds);
	void paint_score(Condition& cond, int x, int y, int score_);
	void paint_stars(Condition& cond);
	void paint_player(Condition& cond);
	void paint_enemy(Condition& cond, int num);
	void paint_game_elems(Condition& cond);

	void paint_field(Condition& cond);
	void paint_playing_field(Condition& cond);
	void paint_maps_field(Condition& cond);
	void paint_difficulties_field(Condition& cond);
	void paint_tools_field(Condition& cond);
	void paint_help_field(Condition& cond);

	void paint_all(Condition& cond);
	void paint_autentification_page(Condition& cond);
};