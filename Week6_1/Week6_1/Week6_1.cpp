//#define DEBUG
#ifdef UNICODE
#ifdef DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#else
#ifdef DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#endif

#include <windows.h>

RECT rect_user = { 10, 10, 15, 15 };		//	사용자 사각형
RECT rect_target = { 50, 50, 150, 150 };	//	타겟 사각형
const wchar_t* text = L"Crash!!!";			//	충돌 메시지

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//	창의 최소 및 최대 크기에 대한 정보 제어
	case WM_GETMINMAXINFO:
	{
		// MINMAXINFO 구조체 포인터를 선언 후, lParam(창의 크기 제한 정보)에 저장된 값을 MINMAXINFO 구조체 포인터로 캐스팅한 값으로 초기화 
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		//	MINMAXINFO 구조체 멤버들을 설정하여 창의 최소 크기와 최대 크기를 지정
		minMaxInfo->ptMinTrackSize.x = 800; // 최소 너비
		minMaxInfo->ptMinTrackSize.y = 600; // 최소 높이
		minMaxInfo->ptMaxTrackSize.x = 800; // 최대 너비
		minMaxInfo->ptMaxTrackSize.y = 600; // 최대 높이
	}
	break;
	//	키보드의 키가 눌린경우
	case WM_KEYDOWN:
		//	왼쪽 방향키인 경우
		if (wParam == VK_LEFT)
		{
			//	사용자 사각형의 왼쪽 상단 x좌표와 오른쪽 하단 x좌표 1감소(왼쪽으로 이동)후 WM_PAINT 메시지 발생
			rect_user.left -= 1;
			rect_user.right -= 1;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		//	오른쪽 방향키인 경우
		else if (wParam == VK_RIGHT)
		{
			//	사용자 사각형의 왼쪽 상단 x좌표와 오른쪽 하단 x좌표 1증가(오른쪽으로 이동)후 WM_PAINT 메시지 발생
			rect_user.left += 1;
			rect_user.right += 1;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		//	위쪽 방향키인 경우
		else if (wParam == VK_UP)
		{
			//	사용자 사각형의 왼쪽 상단 y좌표와 오른쪽 하단 y좌표 1감소(위로 이동)후 WM_PAINT 메시지 발생
			rect_user.top -= 1;
			rect_user.bottom -= 1;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		//	아래쪽 방향키인 경우
		else if (wParam == VK_DOWN)
		{
			//	사용자 사각형의 왼쪽 상단 y좌표와 오른쪽 하단 y좌표 1증가(위로 이동)후 WM_PAINT 메시지 발생
			rect_user.top += 1;
			rect_user.bottom += 1;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
	{
		//	페인트 구조체 생성 및 디바이스 컨텍스트 가져오기
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		//	브러시 생성
		HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));

		//	화면 지우기
		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, hBrush_eraser);

		//	타겟 사각형과 사용자 사각형이 충돌한 경우
		if (PtInRect(&rect_target, { rect_user.left,rect_user.top }) || PtInRect(&rect_target, { rect_user.right,rect_user.bottom })) {
			//	충돌 메시지 출력
			TextOut(hdc, 10, 10, text, lstrlen(text));
		}
		//	타겟 사각형 그리기
		SelectObject(hdc, hBrush_target);
		Rectangle(hdc, rect_target.left, rect_target.top, rect_target.right, rect_target.bottom);

		//	사용자 사각형 그리기
		SelectObject(hdc, hBrush_user);
		Rectangle(hdc, rect_user.left, rect_user.top, rect_user.right, rect_user.bottom);

		//브러시 삭제와 얻어온 디바이스 컨텍스트 반환
		DeleteObject(hBrush_user);
		DeleteObject(hBrush_target);
		DeleteObject(hBrush_eraser);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201907011 이석재"),
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

	// 메시지 처리.
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);
		}
		//if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// 메시지 해석해줘.
		//	TranslateMessage(&msg);
		//	// 메시지를 처리해야할 곳에 전달해줘.
		//	DispatchMessage(&msg);
		//} // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		//else{}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//종료 메시지 보내기
	return (int)msg.wParam;

}