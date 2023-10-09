#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//	windows.h란?
// 윈도우 개발자들이 필요한 모든 매크로들, 다양한 함수들과 서브시스템에서 사용되는 모든 데이터 타입들
// 그리고 윈도우 API의 함수들을 위한 정의를 포함하는 헤더파일
#include <windows.h>

//	좌표값을 저장할 전역변수 선언
POINT startPoint = { 0 };		//	사각형 시작점의 좌표값
POINT endPoint = { 0 };			//	사각형 끝점의 좌표값
POINT m_startPoint = { 0 };		//	사각형 이동이 시작된 좌표값
POINT m_endPoint = { 0 };		//	사각형 이동이 끝난 좌표값
POINT distance = { 0 };			//	마우스 이동 거리
POINT startPointSaved = { 0 };	//	기존 사각형의 시작점의 좌표값
POINT endPointSaved = { 0 };	//	기존 사각형의 끝점의 좌표값

//	마우스 버튼이 눌린 상태인지 체크하는 전역변수 선언
int isMouseLButtonPressed = 0;	//	마우스 왼쪽 버튼이 눌린 상태인지 체크
int isMouseRButtonPressed = 0;	//	마우스 오른쪽 버튼이 눌린 상태인지 체크

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

	//	마우스 왼쪽 버튼을 누른 경우
	case WM_LBUTTONDOWN:
	{
		//	마우스 왼쪽 버튼을 눌렀을 때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 시작점의 좌표값으로 설정
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);

		//	마우스 왼쪽 버튼이 눌린 상태인지 체크하는 변수의 값을 1(true)로 변경
		isMouseLButtonPressed = 1;
	}
	break;

	//	마우스 오른쪽 버튼을 누른 경우
	case WM_RBUTTONDOWN:
	{
		//	마우스 오른쪽 버튼을 눌렀을 때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 시작된 좌표값으로 설정
		m_startPoint.x = LOWORD(lParam);
		m_startPoint.y = HIWORD(lParam);

		//	마우스 오른쪽 버튼을 기존에 만들어진 사각형 영역 안에서 눌렀다면
		if (m_startPoint.x > startPoint.x && m_startPoint.x < endPoint.x && m_startPoint.y > startPoint.y && m_startPoint.y < endPoint.y)
		{
			//	기존 사각형 시작점과 끝점의 좌표값을 Saved 변수에 저장
			startPointSaved = startPoint;
			endPointSaved = endPoint;

			//	마우스 오른쪽 버튼이 눌린 상태인지 체크하는 변수의 값을 1(true)로 변경
			isMouseRButtonPressed = 1;
		}
	}
	break;

	//	마우스 왼쪽 버튼을 뗀 경우
	case WM_LBUTTONUP:
	{
		//	마우스 왼쪽 버튼이 눌린 상태인지 체크하는 변수의 값을 0(false)로 변경
		isMouseLButtonPressed = 0;

	}
	break;

	//	마우스 오른쪽 버튼을 뗀 경우
	case WM_RBUTTONUP:
	{
		//	마우스 오른쪽 버튼이 눌린 상태인지 체크하는 변수의 값을 0(false)로 변경
		isMouseRButtonPressed = 0;
	}
	break;

	//	마우스가 움직이는 경우
	case WM_MOUSEMOVE:
	{
		// 마우스 왼쪽 버튼을 누른 상태로 드래그를 하는 경우
		if (isMouseLButtonPressed)
		{
			//	마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 끝점의 좌표값으로 설정
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			//	해석: 윈도우 클라이언트 영역 전체를 업데이트하기 위해 WM_PAINT 메시지 발생(윈도우를 다시 그리도록 요청)
			//	첫번째 매개변수: 어떤 윈도우에 대한 업데이트를 수행?
			//	두번째 매개변수: 업데이트하려는 영역의 좌표?(NULL일 경우 전체 클라이언트 영역)
			//	세번째 매개변수: 업데이트하려는 영역의 배경 삭제 여부?(TRUE일 경우 삭제)
			InvalidateRect(hwnd, NULL, TRUE);
		}
		// 마우스 오른쪽 버튼을 누른 상태로 드래그를 하는 경우(*단 만들어진 사각형 영역 안에서 눌렀을 경우)
		if (isMouseRButtonPressed)
		{
			//	마우스를 움직였을때 좌표값을 LOWORD(lParam), HIWORD(lParam)함수를 통해 가져와서 사각형 이동이 끝난 좌표값으로 설정
			m_endPoint.x = LOWORD(lParam);
			m_endPoint.y = HIWORD(lParam);

			//	사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
			distance.x = m_endPoint.x - m_startPoint.x;
			distance.y = m_endPoint.y - m_startPoint.y;

			// 사각형의 시작점과 끝점의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
			startPoint.x = startPointSaved.x + distance.x;
			startPoint.y = startPointSaved.y + distance.y;
			endPoint.x = endPointSaved.x + distance.x;
			endPoint.y = endPointSaved.y + distance.y;

			//	해석: 윈도우 클라이언트 영역 전체를 업데이트하기 위해 WM_PAINT 메시지 발생(윈도우를 다시 그리도록 요청)
			//	첫번째 매개변수: 어떤 윈도우에 대한 업데이트를 수행?
			//	두번째 매개변수: 업데이트하려는 영역의 좌표?(NULL일 경우 전체 클라이언트 영역)
			//	세번째 매개변수: 업데이트하려는 영역의 배경 삭제 여부?(TRUE일 경우 삭제)
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		//	BeginPaint(hwnd, &ps), EndPaint(hdc, &ps)와 GetDC(hwnd), ReleaseDC(hwnd) 함수의 차이?
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hwnd, &ps);
		HDC hdc = GetDC(hwnd);															// hwnd에 해당하는 디바이스 컨텍스트를 얻어와 rect에 저장

		//	마우스의 왼쪽 버튼이나 오른쪽 버튼이 눌린 상태인 경우
		if (isMouseLButtonPressed || isMouseRButtonPressed)
		{
			//	화면 지우기
			RECT rect;																	//	화면을 지울 영역의 좌표를 저장할 변수 선언
			GetClientRect(hwnd, &rect);													//	윈도우 클라이언트 영역을 얻어 rect에 저장
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));							//	화면을 지움

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));							//	브러시를 생성하고 색상은 핑크색(단색)으로 지정
			SelectObject(hdc, hBrush);													//	그리기에 사용할 브러시를 선택
			Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);			//	시작점과 끝점을 이용하여 직사각형을 그림
			DeleteObject(hBrush);														//	생성한 브러시를 삭제
		}
		ReleaseDC(hwnd, hdc);															//	얻어온 디바이스 컨텍스트를 반환
		//EndPaint(hdc, &ps);

	}
	break;

	//	창을 닫았을 경우
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

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
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

	//종료 메시지 보내기
	return (int)msg.wParam;

}