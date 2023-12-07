#include "DrawObject.h"

// �簢��
void DrawBox(HDC hdc, RECT& Box) {
	// �귯�ø� �����ϰ� ������ ��ũ��(�ܻ�)���� ����
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	// �׸��⿡ ����� �귯�ø� ����
	SelectObject(hdc, hBrush);
	// ������ �簢���� ��ǥ���� �̿��Ͽ� �簢���� �׸���
	Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);
	// ����� �귯�� ���ҽ��� ����
	DeleteObject(hBrush);							
}

// ��
void DrawCircle(HDC hdc, RECT& Circle) {
	// �귯�ø� �����ϰ� ������ ��ũ��(�ܻ�)���� ����
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	// �׸��⿡ ����� �귯�ø� ����
	SelectObject(hdc, hBrush);
	// ������ ���� ��ǥ���� �̿��Ͽ� ���� �׸���
	Ellipse(hdc, Circle.left, Circle.top, Circle.right, Circle.bottom);
	// ����� �귯�� ���ҽ��� ����
	DeleteObject(hBrush);
}

// ���뺸��
void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
	if (blink) {
		// ���뺸���� �� �Ǻο� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_Face = CreateSolidBrush(RGB(127, 200, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_Face);
		// ���뺸���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 235, 112, 565, 442);

		// ���뺸���� �Կ� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_Mouth);
		// ���뺸���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 380, 270, 420, 365);

		// ���뺸���� �� �� �κп� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_NoseWhite);
		// ���뺸���� �� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 350, 285, 400, 325);
		Ellipse(hdc, 400, 285, 450, 325);

		// ���뺸���� ���� �� �κп� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_NoseBlack);
		// ���뺸���� ���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 380, 265, 420, 305);

		// ���뺸���� ���� �ش��ϴ� ���� ���� ����
		HPEN B_Eye = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// �׸��⿡ ����� ���� ����
		SelectObject(hdc, B_Eye);
		// ���뺸���� �� �κ��� MoveToEx, LineTo �Լ��� �̿��Ͽ� �׸���
		MoveToEx(hdc, 292, 250, NULL);
		LineTo(hdc, 272, 240);
		MoveToEx(hdc, 292, 250, NULL);
		LineTo(hdc, 272, 260);

		MoveToEx(hdc, 502, 250, NULL);
		LineTo(hdc, 522, 240);
		MoveToEx(hdc, 502, 250, NULL);
		LineTo(hdc, 522, 260);

		// ���뺸���� ������ �ش��ϴ� ���� ���� ����
		HPEN B_Beard = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// �׸��⿡ ����� ���� ����
		SelectObject(hdc, B_Beard);
		// ���뺸���� ���� �κ��� MoveToEx, LineTo �Լ��� �̿��Ͽ� �׸���
		MoveToEx(hdc, 370, 300, NULL);
		LineTo(hdc, 330, 290);
		MoveToEx(hdc, 430, 300, NULL);
		LineTo(hdc, 470, 290);
		MoveToEx(hdc, 370, 310, NULL);
		LineTo(hdc, 330, 320);
		MoveToEx(hdc, 430, 310, NULL);
		LineTo(hdc, 470, 320);

		// ����� �귯��, �� ���ҽ��� ����
		DeleteObject(B_Face);
		DeleteObject(B_Mouth);
		DeleteObject(B_NoseWhite);
		DeleteObject(B_NoseBlack);
		DeleteObject(B_Eye);
		DeleteObject(B_Beard);
	}

	else {
		// ���뺸���� �� �Ǻο� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_Face = CreateSolidBrush(RGB(127, 200, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_Face);
		// ���뺸���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 235, 112, 565, 442);

		// ���뺸���� �Կ� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_Mouth);
		// ���뺸���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 380, 270, 420, 365);

		// ���뺸���� �� �� �κп� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_NoseWhite);
		// ���뺸���� �� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 350, 285, 400, 325);
		Ellipse(hdc, 400, 285, 450, 325);

		// ���뺸���� ���� �� �κп� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_NoseBlack);
		// ���뺸���� ���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 380, 265, 420, 305);

		// ���뺸���� �� �κп� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_EyeBlack = CreateSolidBrush(RGB(0, 0, 0));
		// �׸��⿡ ����� �귯�ø� ����
		SelectObject(hdc, B_EyeBlack);
		// ���뺸���� �� �κ��� Ellipse �Լ��� �̿��Ͽ� �׸���
		Ellipse(hdc, 270, 245, 280, 265);
		Ellipse(hdc, 530, 245, 520, 265);

		// ���뺸���� �����ڿ� �ش��ϴ� ���� �귯�ø� ����
		HBRUSH B_EyeWhite = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, B_EyeWhite);
		Ellipse(hdc, 272, 250, 278, 258);
		Ellipse(hdc, 522, 250, 528, 258);

		// ���뺸���� ������ �ش��ϴ� ���� ���� ����
		HPEN B_Beard = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// �׸��⿡ ����� ���� ����
		SelectObject(hdc, B_Beard);
		// ���뺸���� ���� �κ��� MoveToEx, LineTo �Լ��� �̿��Ͽ� �׸���
		MoveToEx(hdc, 370, 300, NULL);
		LineTo(hdc, 330, 290);
		MoveToEx(hdc, 430, 300, NULL);
		LineTo(hdc, 470, 290);
		MoveToEx(hdc, 370, 310, NULL);
		LineTo(hdc, 330, 320);
		MoveToEx(hdc, 430, 310, NULL);
		LineTo(hdc, 470, 320);

		// ����� �귯��, �� ���ҽ��� ����
		DeleteObject(B_Face);
		DeleteObject(B_Mouth);
		DeleteObject(B_NoseWhite);
		DeleteObject(B_NoseBlack);
		DeleteObject(B_EyeBlack);
		DeleteObject(B_EyeWhite);
		DeleteObject(B_Beard);
	}
}

// ���̾�
void DrawRyan(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	// ���̾� ��ǥ�� ����(���̾��� �ݴ�� �׸��� ��츦 ����Ͽ�)
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };
	POINT CENTERPOINT = { 0 };

	MINPOINT.x = min(startPoint.x, endPoint.x);
	MINPOINT.y = min(startPoint.y, endPoint.y);
	MAXPOINT.x = max(startPoint.x, endPoint.x);
	MAXPOINT.y = max(startPoint.y, endPoint.y);

	// ���콺�� �������� ������ ���� �߾� ��ǥ�� ���
	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	// ���̾��� �Ǻο� �ش��ϴ� ���� �귯�ø� ����
	HBRUSH R_Skin = CreateSolidBrush(RGB(255, 200, 15));
	// �׸��⿡ ����� �귯�ø� ����
	SelectObject(hdc, R_Skin);

	// ���̾��� �Ϳ� �ش��ϴ� ��ǥ���� ������ ���� ���� �� ��ǥ�� �Ҵ�
	RECT R_LeftEar = { MINPOINT.x - width / 10, MINPOINT.y - width / 10, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
	RECT R_RightEar = { MAXPOINT.x - width / 3, MINPOINT.y - width / 10, MAXPOINT.x + width / 10, MINPOINT.y + height / 3 };

	// ���̾��� �󱼿� �ش��ϴ� ��ǥ���� ������ ���� ���� �� ��ǥ�� �Ҵ�
	RECT R_Face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };

	// ���̾��� �� �κ��� Ellipse �Լ��� �̿��ؼ� �׸���
	Ellipse(hdc, R_LeftEar.left, R_LeftEar.top, R_LeftEar.right, R_LeftEar.bottom);
	Ellipse(hdc, R_RightEar.left, R_RightEar.top, R_RightEar.right, R_RightEar.bottom);

	// ���̾��� �� �κ��� Ellipse �Լ��� �̿��ؼ� �׸���
	Ellipse(hdc, R_Face.left, R_Face.top, R_Face.right, R_Face.bottom);

	// ���̾��� ���翡 �ش��ϴ� ���� ���� ����
	HPEN R_Eyebrow = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	// �׸��⿡ ����� ���� ����
	SelectObject(hdc, R_Eyebrow);

	// ���̾��� ���� �κ��� MoveToEx, LineTo �Լ��� �̿��Ͽ� �׸���
	MoveToEx(hdc, MINPOINT.x + centerX / 4 + centerX / 30, MINPOINT.y + centerY / 3 * 2, NULL);
	LineTo(hdc, MINPOINT.x + (centerX / 4 * 3) - centerX / 30, MINPOINT.y + (centerY / 3 * 2));
	MoveToEx(hdc, MINPOINT.x + centerX / 4 + centerX / 30, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
	LineTo(hdc, MINPOINT.x + (centerX / 4 * 3) - centerX / 30, MINPOINT.y + (centerY / 3 * 2) + 2);
	MoveToEx(hdc, MINPOINT.x + centerX / 4 + centerX / 30, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
	LineTo(hdc, MINPOINT.x + (centerX / 4 * 3) - centerX / 30, MINPOINT.y + (centerY / 3 * 2) + 4);

	MoveToEx(hdc, MAXPOINT.x - centerX / 4 - centerX / 30, MINPOINT.y + centerY / 3 * 2, NULL);
	LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3) + centerX / 30, MINPOINT.y + (centerY / 3 * 2));
	MoveToEx(hdc, MAXPOINT.x - centerX / 4 - centerX / 30, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
	LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3) + centerX / 30, MINPOINT.y + (centerY / 3 * 2) + 2);
	MoveToEx(hdc, MAXPOINT.x - centerX / 4 - centerX / 30, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
	LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3) + centerX / 30, MINPOINT.y + (centerY / 3 * 2) + 4);

	// ���̾��� ���� �ش��ϴ� ���� �귯�ø� ����
	HBRUSH R_Eye = CreateSolidBrush(RGB(0, 0, 0));
	// �׸��⿡ ����� �귯�ø� ����
	SelectObject(hdc, R_Eye);

	// ���̾��� ���� �ش��ϴ� ��ǥ���� ������ ���� ���� �� ��ǥ�� �Ҵ�
	POINT R_LeftEyeP = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
	POINT R_RightEyeP = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
	RECT R_LeftEye = { R_LeftEyeP.x, R_LeftEyeP.y + 5, R_LeftEyeP.x + width / 15, R_LeftEyeP.y + height / 15 + 5 };
	RECT R_RightEye = { R_RightEyeP.x, R_RightEyeP.y + 5, R_RightEyeP.x - width / 15, R_RightEyeP.y + height / 15 + 5 };

	// ���̾��� �� �κ��� Ellipse �Լ��� �̿��ؼ� �׸���
	Ellipse(hdc, R_LeftEye.left, R_LeftEye.top, R_LeftEye.right, R_LeftEye.bottom);
	Ellipse(hdc, R_RightEye.left, R_RightEye.top, R_RightEye.right, R_RightEye.bottom);

	// ���̾��� �ڿ� �ش��ϴ� ���� �귯�ø� ����
	HBRUSH R_Nose = CreateSolidBrush(RGB(255, 255, 255));
	// �׸��⿡ ����� �귯�ø� ����
	SelectObject(hdc, R_Nose);

	// ���̾��� �ڿ� �ش��ϴ� ��ǥ���� ������ ���� ���� �� ��ǥ�� �Ҵ�
	RECT R_LeftNose = { centerPoint.x - centerX / 5, centerPoint.y + 10, centerPoint.x, centerPoint.y + centerY / 5 + 10 };
	RECT R_RightNose = { centerPoint.x, centerPoint.y + 10, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 + 10 };

	// ���̾��� �� �κ��� Ellipse �Լ��� �̿��ؼ� �׸���
	Ellipse(hdc, R_LeftNose.left, R_LeftNose.top, R_LeftNose.right, R_LeftNose.bottom);
	Ellipse(hdc, R_RightNose.left, R_RightNose.top, R_RightNose.right, R_RightNose.bottom);

	// ����� �귯��, �� ���ҽ��� ����
	DeleteObject(R_Skin);
	DeleteObject(R_Eyebrow);
	DeleteObject(R_Eye);
	DeleteObject(R_Nose);
}

//ť��
void DrawCube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	POINT mouseDistance = {};
	int diagonal;
	POINT cubeStartPoint = {};
	POINT cubeStartPoint2 = {};
	POINT cubeEndPoint = {};
	POINT cubeEndPoint2 = {};

	// ���콺�� �̵��Ÿ� ���
	if (startPoint.x < endPoint.x)
		mouseDistance.x = endPoint.x - startPoint.x;
	else
		mouseDistance.x = startPoint.x - endPoint.x;
	if (startPoint.y < endPoint.y)
		mouseDistance.y = endPoint.y - startPoint.y;
	else
		mouseDistance.y = startPoint.y - endPoint.y;

	// ť�� ���� ���� ���� ����
	if (mouseDistance.x > mouseDistance.y) {
		diagonal = mouseDistance.y / 4;
	}
	else {
		diagonal = mouseDistance.x / 4;
	}

	// ť���� �⺻ ���� ��ǥ���� �� ��ǥ�� �Ҵ�
	cubeStartPoint.x = startPoint.x;
	cubeStartPoint.y = startPoint.y + diagonal;
	cubeEndPoint.x = endPoint.x - diagonal;
	cubeEndPoint.y = endPoint.y;
	cubeStartPoint2.x = startPoint.x + diagonal;
	cubeStartPoint2.y = startPoint.y;
	cubeEndPoint2.x = endPoint.x;
	cubeEndPoint2.y = endPoint.y - diagonal;

	// ť�긦 �巡���ϴ� ���⿡ ���� ��ǥ�� ���Ҵ�
	if (startPoint.x > endPoint.x && startPoint.y > endPoint.y) {
		cubeStartPoint.x = startPoint.x;
		cubeStartPoint.y = startPoint.y - diagonal;
		cubeEndPoint.x = endPoint.x + diagonal;
		cubeEndPoint.y = endPoint.y;
		cubeStartPoint2.x = startPoint.x - diagonal;
		cubeStartPoint2.y = startPoint.y;
		cubeEndPoint2.x = endPoint.x;
		cubeEndPoint2.y = endPoint.y + diagonal;
	}
	else if (startPoint.x > endPoint.x) {
		cubeStartPoint.x = startPoint.x;
		cubeStartPoint.y = startPoint.y + diagonal;
		cubeEndPoint.x = endPoint.x + diagonal;
		cubeEndPoint.y = endPoint.y;
		cubeStartPoint2.x = startPoint.x - diagonal;
		cubeStartPoint2.y = startPoint.y;
		cubeEndPoint2.x = endPoint.x;
		cubeEndPoint2.y = endPoint.y - diagonal;
	}
	else if (startPoint.y > endPoint.y) {
		cubeStartPoint.x = startPoint.x;
		cubeStartPoint.y = startPoint.y - diagonal;
		cubeEndPoint.x = endPoint.x - diagonal;
		cubeEndPoint.y = endPoint.y;
		cubeStartPoint2.x = startPoint.x + diagonal;
		cubeStartPoint2.y = startPoint.y;
		cubeEndPoint2.x = endPoint.x;
		cubeEndPoint2.y = endPoint.y + diagonal;
	}

	// ť���� �鿡 ���� ��ǥ�� �Ҵ�
	POINT vertices[6][4] = {
		// �޸��� ��ǥ�� �Ҵ�
		{{cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y}},
		 // �Ʒ����� ��ǥ�� �Ҵ�
		 {{cubeStartPoint.x, cubeEndPoint.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint.x, cubeEndPoint.y}},
		 // ���ʸ��� ��ǥ�� �Ҵ�
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeStartPoint.x, cubeEndPoint.y}},
		 // �����ʸ��� ��ǥ�� �Ҵ�
		 {{cubeEndPoint.x, cubeStartPoint.y},
		 {cubeEndPoint.x, cubeEndPoint.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y}},
		 // ������ ��ǥ�� �Ҵ�
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y},
		 {cubeEndPoint.x, cubeStartPoint.y}},
		 // �ո��� ��ǥ�� �Ҵ�
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint.x, cubeEndPoint.y},
		 {cubeEndPoint.x, cubeEndPoint.y},
		 {cubeEndPoint.x, cubeStartPoint.y}}
	};

	// ���� �����ϰ� ������ ���������� ����
	HPEN hPen= CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	// �׸��⿡ ����� ���� ����
	SelectObject(hdc, hPen);

	// �Ҵ�� ���� ��ǥ���� �̿��Ͽ� ť�� �׸���
	for (int i = 0; i < 6; i++) {
		Polygon(hdc, vertices[i], 4);
	}

	// ����� �� ���ҽ��� ����
	DeleteObject(hPen);
}