#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("SimplePaint");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_VREDRAW | CS_HREDRAW;
    RegisterClass(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return (int)Message.wParam;
}

enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 };
HWND r1, r2, r3, r4, r5, r6;
int Thick = 1;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HPEN MyPen, OldPen;
    static int x;
    static int y;
    static BOOL bNowDraw = FALSE;

    switch (iMessage)
    {
    case WM_CREATE:
        CreateWindow(TEXT("button"), TEXT("Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);
        CreateWindow(TEXT("button"), TEXT("Thick"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 5, 120, 110, hWnd, (HMENU)1, g_hInst, NULL);
        r1 = CreateWindow(TEXT("button"), TEXT("Black"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 15, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
        r2 = CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 15, 50, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);
        r3 = CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 15, 80, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL);
        r4 = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 155, 20, 100, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL);
        r5 = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 155, 50, 100, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL);
        r6 = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 155, 80, 100, 30, hWnd, (HMENU)ID_R6, g_hInst, NULL);
        CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
        CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_R1:
            Color = RGB(0, 0, 0);
            break;
        case ID_R2:
            Color = RGB(255, 0, 0);
            break;
        case ID_R3:
            Color = RGB(0, 0, 255);
            break;
        case ID_R4:
            Thick = 1;
            break;
        case ID_R5:
            Thick = 3;
            break;
        case ID_R6:
            Thick = 5;
            break;
        }
        return 0;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        bNowDraw = TRUE;
        return 0;
    case WM_MOUSEMOVE:
        if (bNowDraw == TRUE)
        {
            hdc = GetDC(hWnd);
            MyPen = CreatePen(PS_SOLID, Thick, Color);
            OldPen = (HPEN)SelectObject(hdc, MyPen);
            MoveToEx(hdc, x, y, NULL);
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            LineTo(hdc, x, y);
            SelectObject(hdc, OldPen);
            DeleteObject(MyPen);
            ReleaseDC(hWnd, hdc);
        }
        return 0;
    case WM_LBUTTONUP:
        bNowDraw = FALSE;
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}