#include <windows.h>
#include <math.h>

#define ID_BUTTON1 1
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_BUTTON4 4
#define ID_BUTTON5 5


HWND hButton1, hButton2, hButton3, hButton4, hButton5;

POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };

int shape = 0;
HBRUSH hBrush;
bool isDrawing = false;
bool isMoving = false;
float radius = 0.0f; // 원의 반지름

struct Point3D {
    float x, y, z;
};

struct Point2D {
    float x, y;
};

Point2D Project(Point3D point) {
    Point2D projected;
    float fov = 500; // 가정한 초점 거리
    projected.x = point.x * (fov / point.z) + startPoint.x;
    projected.y = -point.y * (fov / point.z) + startPoint.y; // y축이 상하 반전되므로 부호 변경
    return projected;
}

void clear_Screen(HWND hWnd, HDC hdc) {
        RECT rect;
        GetClientRect(hWnd, &rect);
        HBRUSH hBackgroundColor = CreateSolidBrush(RGB(255, 240, 200));
        FillRect(hdc, &rect, hBackgroundColor);
}


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
        else if (LOWORD(wParam) == 5) {
            // 다섯 번째 버튼 클릭
            shape = 5;
        }

        break;
    case WM_LBUTTONDOWN:
        isDrawing = true;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        break;


    case WM_LBUTTONUP:
        isDrawing = false;
        break;

    case WM_MOUSEMOVE: {
        if (isDrawing) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, FALSE);
        }}
                     break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        clear_Screen(hWnd, hdc);

        hBrush = CreateSolidBrush(RGB(0, 255, 0));
        SelectObject(hdc, hBrush);

        if (shape == ID_BUTTON1) {
 
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }

        else if (shape == ID_BUTTON2) {
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }

        else if (shape == ID_BUTTON3) {

        }

        else if (shape == ID_BUTTON4) {

        }

        else if (shape == ID_BUTTON5) {



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
        L"ButtonWindowClass", L"곰돌이", WS_OVERLAPPEDWINDOW,
        0, 0, 1000, 800, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        36, 20, 160, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        212, 20, 160, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        388, 20, 160, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        564, 20, 160, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        740, 20, 160, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
