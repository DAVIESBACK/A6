#include "sign_up.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window myWindow(hInstance, "MyWindowClass", "My Win32 App");

    if (!myWindow.Create(800, 600)) {
        return -1;
    }

    myWindow.Show(nCmdShow);
    myWindow.MessageLoop();
    
    return 0;
}
