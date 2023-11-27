#include "CreateInterface.h"

void CreateButtons(HWND hwnd, HINSTANCE hInstance) {
	// 첫 번째 버튼
	CreateWindow(
		TEXT("button"), // 버튼 클래스
		TEXT("Box"), // 버튼 텍스트
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
		8 + 8, // x 위치: 박스 왼쪽 마진 + 내부 마진
		8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
		140, // 버튼 너비
		64, // 버튼 높이
		hwnd, // 부모 윈도우
		(HMENU)1, // 버튼 ID
		hInstance,
		NULL);

	// 두 번째 버튼
	CreateWindow(
		TEXT("button"), // 버튼 클래스
		TEXT("Circle"), // 버튼 텍스트
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
		8 + 8 + 140 + 16, // x 위치: 박스 왼쪽 마진 + 내부 마진
		8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
		140, // 버튼 너비
		64, // 버튼 높이
		hwnd, // 부모 윈도우
		(HMENU)2, // 버튼 ID
		hInstance,
		NULL);

	// 세 번째 버튼
	CreateWindow(
		TEXT("button"), // 버튼 클래스
		TEXT("Bonobono"), // 버튼 텍스트
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
		8 + 8 + (140 + 16) * 2, // x 위치: 박스 왼쪽 마진 + 내부 마진
		8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
		140, // 버튼 너비
		64, // 버튼 높이
		hwnd, // 부모 윈도우
		(HMENU)3, // 버튼 ID
		hInstance,
		NULL);

	// 네 번째 버튼
	CreateWindow(
		TEXT("button"), // 버튼 클래스
		TEXT("Ryan"), // 버튼 텍스트
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
		8 + 8 + (140 + 16) * 3, // x 위치: 박스 왼쪽 마진 + 내부 마진
		8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
		140, // 버튼 너비
		64, // 버튼 높이
		hwnd, // 부모 윈도우
		(HMENU)4, // 버튼 ID
		hInstance,
		NULL);

	// 다섯 번째 버튼
	CreateWindow(
		TEXT("button"), // 버튼 클래스
		TEXT("Cube"), // 버튼 텍스트
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
		8 + 8 + (140 + 16) * 4, // x 위치: 박스 왼쪽 마진 + 내부 마진
		8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
		140, // 버튼 너비
		64, // 버튼 높이
		hwnd, // 부모 윈도우
		(HMENU)5, // 버튼 ID
		hInstance,
		NULL);
}

void DrawInterface(HWND hwnd, HDC hdc, RECT& drawing_area) {
	// 배경색의 브러시 생성
	HBRUSH hBrushBackground = CreateSolidBrush(RGB(255, 240, 200));
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(hdc, &rect, hBrushBackground);

	// 사각형 박스 그리기
	HBRUSH hBrushBox = CreateSolidBrush(RGB(255, 240, 200));  // 박스의 배경색
	HPEN hPenBox = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));  // 테두리의 색상: 검정색
	SelectObject(hdc, hPenBox);
	SelectObject(hdc, hBrushBox);
	RECT rectBox = { 8, 8, 800 - 8, 480 - 8 };  // 8px의 마진으로 박스 설정
	Rectangle(hdc, rectBox.left, rectBox.top, rectBox.right, rectBox.bottom);

	// 드로잉 영역의 크기와 위치를 설정합니다.
	// 버튼의 높이(64)와 마진(16)을 고려하여 top을 설정합니다.
	// 테두리는 박스 안쪽으로 8px의 여백을 가지고 있습니다.
	drawing_area.left = rectBox.left + 8;
	drawing_area.top = rectBox.top + 64 + 16;  // 버튼의 bottom + 버튼과 박스 사이의 마진
	drawing_area.right = rectBox.right - 8;
	drawing_area.bottom = rectBox.bottom - 8;

	// 드로잉 영역의 배경색을 흰색으로 설정합니다.
	HBRUSH hBrushDrawing = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &drawing_area, hBrushDrawing);

	// 드로잉 영역의 테두리를 남색으로 그립니다.
	HPEN hPenDrawing = CreatePen(PS_SOLID, 1, RGB(0, 0, 128));
	SelectObject(hdc, hPenDrawing);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // 내부 채우기 없음

	// 사각형 테두리 그리기
	Rectangle(hdc, drawing_area.left, drawing_area.top, drawing_area.right, drawing_area.bottom);

	// 리소스 해제
	DeleteObject(hBrushDrawing);
	DeleteObject(hPenDrawing);

	// 리소스 해제
	DeleteObject(hBrushBackground);
	DeleteObject(hBrushBox);
	DeleteObject(hPenBox);
}