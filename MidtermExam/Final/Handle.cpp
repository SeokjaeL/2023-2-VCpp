#include "Handle.h"
#include "Common.h"

// 마우스 이동 핸들러
void HandleMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseLButtonPressed, BOOL& isMouseRButtonPressed, POINT& startPoint, POINT& endPoint, RECT& Box, RECT& Circle, POINT& m_startPoint, POINT& m_endPoint, POINT& startPointSaved, POINT& endPointSaved, POINT& distance) {
	// 도형의 종류가 Circle이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Circle && isMouseLButtonPressed) {
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// 반지름은 두 방향 중 작은 값으로 설정
		int radius = min(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y)); 

		// 중심의 x 좌표와 y좌표 설정
		int centerX = (startPoint.x + endPoint.x) / 2;
		int centerY = (startPoint.y + endPoint.y) / 2;

		// 원의 좌표값 계산
		Circle.left = centerX - radius;
		Circle.top = centerY - radius;
		Circle.right = centerX + radius;
		Circle.bottom = centerY + radius;

		// 화면을 갱신하여 원을 그리기
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

			// 화면을 갱신하여 원을 그리기
			InvalidateRect(hwnd, &drawing_area, TRUE);
		}
	}

	// 도형의 종류가 Box, Cube이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Box && isMouseLButtonPressed || Shape == S_Cube && isMouseLButtonPressed) {
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

		// 화면을 갱신하여 사각형을 그리기
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}

	// 도형의 종류가 Ryan이고 마우스 왼쪽 버튼이 눌린 경우
	if (Shape == S_Ryan && isMouseLButtonPressed) {
		// 마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
		endPoint = { LOWORD(lParam), HIWORD(lParam) };

		// 화면을 갱신하여 Ryan을 그리기
		InvalidateRect(hwnd, &drawing_area, TRUE);
	}
}

// 마우스 완쪽 버튼 눌림 핸들러
void HandleLeftButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, POINT& startPoint, POINT& endPoint, BOOL& isMouseLButtonPressed, int& Shape, const RECT& drawing_area) {
	// 좌표값을 가져와서 시작 좌표값에 할당
	startPoint = { LOWORD(lParam), HIWORD(lParam) };
	endPoint = startPoint;

	// 도형의 종류가 Circle, Box, Ryan인 경우에만 처리
	if (Shape == S_Circle || Shape == S_Box || Shape == S_Ryan || Shape == S_Cube) {
		// 시작점이 드로잉 영역 안에 있다면
		if (PtInRect(&drawing_area, startPoint)) {
			// 체크 변수의 값을 TRUE로 설정
			isMouseLButtonPressed = TRUE;
		}
	}
}

// 마우스 오른쪽 버튼 눌림 핸들러
void HandleRightButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam, RECT& drawing_area, int& Shape, BOOL& isMouseRButtonPressed, POINT& startPointSaved, POINT& endPointSaved, POINT& endPoint, POINT& m_startPoint, RECT& Box, RECT& Circle) {
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
	if (Shape == S_Box) {
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