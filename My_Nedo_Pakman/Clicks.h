#pragma once
#include "Condition.h"

void left_button_down(Condition& cond, int x, int y);

void left_button_up(Condition& cond, int x, int y);

void change_status_by_button_click(Condition& cond);

void field_click(Condition& cond, int x, int y);

void choosing_map(Condition& cond, int x, int y);

void choosing_difficulty(Condition& cond, int x, int y);