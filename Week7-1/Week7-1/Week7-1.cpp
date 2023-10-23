#include <windows.h>

#define ID_BUTTON1 1
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_BUTTON4 4

HWND hButton1, hButton2, hButton3, hButton4;

POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };

int shape = 0;
bool isDrawing = false;


// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            shape = 1;
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            shape = 2;
        }
        else if (LOWORD(wParam) == 3) {
            // 세 번째 버튼 클릭
            shape = 3;
        }
        else if (LOWORD(wParam) == 4) {
            // 네 번째 버튼 클릭
            shape = 4;
        }
        break;
    case WM_LBUTTONDOWN:
        isDrawing = true;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;

    case WM_MOUSEMOVE: {
        if (isDrawing) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, FALSE);
        }}
        break;

    case WM_LBUTTONUP: 
        isDrawing = false;
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rect;
        GetClientRect(hWnd, &rect);
        HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
        FillRect(hdc, &rect, whiteBrush);

        // Create a pink brush
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 105, 180));
        SelectObject(hdc, hBrush);

        if (shape == ID_BUTTON1) {
            POINT triangle[3] = { startPoint, {startPoint.x - (endPoint.x - startPoint.x), endPoint.y}, endPoint };
            Polygon(hdc, triangle, 3);
        }

        else if (shape == ID_BUTTON2) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }

        else if (shape == ID_BUTTON3) {
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }

        else if (shape == ID_BUTTON4) {
            MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
            LineTo(hdc, endPoint.x, endPoint.y);
        }

        DeleteObject(hBrush);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 프로그램 진입점
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    HWND hWnd;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Triangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 100, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Rectangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 100, 100, 60, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 180, 100, 60, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Line", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 260, 100, 60, hWnd, (HMENU)4, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
