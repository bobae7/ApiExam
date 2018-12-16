#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCSTR lpszClass = (LPCSTR)TEXT("OldObject");

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
    hWndMain = hWnd;
    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return (int)Message.wParam;
}

void TestResource(BOOL bUnSel, BOOL bDelete, int num)
{
    HDC hdc;
    HPEN hPen, OldPen;
    int i;
    TCHAR str[256];

    hdc = GetDC(hWndMain);
    for (i = 0; i < num; i++)
    {
        hPen = CreatePen(PS_SOLID, rand() % 5 + 1, RGB(rand() % 256, rand() % 256, rand() % 256));
        OldPen = (HPEN)SelectObject(hdc, hPen);
        MoveToEx(hdc, rand() % 1400, rand() % 600 + 40, NULL);
        LineTo(hdc, rand() % 1400, rand() % 600 + 40);
        if (bUnSel) SelectObject(hdc, OldPen);
        if (bDelete) DeleteObject(hPen);
        wsprintf(str, TEXT("%d"), i);
        SetWindowText(hWndMain, str);
    }
    ReleaseDC(hWndMain, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    TCHAR *Mes = (TCHAR *)TEXT("1:정상적인 경우, 2:선택 해제없이 삭제만, 3,삭재하지 않음");

    switch (iMessage)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case '1':
            TestResource(TRUE, TRUE, 100000);
            break;
        case '2':
            TestResource(FALSE, TRUE, 100000);
            break;
        case '3':
            TestResource(FALSE, FALSE, 100000);
            break;
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}