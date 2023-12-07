#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

#include <windows.h>
#include "DrawObject.h"
#include "CreateInterface.h"
#include "Util.h"
#include "Common.h"
#include "Handle.h"

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
		SetMinMaxWindowSizes(hwnd, (MINMAXINFO*)lParam, 800, 480);
	}
	break;

	// Ű�� ���� ������ ���
	case WM_KEYDOWN:
	{
		// ���࿡ ������ ������ ���뺸���̰�, �����̽�Ű�� ���� ���¶��
		if (Shape == S_Bonobono && wParam == VK_SPACE) {
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
			startPoint = { 0 };							// startPoint�� ��ǥ���� 0���� �ʱ�ȭ
			endPoint = { 0 };							// endPoint�� ��ǥ���� 0���� �ʱ�ȭ
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
		HandleLeftButtonDown(hwnd, wParam, lParam, startPoint, endPoint, isMouseLButtonPressed, Shape, drawing_area);
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
		HandleRightButtonDown(hwnd, wParam, lParam, drawing_area, Shape, isMouseRButtonPressed, startPointSaved, endPointSaved, endPoint, m_startPoint, Box, Circle);
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
		HandleMouseMove(hwnd, wParam, lParam, drawing_area, Shape, isMouseLButtonPressed, isMouseRButtonPressed, startPoint, endPoint, Box, Circle, m_startPoint, m_endPoint, startPointSaved, endPointSaved, distance);
	}
	break;

	case WM_PAINT:
	{
		// ����Ʈ ����ü ����� ������ �ڵ鷯 �޾ƿ���
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		DrawInterface(hwnd, hdc, drawing_area);

		// ������ ������ Box���
		if (Shape == S_Box) {
			DrawBox(hdc, Box);
		}

		// ������ ������ Circle�̶��
		if (Shape == S_Circle) {
			DrawCircle(hdc, Circle);
		}

		// ������ ������ Bonobono���
		if (Shape == S_Bonobono) {
			DrawBonobono(hwnd, hdc, isSpaceButtonPressed);
		}

		// ������ ������ Ryan�̶��
		if (Shape == S_Ryan) {
			DrawRyan(hwnd, hdc, startPoint, endPoint);
		}

		// ������ ������ Ryan�̶��
		if (Shape == S_Cube) {
			DrawCube(hwnd, hdc, startPoint, endPoint);
		}

		EndPaint(hwnd, &ps);
	}
	break;

	// ��ư(������)�� ����
	case WM_CREATE:
	{
		CreateButtons(hwnd, ((LPCREATESTRUCT)lParam)->hInstance);
	}
	break;

	// ���콺 �������� ����� ����
	case WM_SETCURSOR:
	{
		UpdateCursor(hwnd, drawing_area);
		return TRUE; // �޽����� ó���Ǿ����� ��Ÿ���ϴ�.
	}
	break;

	// �����찡 ����Ȱ��
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	// �ش������ ���� ���
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
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