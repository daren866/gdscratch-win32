#include <windows.h>
#include <commctrl.h>
#include <string>

// 全局变量
HWND hMainWnd;
HWND hRenderArea;
HWND hFileEdit;
HWND hRenderButton;
HWND hLoadButton;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // 创建渲染区域
            hRenderArea = CreateWindowExW(
                WS_EX_CLIENTEDGE,
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
            hFileEdit = CreateWindowExW(
                WS_EX_CLIENTEDGE,
                L"EDIT",
                L"C:\\xxx\\xxx.sb3",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_READONLY,
                600, 50, 250, 25,
                hWnd,
                (HMENU)2,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            // 创建文件选择按钮
            hLoadButton = CreateWindowExW(
                0,
                L"BUTTON",
                L"选择文件",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                600, 100, 120, 30,
                hWnd,
                (HMENU)4,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            // 创建渲染按钮
            hRenderButton = CreateWindowExW(
                0,
                L"BUTTON",
                L"渲染",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                740, 100, 120, 30,
                hWnd,
                (HMENU)3,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 3:  // 渲染按钮
                    MessageBoxW(hWnd, L"渲染功能", L"提示", MB_OK);
                    break;
                case 4:  // 选择文件按钮
                    // 显示文件选择对话框
                    OPENFILENAMEW ofn;
                    wchar_t szFileName[MAX_PATH] = L"";
                    // 注意：宽字符版本的文件过滤器写法
                    wchar_t szFilter[] = L"Scratch 文件 (*.sb3)\0*.sb3\0所有文件 (*.*)\0*.*\0";
                    
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = szFilter;
                    ofn.lpstrFile = szFileName;
                    ofn.nMaxFile = MAX_PATH;
                    ofn.lpstrTitle = L"选择 Scratch 文件";
                    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
                    
                    if (GetOpenFileNameW(&ofn)) {
                        // 更新文件路径到编辑框
                        SetWindowTextW(hFileEdit, szFileName);
                    }
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
    WNDCLASSEXW wcex; // 使用 W 版本
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
    wcex.lpszClassName = L"GDScratchWindowClass"; // 使用 L 前缀
    wcex.hIconSm = LoadIconW(wcex.hInstance, IDI_APPLICATION);
    return RegisterClassExW(&wcex); // 使用 W 版本
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
    hMainWnd = CreateWindowExW(
        0,
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
