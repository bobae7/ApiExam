#include <Windows.h>

#define ID_COMBOBOX 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("ComboBox");

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

TCHAR *Items[] = { (LPSTR)TEXT("Apple"), (LPSTR)TEXT("Orange"), (LPSTR)TEXT("Melon"), (LPSTR)TEXT("Grape"), (LPSTR)TEXT("Strawberry") };
char str[128];
HWND hCombo;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    int i;

    switch (iMessage)
    {
    case WM_CREATE:
        hCombo = CreateWindow("combobox", TEXT("Fruit"), WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
            10, 10, 100, 200,
            hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
        for (i = 0; i < 5; i++)
        {
            SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
        }
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_COMBOBOX:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
                i = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
                SetWindowText(hWnd, str);
                break;
            case CBN_EDITCHANGE:
                GetWindowText(hCombo, str, 128);
                SetWindowText(hWnd, str);
                break;
            }
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}