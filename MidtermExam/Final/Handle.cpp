#include "Handle.h"
#include "Common.h"

// ���콺 �̵� �ڵ鷯
void HandleMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseLButtonPressed, BOOL& isMouseRButtonPressed, POINT& startPoint, POINT& endPoint, RECT& Box, RECT& Circle, POINT& m_startPoint, POINT& m_endPoint, POINT& startPointSaved, POINT& endPointSaved, POINT& distance) {
	// ������ ������ Circle�̰� ���콺 ���� ��ư�� ���� ���
	if (Shape == S_Circle && isMouseLButtonPressed) {
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// �������� �� ���� �� ���� ������ ����
		int radius = min(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y)); 

		// �߽��� x ��ǥ�� y��ǥ ����
		int centerX = (startPoint.x + endPoint.x) / 2;
		int centerY = (startPoint.y + endPoint.y) / 2;

		// ���� ��ǥ�� ���
		Circle.left = centerX - radius;
		Circle.top = centerY - radius;
		Circle.right = centerX + radius;
		Circle.bottom = centerY + radius;

		// ȭ���� �����Ͽ� ���� �׸���
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

			// ȭ���� �����Ͽ� ���� �׸���
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}

	// ������ ������ Box, Cube�̰� ���콺 ���� ��ư�� ���� ���
	if (Shape == S_Box && isMouseLButtonPressed || Shape == S_Cube && isMouseLButtonPressed) {
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

		// ȭ���� �����Ͽ� �簢���� �׸���
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}

	// ������ ������ Ryan�̰� ���콺 ���� ��ư�� ���� ���
	if (Shape == S_Ryan && isMouseLButtonPressed) {
		// ���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� ������ ��ǥ������ ����
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// ȭ���� �����Ͽ� Ryan�� �׸���
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}
}

// ���콺 ���� ��ư ���� �ڵ鷯
void HandleLeftButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, POINT& startPoint, POINT& endPoint, BOOL& isMouseLButtonPressed, int& Shape, const RECT& drawing_area) {
	// ��ǥ���� �����ͼ� ���� ��ǥ���� �Ҵ�
	startPoint = { LOWORD(lParam), HIWORD(lParam) };
	endPoint = startPoint;

	// ������ ������ Circle, Box, Ryan�� ��쿡�� ó��
	if (Shape == S_Circle || Shape == S_Box || Shape == S_Ryan || Shape == S_Cube) {
		// �������� ����� ���� �ȿ� �ִٸ�
		if (PtInRect(&drawing_area, startPoint)) {
			// üũ ������ ���� TRUE�� ����
			isMouseLButtonPressed = TRUE;
		}
	}
}

// ���콺 ������ ��ư ���� �ڵ鷯
void HandleRightButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseRButtonPressed, POINT& startPointSaved, POINT& endPointSaved, POINT& endPoint, POINT& m_startPoint, RECT& Box, RECT& Circle) {
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