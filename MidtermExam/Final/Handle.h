#pragma once
#include <Windows.h>

void HandleMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseLButtonPressed, BOOL& isMouseRButtonPressed, POINT& startPoint, POINT& endPoint, RECT& Box, RECT& Circle, POINT& m_startPoint, POINT& m_endPoint, POINT& startPointSaved, POINT& endPointSaved, POINT& distance);

void HandleLeftButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, POINT& startPoint, POINT& endPoint, BOOL& isMouseLButtonPressed, int& Shape, const RECT& drawing_area);

void HandleRightButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseRButtonPressed, POINT& startPointSaved, POINT& endPointSaved, POINT& endPoint, POINT& m_startPoint, RECT& Box, RECT& Circle);
