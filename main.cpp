#include <windows.h>
#include <commctrl.h>
#include <string>

// 全局变量
HWND hMainWnd;
HWND hRenderArea;
HWND hFileEdit;
HWND hRenderButton;
HWND hLoadButton;

// 将 ANSI 字符串转换为宽字符串
std::wstring ToWideString(const char* str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    std::wstring wstr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str, -1, &wstr[0], len);
    return wstr;
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // 创建渲染区域
            hRenderArea = CreateWindowW(
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                10, 50, 560, 380,
                hWnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            // 创建文件编辑框
            hFileEdit = CreateWindowW(
                L"EDIT",
                L"C:\\xxx\\xxx.sb3",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                600, 50, 250, 25,
                hWnd,
                (HMENU)2,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            // 创建渲染按钮
            hRenderButton = CreateWindowW(
                L"BUTTON",
                L"渲染",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                600, 100, 120, 30,
                hWnd,
                (HMENU)3,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            // 创建加载按钮
            hLoadButton = CreateWindowW(
                L"BUTTON",
                L"加载",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                740, 100, 120, 30,
                hWnd,
                (HMENU)4,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 3:
                    MessageBoxW(hWnd, L"渲染功能", L"提示", MB_OK);
                    break;
                case 4:
                    MessageBoxW(hWnd, L"加载功能", L"提示", MB_OK);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GDScratchWindowClass";
    wcex.hIconSm = LoadIconW(wcex.hInstance, IDI_APPLICATION);
    return RegisterClassExW(&wcex);
}

// WinMain 函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 初始化公共控件库
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    MyRegisterClass(hInstance);

    // 创建主窗口
    hMainWnd = CreateWindowW(
        L"GDScratchWindowClass",
        L"舞台渲染画面",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        900, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hMainWnd) {
        return FALSE;
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
