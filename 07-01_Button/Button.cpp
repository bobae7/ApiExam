#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("Button");

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
    switch (iMessage)
    {
    case WM_CREATE:
        CreateWindow(TEXT("button"), TEXT("Click Me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
        CreateWindow(TEXT("button"), TEXT("Me Too"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
        CreateWindow(TEXT("button"), TEXT("Close Me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 80, 100, 25, hWnd, (HMENU)2, g_hInst, NULL);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 0:
            MessageBox(hWnd, TEXT("First Button Clicked"), TEXT("Button"), MB_OK);
            break;
        case 1:
            MessageBox(hWnd, TEXT("Second Button Clicked"), TEXT("Button"), MB_OK);
            break;
        case 2:
            DestroyWindow(hWnd);
            break;
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}