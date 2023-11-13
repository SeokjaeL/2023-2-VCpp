#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// ��ư�� ���� ������ ��ũ�� ���
#define S_Box 1
#define S_Circle 2
#define S_Bonobono 3
#define S_Ryan 4
#define S_Cube 5

#include <windows.h>
#include "yuhanCG.h"

// ��� ��ư�� ���� ���� ���� ����
HWND hButton1;
HWND hButton2;
HWND hButton3;
HWND hButton4;
HWND hButton5;

// ��ǥ���� ������ ���� ���� ����
// ���۰� �� ��ǥ�� ��ǥ�� ���, ���콺 �̵� ��ǥ, �Ÿ��� ��ǥ, ������ ���� ��ǥ, ����� ������ ���� ��ǥ
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT m_startPoint = { 0 };
POINT m_endPoint = { 0 };
POINT distance = { 0 };
POINT startPointSaved = { 0 };
POINT endPointSaved = { 0 };
RECT Box = { 0 };
RECT Circle = { 0 };
RECT drawing_area = { 0 };

// ���� ��ư�� ������ ������ ������ ���� ���� ����
int Shape = 0;

// ���콺�� �����̽��� �Է»��� üũ ���� ���� ����
int isMouseLButtonPressed = FALSE;	// ���콺 ���� ��ư�� ���� �������� üũ
int isMouseRButtonPressed = FALSE;	// ���콺 ������ ��ư�� ���� �������� üũ
int isSpaceButtonPressed = FALSE;	// �����̽� ��ư�� ���� �������� üũ

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// â�� �ּ� �� �ִ� ũ�⿡ ���� ���� ����
	case WM_GETMINMAXINFO:
	{
		// MINMAXINFO ����ü �����͸� ���� ��, lParam(â�� ũ�� ���� ����)�� ����� ���� MINMAXINFO ����ü �����ͷ� ĳ������ ������ �ʱ�ȭ 
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;

		// ������ ���� ũ�� ����
		RECT rect = { 0, 0, 800, 480 };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		// MINMAXINFO ����ü ������� �����Ͽ� â�� �ּ� ũ��� �ִ� ũ�⸦ ����
		minMaxInfo->ptMinTrackSize.x = width; // �ּ� �ʺ�
		minMaxInfo->ptMinTrackSize.y = height; // �ּ� ����
		minMaxInfo->ptMaxTrackSize.x = width; // �ִ� �ʺ�
		minMaxInfo->ptMaxTrackSize.y = height; // �ִ� ����
	}
	break;

	// Ű�� ���� ������ ���
	case WM_KEYDOWN:
	{
		// ���࿡ �����̽�Ű�� ���� ���¶��
		if (wParam == VK_SPACE) {
			// üũ ������ ���� TRUE�� ����
			isSpaceButtonPressed = TRUE;

			// WM_PAINT �޽��� ȣ��
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// Ű�� ���� ���¶��
	case WM_KEYUP:
	{
		// ���࿡ �����̽�Ű�� ���� ���¶��
		if (wParam == VK_SPACE) {
			// üũ ������ ���� FALSE���� ����
			isSpaceButtonPressed = FALSE;

			// WM_PAINT �޽��� ȣ��
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// ��ư�� ���ȴٸ�
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam); // ��ư�� ID�� �����ɴϴ�.

		// ��ư�� ���̵� ���� ó��
		switch (wmId)
		{
			// Box ��ư�̶��
		case 1:
		{
			Shape = S_Box;								// ������ ������ Box�� ����
			SetFocus(hwnd);								// ��Ŀ���� ������ �ڵ鷯������ �̵�(��ư ��Ŀ�� ����)
			Box = { 0 };								// Box�� ��ǥ���� 0���� �ʱ�ȭ
			InvalidateRect(hwnd, &drawing_area, TRUE);	// ����� ������ �ʱ�ȭ
			break;
		}

		// Circle ��ư�̶��
		case 2:
		{
			Shape = S_Circle;							// ������ ������ Circle�� ����
			SetFocus(hwnd);								// ��Ŀ���� ������ �ڵ鷯������ �̵�(��ư ��Ŀ�� ����)
			Circle = { 0 };								// Circle�� ��ǥ���� 0���� �ʱ�ȭ
			InvalidateRect(hwnd, &drawing_area, TRUE);	// ����� ������ �ʱ�ȭ
			break;
		}

		// Bonobono ��ư�̶��
		case 3:
		{
			Shape = S_Bonobono;							// ������ ������ Bonobono�� ����
			SetFocus(hwnd);								// ��Ŀ���� ������ �ڵ鷯������ �̵�(��ư ��Ŀ�� ����)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// WM_PAINT �޽��� ȣ��
			break;
		}

		// Ryan ��ư�̶��
		case 4:
		{
			Shape = S_Ryan;								// ������ ������ Ryan���� ����
			SetFocus(hwnd);								// ��Ŀ���� ������ �ڵ鷯������ �̵�(��ư ��Ŀ�� ����)
			startPoint = { 0 };							// startPoint�� ��ǥ���� 0���� �ʱ�ȭ
			endPoint = { 0 };							// endPoint�� ��ǥ���� 0���� �ʱ�ȭ
			InvalidateRect(hwnd, &drawing_area, TRUE);	// ����� ������ �ʱ�ȭ
			break;
		}

		// Cube ��ư�̶��
		case 5:
		{
			Shape = S_Cube;								// ������ ������ Cube�� ����
			SetFocus(hwnd);								// ��Ŀ���� ������ �ڵ鷯������ �̵�(��ư ��Ŀ�� ����)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// ����� ������ �ʱ�ȭ
			break;
		}

		// �ش������ ���� ���
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		// ������ ������ Circle�̳� Box�ų� Ryan�̶��
		if (Shape == S_Circle || Shape == S_Box || Shape == S_Ryan) {
			// ��ǥ���� �����ͼ� ���� ��ǥ���� �Ҵ�(endPoint�� �ʱⰪ�� startPoint�� ����) 
			startPoint = { LOWORD(lParam), HIWORD(lParam) };
			endPoint = startPoint;

			// �������� ����� ���� �ȿ� �ִٸ�
			if (PtInRect(&drawing_area, startPoint)) {
				// üũ ������ ���� TRUE�� ����
				isMouseLButtonPressed = TRUE;
			}
		}
	}
	break;

	// ���콺 ���� ��ư�� �� ���
	case WM_LBUTTONUP:
	{
		// üũ ������ ���� FALSE���� ����
		isMouseLButtonPressed = FALSE;
	}
	break;

	// ���콺 ������ ��ư�� ���� ���
	case WM_RBUTTONDOWN:
	{
		// ������ ������ Circle�� ���
		if (Shape == S_Circle) {
			// ���� ��ǥ���� ���(endPoint�� �ʱⰪ�� startPointSaved�� ����) 
			startPointSaved = { LOWORD(lParam), HIWORD(lParam) };
			endPoint = startPointSaved;

			// �������� ����� ���� �ȿ� �ִٸ�
			if (PtInRect(&drawing_area, startPointSaved) && PtInRect(&Circle, startPointSaved)) {
				// üũ ������ ���� TRUE�� ����
				isMouseRButtonPressed = TRUE;
			}
		}

		// ������ ������ Box�� ���
		if (Shape == S_Box) {
			// ���콺 ������ ��ư�� ������ �� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� �̵��� ���۵� ��ǥ������ ����
			m_startPoint.x = LOWORD(lParam);
			m_startPoint.y = HIWORD(lParam);

			// ���콺 ������ ��ư�� ������ ������� �簢�� ���� �ȿ��� �����ٸ�
			if (PtInRect(&drawing_area, m_startPoint) && PtInRect(&Box, m_startPoint))
			{
				// üũ ������ ���� TRUE�� ����
				isMouseRButtonPressed = TRUE;

				// ���� �簢���� ��ǥ���� Saved ������ ����
				startPointSaved.x = Box.left;
				startPointSaved.y = Box.top;
				endPointSaved.x = Box.right;
				endPointSaved.y = Box.bottom;
			}
		}
	}
	break;

	// ���콺 ������ ��ư�� �� ���
	case WM_RBUTTONUP:
	{
		// üũ ������ ���� FALSE�� ����
		isMouseRButtonPressed = FALSE;
	}
	break;

	// ���콺�� �����̴� ���
	case WM_MOUSEMOVE:
	{
		// ������ ������ Circle�̰� ���콺 ���� ��ư�� ���� ���
		if (Shape == S_Circle && isMouseLButtonPressed) {
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			int radius = min(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y)); // �������� �� ���� �� ���� ������ ����

			int centerX = (startPoint.x + endPoint.x) / 2; // �߽��� x ��ǥ
			int centerY = (startPoint.y + endPoint.y) / 2; // �߽��� y ��ǥ

			Circle.left = centerX - radius;
			Circle.top = centerY - radius;
			Circle.right = centerX + radius;
			Circle.bottom = centerY + radius;

			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// ������ ������ Circle�̰� ���콺 ������ ��ư�� ���� ���
		if (Shape == S_Circle && isMouseRButtonPressed) {

			// ���� ���콺 ��ġ�� �����ɴϴ�.
			POINT currentPoint = { LOWORD(lParam), HIWORD(lParam) };

			// ���� endPoint ����
			endPointSaved = endPoint;

			// ���콺 �̵� �Ÿ� ���
			int deltaX = currentPoint.x - endPoint.x;

			if (abs(deltaX) >= 100) {
				// �̵� �Ÿ��� 100px �̻��̸� ũ�� ����
				int radius = (Circle.right - Circle.left) / 2;

				if (deltaX > 0) {
					// �������� �̵��� ���
					radius *= 2; // 2�� Ȯ��
				}
				else {
					// �������� �̵��� ���
					radius /= 2; // �������� ���
				}

				// ���� �߽��� �����ϸ鼭 ũ�⸦ ����
				int centerX = (Circle.left + Circle.right) / 2;
				int centerY = (Circle.top + Circle.bottom) / 2;

				Circle.left = centerX - radius;
				Circle.top = centerY - radius;
				Circle.right = centerX + radius;
				Circle.bottom = centerY + radius;

				// endPoint ������Ʈ
				endPoint = currentPoint;

				// ȭ���� �����Ͽ� ���� �׸��ϴ�.
				InvalidateRect(hwnd, &drawing_area, TRUE);
			}
		}

		// ������ ������ Box�̰� ���콺 ���� ��ư�� ���� ���
		if (Shape == S_Box && isMouseLButtonPressed) {
			// ���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� ������ ��ǥ������ ����
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			// �簢�� ��ǥ�� ����(�簢���� �ݴ�� �׸��� ��츦 ����Ͽ�)
			Box.left = min(startPoint.x, endPoint.x);
			Box.top = min(startPoint.y, endPoint.y);
			Box.right = max(startPoint.x, endPoint.x);
			Box.bottom = max(startPoint.y, endPoint.y);

			// ȭ���� �����Ͽ� �簢���� �׸��ϴ�.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// ������ ������ Box�̰� ���콺 ������ ��ư�� ���� ���
		if (Shape == S_Box && isMouseRButtonPressed) {
			// ���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� �̵��� ���� ��ǥ������ ����
			m_endPoint.x = LOWORD(lParam);
			m_endPoint.y = HIWORD(lParam);

			// �簢�� �̵��� ���� ��ǥ���� �簢�� �̵��� ���۵� ��ǥ���� ���� ���� ���콺�� �̵� �Ÿ��� ���
			distance.x = m_endPoint.x - m_startPoint.x;
			distance.y = m_endPoint.y - m_startPoint.y;

			// �簢���� ��ǥ���� ������ �����س��� ��ǥ���� ���콺�� �̵��Ÿ� ��ŭ�� ���� ��ǥ������ ����
			Box.left = startPointSaved.x + distance.x;
			Box.top = startPointSaved.y + distance.y;
			Box.right = endPointSaved.x + distance.x;
			Box.bottom = endPointSaved.y + distance.y;

			// ȭ���� �����Ͽ� �簢���� �׸��ϴ�.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// ������ ������ Ryan�̰� ���콺 ���� ��ư�� ���� ���
		if (Shape == S_Ryan && isMouseLButtonPressed) {
			// ���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� ������ ��ǥ������ ����
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			// ȭ���� �����Ͽ� Ryan�� �׸��ϴ�.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		// ����Ʈ ����ü ����� ������ �ڵ鷯 �޾ƿ���
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

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
		// ��ư�� ����(64)�� ����(16)�� �����Ͽ� top�� �����մϴ�.
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

		// ������ ������ Circle�̶��
		if (Shape == S_Circle) {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));									//	�귯�ø� �����ϰ� ������ ��ũ��(�ܻ�)���� ����
			SelectObject(hdc, hBrush);															//	�׸��⿡ ����� �귯�ø� ����
			Ellipse(hdc, Circle.left, Circle.top, Circle.right, Circle.bottom);	//	������ �簢���� ��ǥ���� �̿��Ͽ� �簢���� �׸�
			DeleteObject(hBrush);																//	������ �귯�ø� ����
		}

		// ������ ������ Box���
		if (Shape == S_Box) {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));									//	�귯�ø� �����ϰ� ������ ��ũ��(�ܻ�)���� ����
			SelectObject(hdc, hBrush);															//	�׸��⿡ ����� �귯�ø� ����
			Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);	//	������ �簢���� ��ǥ���� �̿��Ͽ� �簢���� �׸�
			DeleteObject(hBrush);																//	������ �귯�ø� ����
		}

		// ������ ������ Bonobono���
		if (Shape == S_Bonobono) {
			DrawBonobono(hwnd, hdc, isSpaceButtonPressed);
		}

		// ������ ������ Ryan�̶��
		if (Shape == S_Ryan) {
			DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}

		// ���ҽ� ����
		DeleteObject(hBrushDrawing);
		DeleteObject(hPenDrawing);

		// ���ҽ� ����
		DeleteObject(hBrushBackground);
		DeleteObject(hBrushBox);
		DeleteObject(hPenBox);

		EndPaint(hwnd, &ps);
	}
	break;

	// ��氪�� ����
	case WM_ERASEBKGND:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect((HDC)wParam, &rect, hBrush);
		DeleteObject(hBrush);  // �귯�� ���ҽ��� �����մϴ�.
		return 1;  // ����� �������� ��Ÿ���ϴ�.
	}
	break;

	// ��ư(������)�� ����
	case WM_CREATE:
	{
		// ù ��° ��ư
		hButton1 = CreateWindow(
			TEXT("button"), // ��ư Ŭ����
			TEXT("Box"), // ��ư �ؽ�Ʈ
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
			8 + 8, // x ��ġ: �ڽ� ���� ���� + ���� ����
			8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
			140, // ��ư �ʺ�
			64, // ��ư ����
			hwnd, // �θ� ������
			(HMENU)1, // ��ư ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// �� ��° ��ư
		hButton2 = CreateWindow(
			TEXT("button"), // ��ư Ŭ����
			TEXT("Circle"), // ��ư �ؽ�Ʈ
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
			8 + 8 + 140 + 16, // x ��ġ: �ڽ� ���� ���� + ���� ����
			8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
			140, // ��ư �ʺ�
			64, // ��ư ����
			hwnd, // �θ� ������
			(HMENU)2, // ��ư ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// �� ��° ��ư
		hButton3 = CreateWindow(
			TEXT("button"), // ��ư Ŭ����
			TEXT("Bonobono"), // ��ư �ؽ�Ʈ
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
			8 + 8 + (140 + 16) * 2, // x ��ġ: �ڽ� ���� ���� + ���� ����
			8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
			140, // ��ư �ʺ�
			64, // ��ư ����
			hwnd, // �θ� ������
			(HMENU)3, // ��ư ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// �� ��° ��ư
		hButton4 = CreateWindow(
			TEXT("button"), // ��ư Ŭ����
			TEXT("Ryan"), // ��ư �ؽ�Ʈ
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
			8 + 8 + (140 + 16) * 3, // x ��ġ: �ڽ� ���� ���� + ���� ����
			8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
			140, // ��ư �ʺ�
			64, // ��ư ����
			hwnd, // �θ� ������
			(HMENU)4, // ��ư ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// �ټ� ��° ��ư
		hButton5 = CreateWindow(
			TEXT("button"), // ��ư Ŭ����
			TEXT("Cube"), // ��ư �ؽ�Ʈ
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // ��Ÿ��
			8 + 8 + (140 + 16) * 4, // x ��ġ: �ڽ� ���� ���� + ���� ����
			8 + 8, // y ��ġ: �ڽ� ��� ���� + ���� ����
			140, // ��ư �ʺ�
			64, // ��ư ����
			hwnd, // �θ� ������
			(HMENU)5, // ��ư ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
	}
	break;

	// ���콺 �������� ����� ����
	case WM_SETCURSOR:
	{
		// Ŀ���� ��ġ�� �����ɴϴ�.
		POINT pt;
		GetCursorPos(&pt);
		// �ش� ��ġ�� Ŭ���̾�Ʈ ������ ��ǥ�� ��ȯ�մϴ�.
		ScreenToClient(hwnd, &pt);
		// ����� ���� ���� Ŀ���� �ִ��� Ȯ���մϴ�.
		if (PtInRect(&drawing_area, pt))
		{
			// ����� ���� �ȿ� ������ Ŀ���� ũ�ν��� �����մϴ�.
			SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
		else
		{
			// ����� ���� �ۿ� ������ �⺻ Ŀ���� ����մϴ�.
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return TRUE; // �޽����� ó���Ǿ����� ��Ÿ���ϴ�.
	}
	break;

	// �����찡 ����Ȱ��
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// �ش������ ���� ���
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;

	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("������"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ���̱�.
	ShowWindow(hwnd, SW_SHOW); // â ����
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.

	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, NULL, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	// ���� �޽��� ������
	return (int)msg.wParam;

}