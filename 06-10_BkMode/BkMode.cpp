#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("BkMode");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevIhstance, LPSTR lpszCmdParam, int nCmdShow)
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HFONT hFont, OldFont;
    TCHAR *str = (TCHAR *)TEXT("��Ʈ Test 1234");
    HBRUSH MyBrush, OldBrush;

    switch (iMessage)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        MyBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
        OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
        Rectangle(hdc, 50, 50, 400, 200);
        SelectObject(hdc, OldBrush);
        hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
        OldFont = (HFONT)SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(255, 0, 0));
        SetBkColor(hdc, RGB(255, 255, 0));
        TextOut(hdc, 100, 100, str, lstrlen(str));
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, 100, 150, str, lstrlen(str));

        SelectObject(hdc, OldFont);
        DeleteObject(MyBrush);
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}