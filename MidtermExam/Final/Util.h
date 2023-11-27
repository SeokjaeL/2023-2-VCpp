#pragma once
#include <windows.h>

void SetMinMaxWindowSizes(HWND hWnd, MINMAXINFO* minMaxInfo, int minWidth, int minHeight);

void UpdateCursor(HWND hwnd, const RECT& drawing_area);