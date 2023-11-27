#include "CreateInterface.h"

void CreateButtons(HWND hwnd, HINSTANCE hInstance) {
	// ù ��° ��ư
	CreateWindow(
		TEXT("button"), // ��ư Ŭ����
		TEXT("Box"), // ��ư �ؽ�Ʈ
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
		8 + 8, // x ��ġ: �ڽ� ���� ���� + ���� ����
		8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
		140, // ��ư �ʺ�
		64, // ��ư ����
		hwnd, // �θ� ������
		(HMENU)1, // ��ư ID
		hInstance,
		NULL);

	// �� ��° ��ư
	CreateWindow(
		TEXT("button"), // ��ư Ŭ����
		TEXT("Circle"), // ��ư �ؽ�Ʈ
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
		8 + 8 + 140 + 16, // x ��ġ: �ڽ� ���� ���� + ���� ����
		8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
		140, // ��ư �ʺ�
		64, // ��ư ����
		hwnd, // �θ� ������
		(HMENU)2, // ��ư ID
		hInstance,
		NULL);

	// �� ��° ��ư
	CreateWindow(
		TEXT("button"), // ��ư Ŭ����
		TEXT("Bonobono"), // ��ư �ؽ�Ʈ
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
		8 + 8 + (140 + 16) * 2, // x ��ġ: �ڽ� ���� ���� + ���� ����
		8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
		140, // ��ư �ʺ�
		64, // ��ư ����
		hwnd, // �θ� ������
		(HMENU)3, // ��ư ID
		hInstance,
		NULL);

	// �� ��° ��ư
	CreateWindow(
		TEXT("button"), // ��ư Ŭ����
		TEXT("Ryan"), // ��ư �ؽ�Ʈ
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
		8 + 8 + (140 + 16) * 3, // x ��ġ: �ڽ� ���� ���� + ���� ����
		8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
		140, // ��ư �ʺ�
		64, // ��ư ����
		hwnd, // �θ� ������
		(HMENU)4, // ��ư ID
		hInstance,
		NULL);

	// �ټ� ��° ��ư
	CreateWindow(
		TEXT("button"), // ��ư Ŭ����
		TEXT("Cube"), // ��ư �ؽ�Ʈ
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
		8 + 8 + (140 + 16) * 4, // x ��ġ: �ڽ� ���� ���� + ���� ����
		8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
		140, // ��ư �ʺ�
		64, // ��ư ����
		hwnd, // �θ� ������
		(HMENU)5, // ��ư ID
		hInstance,
		NULL);
}

void DrawInterface(HWND hwnd, HDC hdc, RECT& drawing_area) {
	// ������ �귯�� ����
	HBRUSH hBrushBackground = CreateSolidBrush(RGB(255, 240, 200));
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(hdc, &rect, hBrushBackground);

	// �簢�� �ڽ� �׸���
	HBRUSH hBrushBox = CreateSolidBrush(RGB(255, 240, 200));  // �ڽ��� ����
	HPEN hPenBox = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));  // �׵θ��� ����: ������
	SelectObject(hdc, hPenBox);
	SelectObject(hdc, hBrushBox);
	RECT rectBox = { 8, 8, 800 - 8, 480 - 8 };  // 8px�� �������� �ڽ� ����
	Rectangle(hdc, rectBox.left, rectBox.top, rectBox.right, rectBox.bottom);

	// ����� ������ ũ��� ��ġ�� �����մϴ�.
	// ��ư�� ����(64)�� ����(16)�� ����Ͽ� top�� �����մϴ�.
	// �׵θ��� �ڽ� �������� 8px�� ������ ������ �ֽ��ϴ�.
	drawing_area.left = rectBox.left + 8;
	drawing_area.top = rectBox.top + 64 + 16;  // ��ư�� bottom + ��ư�� �ڽ� ������ ����
	drawing_area.right = rectBox.right - 8;
	drawing_area.bottom = rectBox.bottom - 8;

	// ����� ������ ������ ������� �����մϴ�.
	HBRUSH hBrushDrawing = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &drawing_area, hBrushDrawing);

	// ����� ������ �׵θ��� �������� �׸��ϴ�.
	HPEN hPenDrawing = CreatePen(PS_SOLID, 1, RGB(0, 0, 128));
	SelectObject(hdc, hPenDrawing);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���� ä��� ����

	// �簢�� �׵θ� �׸���
	Rectangle(hdc, drawing_area.left, drawing_area.top, drawing_area.right, drawing_area.bottom);

	// ���ҽ� ����
	DeleteObject(hBrushDrawing);
	DeleteObject(hPenDrawing);

	// ���ҽ� ����
	DeleteObject(hBrushBackground);
	DeleteObject(hBrushBox);
	DeleteObject(hPenBox);
}