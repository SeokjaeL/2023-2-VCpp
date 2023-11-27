#pragma once
#include <Windows.h>

void DrawBox(HDC hdc, RECT& Box);

void DrawCircle(HDC hdc, RECT& Circle);

void DrawBonobono(HWND hwnd, HDC hdc, int blink);

void DrawRyan(HWND hwnd, HDC hdc, int left, int top, int right, int bottom);


