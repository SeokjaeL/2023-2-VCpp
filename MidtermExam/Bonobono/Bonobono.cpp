#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 버튼의 값을 저장할 매크로 상수
#define S_Box 1
#define S_Circle 2
#define S_Bonobono 3
#define S_Ryan 4
#define S_Cube 5

#include <windows.h>

// 기능 버튼에 대한 전역 변수 선언
HWND hButton1;
HWND hButton2;
HWND hButton3;
HWND hButton4;
HWND hButton5;

// 좌표값을 저장할 전역 변수 선언
// 시작과 끝 좌표와 좌표값 백업, 마우스 이동 좌표, 거리값 좌표, 도형에 대한 좌표, 드로잉 영역에 대한 좌표
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT m_startPoint{ 0 };
POINT m_endPoint = { 0 };
POINT distance = { 0 };
POINT startPointSaved = { 0 };
POINT endPointSaved = { 0 };
RECT Box = { 0 };
RECT Circle = { 0 };
RECT drawing_area = { 0 };

// 누른 버튼의 도형의 종류를 저장할 전역 변수 선언
int Shape = 0;

// 마우스와 스페이스의 입력상태 체크 전역 변수 선언
int isMouseLButtonPressed = FALSE;	// 마우스 왼쪽 버튼이 눌린 상태인지 체크
int isMouseRButtonPressed = FALSE;	// 마우스 오른쪽 버튼이 눌린 상태인지 체크
int isSpaceButtonPressed = FALSE;	// 스페이스 버튼이 눌린 상태인지 체크

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// 창의 최소 및 최대 크기에 대한 정보 제어
	case WM_GETMINMAXINFO:
	{
		// MINMAXINFO 구조체 포인터를 선언 후, lParam(창의 크기 제한 정보)에 저장된 값을 MINMAXINFO 구조체 포인터로 캐스팅한 값으로 초기화 
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;

		// 윈도우 영역 크기 정의
		RECT rect = { 0, 0, 800, 480 };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		// MINMAXINFO 구조체 멤버들을 설정하여 창의 최소 크기와 최대 크기를 지정
		minMaxInfo->ptMinTrackSize.x = width; // 최소 너비
		minMaxInfo->ptMinTrackSize.y = height; // 최소 높이
		minMaxInfo->ptMaxTrackSize.x = width; // 최대 너비
		minMaxInfo->ptMaxTrackSize.y = height; // 최대 높이
	}
	break;

	// 키가 눌린 상태인 경우
	case WM_KEYDOWN:
	{
		// 만약에 스페이스키가 눌린 상태라면
		if (wParam == VK_SPACE) {
			// 체크 변수의 값을 TRUE로 설정
			isSpaceButtonPressed = TRUE;

			// WM_PAINT 메시지 호출
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// 키가 떼진 상태라면
	case WM_KEYUP:
	{
		// 만약에 스페이스키가 떼진 상태라면
		if (wParam == VK_SPACE) {
			// 체크 변수의 값을 FALSE으로 설정
			isSpaceButtonPressed = FALSE;

			// WM_PAINT 메시지 호출
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	// 버튼이 눌렸다면
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam); // 버튼의 ID를 가져옵니다.

		// 버튼의 아이디에 따라 처리
		switch (wmId)
		{
		// Box 버튼이라면
		case 1:
		{
			Shape = S_Box;								// 도형의 종류를 Box로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			Box = { 0 };								// Box의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Circle 버튼이라면
		case 2:
		{
			Shape = S_Circle;							// 도형의 종류를 Circle로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			Circle = { 0 };								// Circle의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Bonobono 버튼이라면
		case 3:
		{
			Shape = S_Bonobono;							// 도형의 종류를 Bonobono로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// WM_PAINT 메시지 호출
			break;
		}

		// Ryan 버튼이라면
		case 4:
		{
			Shape = S_Ryan;								// 도형의 종류를 Ryan으로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			startPoint = { 0 };							// startPoint의 좌표값을 0으로 초기화
			endPoint = { 0 };							// endPoint의 좌표값을 0으로 초기화
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// Cube 버튼이라면
		case 5:
		{
			Shape = S_Cube;								// 도형의 종류를 Cube로 설정
			SetFocus(hwnd);								// 포커스를 윈도우 핸들러쪽으로 이동(버튼 포커스 해제)
			InvalidateRect(hwnd, &drawing_area, TRUE);	// 드로잉 영역을 초기화
			break;
		}

		// 해당사항이 없는 경우
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		// 도형의 종류가 Circle이나 Box거나 Ryan이라면
		if (Shape == S_Circle || Shape == S_Box || Shape == S_Ryan) {
			// 좌표값을 가져와서 시작 좌표값에 할당(endPoint의 초기값은 startPoint와 동일) 
			startPoint = { LOWORD(lParam), HIWORD(lParam) };
			endPoint = startPoint;

			// 시작점이 드로잉 영역 안에 있다면
			if (PtInRect(&drawing_area, startPoint)) {
				// 체크 변수의 값을 TRUE로 설정
				isMouseLButtonPressed = TRUE;
			}
		}
	}
	break;

	// 마우스 왼쪽 버튼을 뗀 경우
	case WM_LBUTTONUP:
	{
		// 체크 변수의 값을 FALSE으로 설정
		isMouseLButtonPressed = FALSE;
	}
	break;

	// 마우스 오른쪽 버튼이 눌린 경우
	case WM_RBUTTONDOWN:
	{
		// 도형의 종류가 Circle인 경우
		if (Shape == S_Circle) {
			// 시작 좌표값을 백업(endPoint의 초기값은 startPointSaved와 동일) 
			startPointSaved = { LOWORD(lParam), HIWORD(lParam) };
			endPoint = startPointSaved;

			// 시작점이 드로잉 영역 안에 있다면
			if (PtInRect(&drawing_area, startPointSaved) && PtInRect(&Circle, startPointSaved)) {
				// 체크 변수의 값을 TRUE로 설정
				isMouseRButtonPressed = TRUE;
			}
		}

		// 도형의 종류가 Box인 경우
		if (Shape == S_Box){
			// 마우스 오른쪽 버튼을 눌렀을 때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 시작된 좌표값으로 설정
			m_startPoint.x = LOWORD(lParam);
			m_startPoint.y = HIWORD(lParam);

			// 마우스 오른쪽 버튼을 기존에 만들어진 사각형 영역 안에서 눌렀다면
			if (PtInRect(&drawing_area, m_startPoint) && PtInRect(&Box, m_startPoint))
			{
				// 체크 변수의 값을 TRUE로 설정
				isMouseRButtonPressed = TRUE;

				// 기존 사각형의 좌표값을 Saved 변수에 저장
				startPointSaved.x = Box.left;
				startPointSaved.y = Box.top;
				endPointSaved.x = Box.right;
				endPointSaved.y = Box.bottom;
			}
		}
	}
	break;

	// 마우스 오른쪽 버튼을 뗀 경우
	case WM_RBUTTONUP:
	{
		// 체크 변수의 값을 FALSE로 설정
		isMouseRButtonPressed = FALSE;
	}
	break;

	// 마우스가 움직이는 경우
	case WM_MOUSEMOVE:
	{
		// 도형의 종류가 Circle이고 마우스 왼쪽 버튼이 눌린 경우
		if (Shape == S_Circle && isMouseLButtonPressed) {
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			int radius = min(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y)); // 반지름은 두 방향 중 작은 값으로 설정

			int centerX = (startPoint.x + endPoint.x) / 2; // 중심의 x 좌표
			int centerY = (startPoint.y + endPoint.y) / 2; // 중심의 y 좌표

			Circle.left = centerX - radius;
			Circle.top = centerY - radius;
			Circle.right = centerX + radius;
			Circle.bottom = centerY + radius;

			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// 도형의 종류가 Circle이고 마우스 오른쪽 버튼이 눌린 경우
		if (Shape == S_Circle && isMouseRButtonPressed) {

			// 현재 마우스 위치를 가져옵니다.
			POINT currentPoint = { LOWORD(lParam), HIWORD(lParam) };

			// 이전 endPoint 저장
			endPointSaved = endPoint;

			// 마우스 이동 거리 계산
			int deltaX = currentPoint.x - endPoint.x;

			if (abs(deltaX) >= 100) {
				// 이동 거리가 100px 이상이면 크기 조정
				int radius = (Circle.right - Circle.left) / 2;

				if (deltaX > 0) {
					// 우측으로 이동한 경우
					radius *= 2; // 2배 확대
				}
				else {
					// 좌측으로 이동한 경우
					radius /= 2; // 절반으로 축소
				}

				// 원의 중심을 유지하면서 크기를 조정
				int centerX = (Circle.left + Circle.right) / 2;
				int centerY = (Circle.top + Circle.bottom) / 2;

				Circle.left = centerX - radius;
				Circle.top = centerY - radius;
				Circle.right = centerX + radius;
				Circle.bottom = centerY + radius;

				// endPoint 업데이트
				endPoint = currentPoint;

				// 화면을 갱신하여 원을 그립니다.
				InvalidateRect(hwnd, &drawing_area, TRUE);
			}
		}

		// 도형의 종류가 Box이고 마우스 왼쪽 버튼이 눌린 경우
		if (Shape == S_Box && isMouseLButtonPressed) {
			// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			// 사각형 좌표값 정렬(사각형을 반대로 그리는 경우를 대비하여)
			Box.left = min(startPoint.x, endPoint.x);
			Box.top = min(startPoint.y, endPoint.y);
			Box.right = max(startPoint.x, endPoint.x);
			Box.bottom = max(startPoint.y, endPoint.y);

			// 화면을 갱신하여 사각형을 그립니다.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// 도형의 종류가 Box이고 마우스 오른쪽 버튼이 눌린 경우
		if (Shape == S_Box && isMouseRButtonPressed) {
			// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 끝난 좌표값으로 설정
			m_endPoint.x = LOWORD(lParam);
			m_endPoint.y = HIWORD(lParam);

			// 사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
			distance.x = m_endPoint.x - m_startPoint.x;
			distance.y = m_endPoint.y - m_startPoint.y;

			// 사각형의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
			Box.left = startPointSaved.x + distance.x;
			Box.top = startPointSaved.y + distance.y;
			Box.right = endPointSaved.x + distance.x;
			Box.bottom = endPointSaved.y + distance.y;

			// 화면을 갱신하여 사각형을 그립니다.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}

		// 도형의 종류가 Ryan이고 마우스 왼쪽 버튼이 눌린 경우
		if (Shape == S_Ryan && isMouseLButtonPressed) {
			// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
			endPoint = { LOWORD(lParam), HIWORD(lParam) };

			// 화면을 갱신하여 Ryan을 그립니다.
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		// 페인트 구조체 선언과 윈도우 핸들러 받아오기
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

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

		// 도형의 종류가 Circle이라면
		if (Shape == S_Circle){
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));									//	브러시를 생성하고 색상은 핑크색(단색)으로 지정
			SelectObject(hdc, hBrush);															//	그리기에 사용할 브러시를 선택
			Ellipse(hdc, Circle.left, Circle.top, Circle.right, Circle.bottom);	//	저장한 사각형의 좌표값을 이용하여 사각형을 그림
			DeleteObject(hBrush);																//	생성한 브러시를 삭제
		}

		// 도형의 종류가 Box라면
		if (Shape == S_Box){
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));									//	브러시를 생성하고 색상은 핑크색(단색)으로 지정
			SelectObject(hdc, hBrush);															//	그리기에 사용할 브러시를 선택
			Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);	//	저장한 사각형의 좌표값을 이용하여 사각형을 그림
			DeleteObject(hBrush);																//	생성한 브러시를 삭제
		}

		// 도형의 종류가 Bonobono라면
		if (Shape == S_Bonobono){
			if (isSpaceButtonPressed) {
				// 보노보노의 얼굴 피부에 해당하는 색의 브러시를 생성
				HBRUSH B_Face = CreateSolidBrush(RGB(127, 200, 255));
				// 브러시 선택
				SelectObject(hdc, B_Face);
				// 보노보노의 얼굴 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 235, 112, 565, 442);

				// 보노보노의 입에 해당하는 색의 브러시를 생성
				HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
				// 브러시 선택
				SelectObject(hdc, B_Mouth);
				// 보노보노의 입 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 380, 270, 420, 365);

				// 보노보노의 흰 코 부분에 해당하는 색의 브러시를 생성
				HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
				// 브러시 선택
				SelectObject(hdc, B_NoseWhite);
				// 보노보노의 흰 코 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 350, 285, 400, 325);
				Ellipse(hdc, 400, 285, 450, 325);

				// 보노보노의 검은 코 부분에 해당하는 색의 브러시를 생성
				HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
				// 브러시 선택
				SelectObject(hdc, B_NoseBlack);
				// 보노보노의 검은 코 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 380, 265, 420, 305);

				// 보노보노의 눈에 해당하는 색의 펜을 생성
				HPEN B_Eye = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				// 펜 선택
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
				// 펜 선택
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

				// 사용한 브러시 리소스를 해제
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
				// 브러시 선택
				SelectObject(hdc, B_Face);
				// 보노보노의 얼굴 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 235, 112, 565, 442);

				// 보노보노의 입에 해당하는 색의 브러시를 생성
				HBRUSH B_Mouth = CreateSolidBrush(RGB(255, 150, 255));
				// 브러시 선택
				SelectObject(hdc, B_Mouth);
				// 보노보노의 입 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 380, 270, 420, 365);

				// 보노보노의 흰 코 부분에 해당하는 색의 브러시를 생성
				HBRUSH B_NoseWhite = CreateSolidBrush(RGB(255, 255, 255));
				// 브러시 선택
				SelectObject(hdc, B_NoseWhite);
				// 보노보노의 흰 코 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 350, 285, 400, 325);
				Ellipse(hdc, 400, 285, 450, 325);

				// 보노보노의 검은 코 부분에 해당하는 색의 브러시를 생성
				HBRUSH B_NoseBlack = CreateSolidBrush(RGB(0, 0, 0));
				// 브러시 선택
				SelectObject(hdc, B_NoseBlack);
				// 보노보노의 검은 코 부분을 Ellipse 함수를 이용하여 그리기
				Ellipse(hdc, 380, 265, 420, 305);

				// 보노보노의 눈 부분에 해당하는 색의 브러시를 생성
				HBRUSH B_EyeBlack = CreateSolidBrush(RGB(0, 0, 0));
				// 브러시 선택
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
				// 펜 선택
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

				// 사용한 브러시 리소스를 해제
				DeleteObject(B_Face);
				DeleteObject(B_Mouth);
				DeleteObject(B_NoseWhite);
				DeleteObject(B_NoseBlack);
				DeleteObject(B_EyeBlack);
				DeleteObject(B_EyeWhite);
				DeleteObject(B_Beard);
			}
		}

		// 도형의 종류가 Ryan이라면
		if (Shape == S_Ryan) {
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
			// 브러시 선택
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
			// 펜 선택
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
			// 브러시 선택
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
			// 브러시 선택
			SelectObject(hdc, R_Nose);

			// 라이언의 코에 해당하는 좌표값을 저장할 변수 선언 및 좌표값 할당
			RECT R_LeftNose = { centerPoint.x - centerX / 5, centerPoint.y + 10, centerPoint.x, centerPoint.y + centerY / 5 + 10 };
			RECT R_RightNose = { centerPoint.x, centerPoint.y + 10, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 + 10 };

			// 라이언의 코 부분을 Ellipse 함수를 이용해서 그리기
			Ellipse(hdc, R_LeftNose.left, R_LeftNose.top, R_LeftNose.right, R_LeftNose.bottom);
			Ellipse(hdc, R_RightNose.left, R_RightNose.top, R_RightNose.right, R_RightNose.bottom);

			// 사용한 브러시 리소스를 해제
			DeleteObject(R_Skin);
			DeleteObject(R_Eyebrow);
			DeleteObject(R_Eye);
			DeleteObject(R_Nose);
		}

		// 리소스 해제
		DeleteObject(hBrushDrawing);
		DeleteObject(hPenDrawing);

		// 리소스 해제
		DeleteObject(hBrushBackground);
		DeleteObject(hBrushBox);
		DeleteObject(hPenBox);

		EndPaint(hwnd, &ps);
	}
	break;

	// 배경값을 설정
	case WM_ERASEBKGND:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect((HDC)wParam, &rect, hBrush);
		DeleteObject(hBrush);  // 브러시 리소스를 해제합니다.
		return 1;  // 배경을 지웠음을 나타냅니다.
	}
	break;

	// 버튼(윈도우)을 생성
	case WM_CREATE:
	{
		// 첫 번째 버튼
		hButton1 = CreateWindow(
			TEXT("button"), // 버튼 클래스
			TEXT("Box"), // 버튼 텍스트
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
			8 + 8, // x 위치: 박스 왼쪽 마진 + 내부 마진
			8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
			140, // 버튼 너비
			64, // 버튼 높이
			hwnd, // 부모 윈도우
			(HMENU)1, // 버튼 ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// 두 번째 버튼
		hButton2 = CreateWindow(
			TEXT("button"), // 버튼 클래스
			TEXT("Circle"), // 버튼 텍스트
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
			8 + 8 + 140 + 16, // x 위치: 박스 왼쪽 마진 + 내부 마진
			8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
			140, // 버튼 너비
			64, // 버튼 높이
			hwnd, // 부모 윈도우
			(HMENU)2, // 버튼 ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// 세 번째 버튼
		hButton3 = CreateWindow(
			TEXT("button"), // 버튼 클래스
			TEXT("Bonobono"), // 버튼 텍스트
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
			8 + 8 + (140 + 16) * 2, // x 위치: 박스 왼쪽 마진 + 내부 마진
			8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
			140, // 버튼 너비
			64, // 버튼 높이
			hwnd, // 부모 윈도우
			(HMENU)3, // 버튼 ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// 네 번째 버튼
		hButton4 = CreateWindow(
			TEXT("button"), // 버튼 클래스
			TEXT("Ryan"), // 버튼 텍스트
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
			8 + 8 + (140 + 16) * 3, // x 위치: 박스 왼쪽 마진 + 내부 마진
			8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
			140, // 버튼 너비
			64, // 버튼 높이
			hwnd, // 부모 윈도우
			(HMENU)4, // 버튼 ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		// 다섯 번째 버튼
		hButton5 = CreateWindow(
			TEXT("button"), // 버튼 클래스
			TEXT("Cube"), // 버튼 텍스트
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, // 스타일
			8 + 8 + (140 + 16) * 4, // x 위치: 박스 왼쪽 마진 + 내부 마진
			8 + 8, // y 위치: 박스 상단 마진 + 내부 마진
			140, // 버튼 너비
			64, // 버튼 높이
			hwnd, // 부모 윈도우
			(HMENU)5, // 버튼 ID
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
	}
	break;

	// 마우스 포인터의 모양을 변경
	case WM_SETCURSOR:
	{
		// 커서의 위치를 가져옵니다.
		POINT pt;
		GetCursorPos(&pt);
		// 해당 위치를 클라이언트 영역의 좌표로 변환합니다.
		ScreenToClient(hwnd, &pt);
		// 드로잉 영역 내에 커서가 있는지 확인합니다.
		if (PtInRect(&drawing_area, pt))
		{
			// 드로잉 영역 안에 있으면 커서를 크로스로 변경합니다.
			SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
		else
		{
			// 드로잉 영역 밖에 있으면 기본 커서를 사용합니다.
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return TRUE; // 메시지가 처리되었음을 나타냅니다.
	}
	break;

	// 윈도우가 종료된경우
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	// 해당사항이 없는 경우
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
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("곰돌이"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.

	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, NULL, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	// 종료 메시지 보내기
	return (int)msg.wParam;

}