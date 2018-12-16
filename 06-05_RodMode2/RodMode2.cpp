#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("OldObject");
int g_nShape = 0;   // 0: 자유곡선, 1: 선, 2: 원, 3: 사각형

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
    WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    static int sx, sy, oldx, oldy;
    static BOOL bNowDraw = FALSE;
    HBRUSH OldBrush;
    HPEN MyPen, OldPen;
    HDC hdc;

    switch(iMessage)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_SHAPE_FREELINE:
            g_nShape = 0;
            break;
        case ID_SHAPE_LINE:
            g_nShape = 1;
            break;
        case ID_SHAPE_CIRCLE:
            g_nShape = 2;
            break;
        case ID_SHAPE_SQUARE:
            g_nShape = 3;
            break;
        }
        return 0;
    case WM_LBUTTONDOWN:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        oldx = sx;
        oldy = sy;
        bNowDraw = TRUE;
        return 0;
    case WM_MOUSEMOVE:
        if (bNowDraw)
        {
            hdc = GetDC(hWnd);
            switch (g_nShape)
            {
            case 0:         // 자유 곡선
                sx = LOWORD(lParam);
                sy = HIWORD(lParam);
                MoveToEx(hdc, sx, sy, NULL);
                LineTo(hdc, oldx, oldy);
                oldx = sx;
                oldy = sy;
                break;
            case 1:         // 선
                SetROP2(hdc, R2_NOT);
                MoveToEx(hdc, sx, sy, NULL);
                LineTo(hdc, oldx, oldy);
                oldx = LOWORD(lParam);
                oldy = HIWORD(lParam);
                MoveToEx(hdc, sx, sy, NULL);
                LineTo(hdc, oldx, oldy);
                break;
            case 2:         // 원
                OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
                MyPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                OldPen = (HPEN)SelectObject(hdc, MyPen);
                SetROP2(hdc, R2_NOT);
                Ellipse(hdc, sx, sy, oldx, oldy);
                oldx = LOWORD(lParam);
                oldy = HIWORD(lParam);
                Ellipse(hdc, sx, sy, oldx, oldy);
                SelectObject(hdc, SelectObject);
                DeleteObject(SelectObject(hdc, OldPen));
                break;
            case 3:         // 사각형
                SelectObject(hdc, GetStockObject(NULL_BRUSH));
                MyPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                OldPen = (HPEN)SelectObject(hdc, MyPen);
                SetROP2(hdc, R2_NOT);
                Rectangle(hdc, sx, sy, oldx, oldy);
                oldx = LOWORD(lParam);
                oldy = HIWORD(lParam);
                Rectangle(hdc, sx, sy, oldx, oldy);
                DeleteObject(SelectObject(hdc, OldPen));
                break;
            }
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