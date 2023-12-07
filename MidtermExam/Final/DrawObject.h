#pragma once
#include <Windows.h>

void DrawBox(HDC hdc, RECT& Box);

void DrawCircle(HDC hdc, RECT& Circle);

void DrawBonobono(HWND hwnd, HDC hdc, int blink);

void DrawRyan(HWND hwnd, HDC hdc, POINT startPoint, POINT endPoint);

void DrawCube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint);
