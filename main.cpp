#include "test.h"
#include <windows.h> // 包含 Windows API 头文件

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 调用你原来的测试函数（如果不需要可以删掉这行
    // 无
    // 显示 GUI 弹窗
    // 参数1: 窗口父句柄 (NULL表示没有父窗口)
    // 参数2: 弹窗内容
    // 参数3: 弹窗标题
    // 参数4: 弹窗类型 (MB_OK 表示只显示一个"确定"按钮)
    MessageBox(NULL, TEXT("helloworld"), TEXT("helloworld"), MB_OK);

    return 0;
}
