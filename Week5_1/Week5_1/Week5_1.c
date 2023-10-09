#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//	windows.h��?
// ������ �����ڵ��� �ʿ��� ��� ��ũ�ε�, �پ��� �Լ���� ����ý��ۿ��� ���Ǵ� ��� ������ Ÿ�Ե�
// �׸��� ������ API�� �Լ����� ���� ���Ǹ� �����ϴ� �������
#include <windows.h>

//	��ǥ���� ������ �������� ����
POINT startPoint = { 0 };		//	�簢�� �������� ��ǥ��
POINT endPoint = { 0 };			//	�簢�� ������ ��ǥ��
POINT m_startPoint = { 0 };		//	�簢�� �̵��� ���۵� ��ǥ��
POINT m_endPoint = { 0 };		//	�簢�� �̵��� ���� ��ǥ��
POINT distance = { 0 };			//	���콺 �̵� �Ÿ�
POINT startPointSaved = { 0 };	//	���� �簢���� �������� ��ǥ��
POINT endPointSaved = { 0 };	//	���� �簢���� ������ ��ǥ��

//	���콺 ��ư�� ���� �������� üũ�ϴ� �������� ����
int isMouseLButtonPressed = 0;	//	���콺 ���� ��ư�� ���� �������� üũ
int isMouseRButtonPressed = 0;	//	���콺 ������ ��ư�� ���� �������� üũ

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	//	â�� �ּ� �� �ִ� ũ�⿡ ���� ���� ����
	case WM_GETMINMAXINFO:
	{
		// MINMAXINFO ����ü �����͸� ���� ��, lParam(â�� ũ�� ���� ����)�� ����� ���� MINMAXINFO ����ü �����ͷ� ĳ������ ������ �ʱ�ȭ 
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		//	MINMAXINFO ����ü ������� �����Ͽ� â�� �ּ� ũ��� �ִ� ũ�⸦ ����
		minMaxInfo->ptMinTrackSize.x = 800; // �ּ� �ʺ�
		minMaxInfo->ptMinTrackSize.y = 600; // �ּ� ����
		minMaxInfo->ptMaxTrackSize.x = 800; // �ִ� �ʺ�
		minMaxInfo->ptMaxTrackSize.y = 600; // �ִ� ����
	}
	break;

	//	���콺 ���� ��ư�� ���� ���
	case WM_LBUTTONDOWN:
	{
		//	���콺 ���� ��ư�� ������ �� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� �������� ��ǥ������ ����
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);

		//	���콺 ���� ��ư�� ���� �������� üũ�ϴ� ������ ���� 1(true)�� ����
		isMouseLButtonPressed = 1;
	}
	break;

	//	���콺 ������ ��ư�� ���� ���
	case WM_RBUTTONDOWN:
	{
		//	���콺 ������ ��ư�� ������ �� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� �̵��� ���۵� ��ǥ������ ����
		m_startPoint.x = LOWORD(lParam);
		m_startPoint.y = HIWORD(lParam);

		//	���콺 ������ ��ư�� ������ ������� �簢�� ���� �ȿ��� �����ٸ�
		if (m_startPoint.x > startPoint.x && m_startPoint.x < endPoint.x && m_startPoint.y > startPoint.y && m_startPoint.y < endPoint.y)
		{
			//	���� �簢�� �������� ������ ��ǥ���� Saved ������ ����
			startPointSaved = startPoint;
			endPointSaved = endPoint;

			//	���콺 ������ ��ư�� ���� �������� üũ�ϴ� ������ ���� 1(true)�� ����
			isMouseRButtonPressed = 1;
		}
	}
	break;

	//	���콺 ���� ��ư�� �� ���
	case WM_LBUTTONUP:
	{
		//	���콺 ���� ��ư�� ���� �������� üũ�ϴ� ������ ���� 0(false)�� ����
		isMouseLButtonPressed = 0;

	}
	break;

	//	���콺 ������ ��ư�� �� ���
	case WM_RBUTTONUP:
	{
		//	���콺 ������ ��ư�� ���� �������� üũ�ϴ� ������ ���� 0(false)�� ����
		isMouseRButtonPressed = 0;
	}
	break;

	//	���콺�� �����̴� ���
	case WM_MOUSEMOVE:
	{
		// ���콺 ���� ��ư�� ���� ���·� �巡�׸� �ϴ� ���
		if (isMouseLButtonPressed)
		{
			//	���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� ������ ��ǥ������ ����
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			//	�ؼ�: ������ Ŭ���̾�Ʈ ���� ��ü�� ������Ʈ�ϱ� ���� WM_PAINT �޽��� �߻�(�����츦 �ٽ� �׸����� ��û)
			//	ù��° �Ű�����: � �����쿡 ���� ������Ʈ�� ����?
			//	�ι�° �Ű�����: ������Ʈ�Ϸ��� ������ ��ǥ?(NULL�� ��� ��ü Ŭ���̾�Ʈ ����)
			//	����° �Ű�����: ������Ʈ�Ϸ��� ������ ��� ���� ����?(TRUE�� ��� ����)
			InvalidateRect(hwnd, NULL, TRUE);
		}
		// ���콺 ������ ��ư�� ���� ���·� �巡�׸� �ϴ� ���(*�� ������� �簢�� ���� �ȿ��� ������ ���)
		if (isMouseRButtonPressed)
		{
			//	���콺�� ���������� ��ǥ���� LOWORD(lParam), HIWORD(lParam)�Լ��� ���� �����ͼ� �簢�� �̵��� ���� ��ǥ������ ����
			m_endPoint.x = LOWORD(lParam);
			m_endPoint.y = HIWORD(lParam);

			//	�簢�� �̵��� ���� ��ǥ���� �簢�� �̵��� ���۵� ��ǥ���� ���� ���� ���콺�� �̵� �Ÿ��� ���
			distance.x = m_endPoint.x - m_startPoint.x;
			distance.y = m_endPoint.y - m_startPoint.y;

			// �簢���� �������� ������ ��ǥ���� ������ �����س��� ��ǥ���� ���콺�� �̵��Ÿ� ��ŭ�� ���� ��ǥ������ ����
			startPoint.x = startPointSaved.x + distance.x;
			startPoint.y = startPointSaved.y + distance.y;
			endPoint.x = endPointSaved.x + distance.x;
			endPoint.y = endPointSaved.y + distance.y;

			//	�ؼ�: ������ Ŭ���̾�Ʈ ���� ��ü�� ������Ʈ�ϱ� ���� WM_PAINT �޽��� �߻�(�����츦 �ٽ� �׸����� ��û)
			//	ù��° �Ű�����: � �����쿡 ���� ������Ʈ�� ����?
			//	�ι�° �Ű�����: ������Ʈ�Ϸ��� ������ ��ǥ?(NULL�� ��� ��ü Ŭ���̾�Ʈ ����)
			//	����° �Ű�����: ������Ʈ�Ϸ��� ������ ��� ���� ����?(TRUE�� ��� ����)
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		//	BeginPaint(hwnd, &ps), EndPaint(hdc, &ps)�� GetDC(hwnd), ReleaseDC(hwnd) �Լ��� ����?
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hwnd, &ps);
		HDC hdc = GetDC(hwnd);															// hwnd�� �ش��ϴ� ����̽� ���ؽ�Ʈ�� ���� rect�� ����

		//	���콺�� ���� ��ư�̳� ������ ��ư�� ���� ������ ���
		if (isMouseLButtonPressed || isMouseRButtonPressed)
		{
			//	ȭ�� �����
			RECT rect;																	//	ȭ���� ���� ������ ��ǥ�� ������ ���� ����
			GetClientRect(hwnd, &rect);													//	������ Ŭ���̾�Ʈ ������ ��� rect�� ����
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));							//	ȭ���� ����

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));							//	�귯�ø� �����ϰ� ������ ��ũ��(�ܻ�)���� ����
			SelectObject(hdc, hBrush);													//	�׸��⿡ ����� �귯�ø� ����
			Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);			//	�������� ������ �̿��Ͽ� ���簢���� �׸�
			DeleteObject(hBrush);														//	������ �귯�ø� ����
		}
		ReleaseDC(hwnd, hdc);															//	���� ����̽� ���ؽ�Ʈ�� ��ȯ
		//EndPaint(hdc, &ps);

	}
	break;

	//	â�� �ݾ��� ���
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
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201907011 �̼���"),
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
		if (GetMessage(&msg, hwnd, 0, 0))
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

	//���� �޽��� ������
	return (int)msg.wParam;

}