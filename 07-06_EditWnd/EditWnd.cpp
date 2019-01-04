#include <Windows.h>

#define ID_EDIT 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hEdit;
LPCSTR lpszClass = (LPCSTR)TEXT("EditWnd");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsstance, LPSTR lpszCmdParam, int nCmdShow)
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

int nTop = 10;
bool bShow = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    TCHAR *Mes = (TCHAR *)TEXT("왼쪽 클릭:에디트 이동, 오른쪽 클릭:보임/숨김");

    switch (iMessage)
    {
    case WM_CREATE:
        hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, nTop, 200, 25,
            hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
        SetWindowText(hEdit, TEXT("에디트도 윈도우다"));
        return 0;
    case WM_LBUTTONDOWN:
        nTop += 10;
        MoveWindow(hEdit, 10, nTop, 200, 25, true);
        return 0;
    case WM_RBUTTONDOWN:
        if (bShow)
        {
            bShow = false;
            ShowWindow(hEdit, SW_HIDE);
        }
        else
        {
            bShow = true;
            ShowWindow(hEdit, SW_SHOW);
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 200, 100, Mes, lstrlen(Mes));
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}