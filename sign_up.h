#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window {
public:
    Window(HINSTANCE hInstance, LPCSTR className, LPCSTR windowTitle);
    ~Window();
    
    bool Create(int width, int height);
    void Show(int nCmdShow);
    void MessageLoop();
    
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HINSTANCE hInstance;
    LPCSTR className;
    LPCSTR windowTitle;
    HWND hwnd;
};

#endif
