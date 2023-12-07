#include "DrawObject.h"

// 사각형
void DrawBox(HDC hdc, RECT& Box) {
	// 브러시를 생성하고 색상은 핑크색(단색)으로 지정
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	// 그리기에 사용할 브러시를 선택
	SelectObject(hdc, hBrush);
	// 저장한 사각형의 좌표값을 이용하여 사각형을 그리기
	Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);
	// 사용한 브러시 리소스를 해제
	DeleteObject(hBrush);							
}

// 원
void DrawCircle(HDC hdc, RECT& Circle) {
	// 브러시를 생성하고 색상은 핑크색(단색)으로 지정
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	// 그리기에 사용할 브러시를 선택
	SelectObject(hdc, hBrush);
	// 저장한 원의 좌표값을 이용하여 원을 그리기
	Ellipse(hdc, Circle.left, Circle.top, Circle.right, Circle.bottom);
	// 사용한 브러시 리소스를 해제
	DeleteObject(hBrush);
}

// 보노보노
void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
	if (blink) {
		// 보노보노의 얼굴 피부에 해당하는 색의 브러시를 생성
		HBRUSH B_Face = CreateSolidBrush(RGB(127, 200, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_Face);
		// 보노보노의 얼굴 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 235, 112, 565, 442);

		// 보노보노의 입에 해당하는 색의 브러시를 생성
		HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_Mouth);
		// 보노보노의 입 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 380, 270, 420, 365);

		// 보노보노의 흰 코 부분에 해당하는 색의 브러시를 생성
		HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_NoseWhite);
		// 보노보노의 흰 코 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 350, 285, 400, 325);
		Ellipse(hdc, 400, 285, 450, 325);

		// 보노보노의 검은 코 부분에 해당하는 색의 브러시를 생성
		HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_NoseBlack);
		// 보노보노의 검은 코 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 380, 265, 420, 305);

		// 보노보노의 눈에 해당하는 색의 펜을 생성
		HPEN B_Eye = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// 그리기에 사용할 펜을 선택
		SelectObject(hdc, B_Eye);
		// 보노보노의 눈 부분을 MoveToEx, LineTo 함수를 이용하여 그리기
		MoveToEx(hdc, 292, 250, NULL);
		LineTo(hdc, 272, 240);
		MoveToEx(hdc, 292, 250, NULL);
		LineTo(hdc, 272, 260);

		MoveToEx(hdc, 502, 250, NULL);
		LineTo(hdc, 522, 240);
		MoveToEx(hdc, 502, 250, NULL);
		LineTo(hdc, 522, 260);

		// 보노보노의 수염에 해당하는 색의 펜을 생성
		HPEN B_Beard = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// 그리기에 사용할 펜을 선택
		SelectObject(hdc, B_Beard);
		// 보노보노의 수염 부분을 MoveToEx, LineTo 함수를 이용하여 그리기
		MoveToEx(hdc, 370, 300, NULL);
		LineTo(hdc, 330, 290);
		MoveToEx(hdc, 430, 300, NULL);
		LineTo(hdc, 470, 290);
		MoveToEx(hdc, 370, 310, NULL);
		LineTo(hdc, 330, 320);
		MoveToEx(hdc, 430, 310, NULL);
		LineTo(hdc, 470, 320);

		// 사용한 브러시, 펜 리소스를 해제
		DeleteObject(B_Face);
		DeleteObject(B_Mouth);
		DeleteObject(B_NoseWhite);
		DeleteObject(B_NoseBlack);
		DeleteObject(B_Eye);
		DeleteObject(B_Beard);
	}

	else {
		// 보노보노의 얼굴 피부에 해당하는 색의 브러시를 생성
		HBRUSH B_Face = CreateSolidBrush(RGB(127, 200, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_Face);
		// 보노보노의 얼굴 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 235, 112, 565, 442);

		// 보노보노의 입에 해당하는 색의 브러시를 생성
		HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_Mouth);
		// 보노보노의 입 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 380, 270, 420, 365);

		// 보노보노의 흰 코 부분에 해당하는 색의 브러시를 생성
		HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_NoseWhite);
		// 보노보노의 흰 코 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 350, 285, 400, 325);
		Ellipse(hdc, 400, 285, 450, 325);

		// 보노보노의 검은 코 부분에 해당하는 색의 브러시를 생성
		HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_NoseBlack);
		// 보노보노의 검은 코 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 380, 265, 420, 305);

		// 보노보노의 눈 부분에 해당하는 색의 브러시를 생성
		HBRUSH B_EyeBlack = CreateSolidBrush(RGB(0, 0, 0));
		// 그리기에 사용할 브러시를 선택
		SelectObject(hdc, B_EyeBlack);
		// 보노보노의 눈 부분을 Ellipse 함수를 이용하여 그리기
		Ellipse(hdc, 270, 245, 280, 265);
		Ellipse(hdc, 530, 245, 520, 265);

		// 보노보노의 눈동자에 해당하는 색의 브러시를 생성
		HBRUSH B_EyeWhite = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, B_EyeWhite);
		Ellipse(hdc, 272, 250, 278, 258);
		Ellipse(hdc, 522, 250, 528, 258);

		// 보노보노의 수염에 해당하는 색의 펜을 생성
		HPEN B_Beard = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		// 그리기에 사용할 펜을 선택
		SelectObject(hdc, B_Beard);
		// 보노보노의 수염 부분을 MoveToEx, LineTo 함수를 이용하여 그리기
		MoveToEx(hdc, 370, 300, NULL);
		LineTo(hdc, 330, 290);
		MoveToEx(hdc, 430, 300, NULL);
		LineTo(hdc, 470, 290);
		MoveToEx(hdc, 370, 310, NULL);
		LineTo(hdc, 330, 320);
		MoveToEx(hdc, 430, 310, NULL);
		LineTo(hdc, 470, 320);

		// 사용한 브러시, 펜 리소스를 해제
		DeleteObject(B_Face);
		DeleteObject(B_Mouth);
		DeleteObject(B_NoseWhite);
		DeleteObject(B_NoseBlack);
		DeleteObject(B_EyeBlack);
		DeleteObject(B_EyeWhite);
		DeleteObject(B_Beard);
	}
}

// 라이언
void DrawRyan(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	// 라이언 좌표값 정렬(라이언을 반대로 그리는 경우를 대비하여)
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };
	POINT CENTERPOINT = { 0 };

	MINPOINT.x = min(startPoint.x, endPoint.x);
	MINPOINT.y = min(startPoint.y, endPoint.y);
	MAXPOINT.x = max(startPoint.x, endPoint.x);
	MAXPOINT.y = max(startPoint.y, endPoint.y);

	// 마우스의 시작점과 끝점을 통해 중앙 좌표값 계산
	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	// 라이언의 피부에 해당하는 색의 브러시를 생성
	HBRUSH R_Skin = CreateSolidBrush(RGB(255, 200, 15));
	// 그리기에 사용할 브러시를 선택
	SelectObject(hdc, R_Skin);

	// 라이언의 귀에 해당하는 좌표값을 저장할 변수 선언 및 좌표값 할당
	RECT R_LeftEar = { MINPOINT.x - width / 10, MINPOINT.y - width / 10, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
	RECT R_RightEar = { MAXPOINT.x - width / 3, MINPOINT.y - width / 10, MAXPOINT.x + width / 10, MINPOINT.y + height / 3 };

	// 라이언의 얼굴에 해당하는 좌표값을 저장할 변수 선언 및 좌표값 할당
	RECT R_Face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };

	// 라이언의 귀 부분을 Ellipse 함수를 이용해서 그리기
	Ellipse(hdc, R_LeftEar.left, R_LeftEar.top, R_LeftEar.right, R_LeftEar.bottom);
	Ellipse(hdc, R_RightEar.left, R_RightEar.top, R_RightEar.right, R_RightEar.bottom);

	// 라이언의 얼굴 부분을 Ellipse 함수를 이용해서 그리기
	Ellipse(hdc, R_Face.left, R_Face.top, R_Face.right, R_Face.bottom);

	// 라이언의 눈썹에 해당하는 색의 펜을 생성
	HPEN R_Eyebrow = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	// 그리기에 사용할 펜을 선택
	SelectObject(hdc, R_Eyebrow);

	// 라이언의 눈썹 부분을 MoveToEx, LineTo 함수를 이용하여 그리기
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

	// 라이언의 눈에 해당하는 색의 브러시를 생성
	HBRUSH R_Eye = CreateSolidBrush(RGB(0, 0, 0));
	// 그리기에 사용할 브러시를 선택
	SelectObject(hdc, R_Eye);

	// 라이언의 눈에 해당하는 좌표값을 저장할 변수 선언 및 좌표값 할당
	POINT R_LeftEyeP = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
	POINT R_RightEyeP = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
	RECT R_LeftEye = { R_LeftEyeP.x, R_LeftEyeP.y + 5, R_LeftEyeP.x + width / 15, R_LeftEyeP.y + height / 15 + 5 };
	RECT R_RightEye = { R_RightEyeP.x, R_RightEyeP.y + 5, R_RightEyeP.x - width / 15, R_RightEyeP.y + height / 15 + 5 };

	// 라이언의 눈 부분을 Ellipse 함수를 이용해서 그리기
	Ellipse(hdc, R_LeftEye.left, R_LeftEye.top, R_LeftEye.right, R_LeftEye.bottom);
	Ellipse(hdc, R_RightEye.left, R_RightEye.top, R_RightEye.right, R_RightEye.bottom);

	// 라이언의 코에 해당하는 색의 브러시를 생성
	HBRUSH R_Nose = CreateSolidBrush(RGB(255, 255, 255));
	// 그리기에 사용할 브러시를 선택
	SelectObject(hdc, R_Nose);

	// 라이언의 코에 해당하는 좌표값을 저장할 변수 선언 및 좌표값 할당
	RECT R_LeftNose = { centerPoint.x - centerX / 5, centerPoint.y + 10, centerPoint.x, centerPoint.y + centerY / 5 + 10 };
	RECT R_RightNose = { centerPoint.x, centerPoint.y + 10, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 + 10 };

	// 라이언의 코 부분을 Ellipse 함수를 이용해서 그리기
	Ellipse(hdc, R_LeftNose.left, R_LeftNose.top, R_LeftNose.right, R_LeftNose.bottom);
	Ellipse(hdc, R_RightNose.left, R_RightNose.top, R_RightNose.right, R_RightNose.bottom);

	// 사용한 브러시, 펜 리소스를 해제
	DeleteObject(R_Skin);
	DeleteObject(R_Eyebrow);
	DeleteObject(R_Eye);
	DeleteObject(R_Nose);
}

//큐브
void DrawCube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	POINT mouseDistance = {};
	int diagonal;
	POINT cubeStartPoint = {};
	POINT cubeStartPoint2 = {};
	POINT cubeEndPoint = {};
	POINT cubeEndPoint2 = {};

	// 마우스의 이동거리 계산
	if (startPoint.x < endPoint.x)
		mouseDistance.x = endPoint.x - startPoint.x;
	else
		mouseDistance.x = startPoint.x - endPoint.x;
	if (startPoint.y < endPoint.y)
		mouseDistance.y = endPoint.y - startPoint.y;
	else
		mouseDistance.y = startPoint.y - endPoint.y;

	// 큐브 길이 조절 조건 설정
	if (mouseDistance.x > mouseDistance.y) {
		diagonal = mouseDistance.y / 4;
	}
	else {
		diagonal = mouseDistance.x / 4;
	}

	// 큐브의 기본 시작 좌표값과 끝 좌표값 할당
	cubeStartPoint.x = startPoint.x;
	cubeStartPoint.y = startPoint.y + diagonal;
	cubeEndPoint.x = endPoint.x - diagonal;
	cubeEndPoint.y = endPoint.y;
	cubeStartPoint2.x = startPoint.x + diagonal;
	cubeStartPoint2.y = startPoint.y;
	cubeEndPoint2.x = endPoint.x;
	cubeEndPoint2.y = endPoint.y - diagonal;

	// 큐브를 드래그하는 방향에 따라 좌표값 재할당
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

	// 큐브의 면에 대한 좌표값 할당
	POINT vertices[6][4] = {
		// 뒷면의 좌표값 할당
		{{cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y}},
		 // 아랫면의 좌표값 할당
		 {{cubeStartPoint.x, cubeEndPoint.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint.x, cubeEndPoint.y}},
		 // 왼쪽면의 좌표값 할당
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeStartPoint2.x, cubeEndPoint2.y},
		 {cubeStartPoint.x, cubeEndPoint.y}},
		 // 오른쪽면의 좌표값 할당
		 {{cubeEndPoint.x, cubeStartPoint.y},
		 {cubeEndPoint.x, cubeEndPoint.y},
		 {cubeEndPoint2.x, cubeEndPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y}},
		 // 윗면의 좌표값 할당
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint2.x, cubeStartPoint2.y},
		 {cubeEndPoint2.x, cubeStartPoint2.y},
		 {cubeEndPoint.x, cubeStartPoint.y}},
		 // 앞면의 좌표값 할당
		 {{cubeStartPoint.x, cubeStartPoint.y},
		 {cubeStartPoint.x, cubeEndPoint.y},
		 {cubeEndPoint.x, cubeEndPoint.y},
		 {cubeEndPoint.x, cubeStartPoint.y}}
	};

	// 펜을 생성하고 색상은 검정색으로 지정
	HPEN hPen= CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	// 그리기에 사용할 펜을 선택
	SelectObject(hdc, hPen);

	// 할당된 면의 좌표값을 이용하여 큐브 그리기
	for (int i = 0; i < 6; i++) {
		Polygon(hdc, vertices[i], 4);
	}

	// 사용한 펜 리소스를 해제
	DeleteObject(hPen);
}