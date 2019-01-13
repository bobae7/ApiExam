#include <Windows.h>

#define ID_LISTBOX 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = (LPCSTR)TEXT("ListBoxExam");

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
HWND hList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    int i;
    TCHAR str[128];

    switch (iMessage) {
    case WM_CREATE:
        hList = CreateWindow(TEXT("listbox"), TEXT("Fruit"), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
            10, 10, 100, 200,
            hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
        for (i = 0; i < 5; ++i)
            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_LISTBOX:
            switch (HIWORD(wParam)) {
            case LBN_SELCHANGE:
                i = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
                SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
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