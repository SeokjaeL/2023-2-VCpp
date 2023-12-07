#include "Util.h"

// 창의 최소 및 최대 크기 설정
void SetMinMaxWindowSizes(HWND hWnd, MINMAXINFO* minMaxInfo, int minWidth, int minHeight) {
	// 윈도우 영역 크기 정의
	RECT rect = { 0, 0, minWidth, minHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// MINMAXINFO 구조체를 사용하여 창 크기 제한 설정
	minMaxInfo->ptMinTrackSize.x = width; // 최소 너비
	minMaxInfo->ptMinTrackSize.y = height; // 최소 높이
	minMaxInfo->ptMaxTrackSize.x = width; // 최대 너비
	minMaxInfo->ptMaxTrackSize.y = height; // 최대 높이
}

// 커서 변경
void UpdateCursor(HWND hwnd, const RECT& drawing_area) {
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
}

