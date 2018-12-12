#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("TimerText2");
LPCSTR lpszTextList[26];
int g_nY = 100;
int g_nDisplayPosition = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;

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

    switch (iMessage)
    {
    case WM_CREATE:
        lpszTextList[0] = (LPCSTR)TEXT("A");
        lpszTextList[1] = (LPCSTR)TEXT("AB");
        lpszTextList[2] = (LPCSTR)TEXT("ABC");
        lpszTextList[3] = (LPCSTR)TEXT("ABCD");
        lpszTextList[4] = (LPCSTR)TEXT("ABCDE");
        lpszTextList[5] = (LPCSTR)TEXT("ABCDEF");
        lpszTextList[6] = (LPCSTR)TEXT("ABCDEFG");
        lpszTextList[7] = (LPCSTR)TEXT("ABCDEFGH");
        lpszTextList[8] = (LPCSTR)TEXT("ABCDEFGHI");
        lpszTextList[9] = (LPCSTR)TEXT("ABCDEFGHIJ");
        lpszTextList[10] = (LPCSTR)TEXT("ABCDEFGHIJK");
        lpszTextList[11] = (LPCSTR)TEXT("ABCDEFGHIJKL");
        lpszTextList[12] = (LPCSTR)TEXT("ABCDEFGHIJKLM");
        lpszTextList[13] = (LPCSTR)TEXT("ABCDEFGHIJKLMN");
        lpszTextList[14] = (LPCSTR)TEXT("ABCDEFGHIJKLMNO");
        lpszTextList[15] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOP");
        lpszTextList[16] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQ");
        lpszTextList[17] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQR");
        lpszTextList[18] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRS");
        lpszTextList[19] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRST");
        lpszTextList[20] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTU");
        lpszTextList[21] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTUV");
        lpszTextList[22] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTUVW");
        lpszTextList[23] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTUVWX");
        lpszTextList[24] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTUVWXY");
        lpszTextList[25] = (LPCSTR)TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        SetTimer(hWnd, 1, 2000, NULL);
        SetTimer(hWnd, 2, 10, NULL);
        return 0;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            g_nY = 100;
            g_nDisplayPosition = ++g_nDisplayPosition % (sizeof(lpszTextList) / sizeof(lpszTextList[0]));
            break;
        case 2:
            if (g_nY <= 10) break;
            g_nY -= 1;
            if (g_nY <= 10) g_nY = 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 10, g_nY, lpszTextList[g_nDisplayPosition], strlen(lpszTextList[g_nDisplayPosition]));
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}