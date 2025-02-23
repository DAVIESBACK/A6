#include <windows.h>

#define ID_BTN_HISTORY 101
#define ID_BTN_HOME 102
#define ID_BTN_LOGOUT 103
#define ID_BTN_NARISA 104
#define ID_BTN_PS 105
#define ID_BTN_BAAN 106
#define ID_BTN_TARNTHONG 107
#define ID_BTN_THONGTARA 108

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            // Set background color
            SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(240, 240, 240)));
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_NARISA:
                    MessageBox(hwnd, "Narisa Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_PS:
                    MessageBox(hwnd, "P.S. Mansion Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_BAAN:
                    MessageBox(hwnd, "Baan Tarnkam Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_TARNTHONG:
                    MessageBox(hwnd, "Tarnthong Place Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_THONGTARA:
                    MessageBox(hwnd, "Thongtara Monte Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_HISTORY:
                    MessageBox(hwnd, "Booking History", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_HOME:
                    MessageBox(hwnd, "Home", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_LOGOUT:
                    MessageBox(hwnd, "Logging Out...", "Info", MB_OK | MB_ICONWARNING);
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "HotelApp";
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindow("HotelApp", "Hotel Management", WS_OVERLAPPEDWINDOW, 
                             CW_USEDEFAULT, CW_USEDEFAULT, 600, 500,
                             NULL, NULL, hInstance, NULL);
    
    if (!hwnd) return 0;
    
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, 
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    
    HWND buttons[] = {
        CreateWindow("BUTTON", "Booking History", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 20, 20, 180, 40, hwnd, (HMENU)ID_BTN_HISTORY, hInstance, NULL),
        CreateWindow("BUTTON", "Narisa Apartment", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 50, 80, 180, 40, hwnd, (HMENU)ID_BTN_NARISA, hInstance, NULL),
        CreateWindow("BUTTON", "P.S. Mansion", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 250, 80, 180, 40, hwnd, (HMENU)ID_BTN_PS, hInstance, NULL),
        CreateWindow("BUTTON", "Baan Tarnkam", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 140, 180, 40, hwnd, (HMENU)ID_BTN_BAAN, hInstance, NULL),
        CreateWindow("BUTTON", "Tarnthong Place Apartment", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 50, 200, 250, 40, hwnd, (HMENU)ID_BTN_TARNTHONG, hInstance, NULL),
        CreateWindow("BUTTON", "Thongtara Monte", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 320, 200, 180, 40, hwnd, (HMENU)ID_BTN_THONGTARA, hInstance, NULL),
        CreateWindow("BUTTON", "Home", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 20, 400, 120, 40, hwnd, (HMENU)ID_BTN_HOME, hInstance, NULL),
        CreateWindow("BUTTON", "Log Out", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 450, 400, 120, 40, hwnd, (HMENU)ID_BTN_LOGOUT, hInstance, NULL)
    };
    
    for (int i = 0; i < 8; i++) {
        SendMessage(buttons[i], WM_SETFONT, (WPARAM)hFont, TRUE);
    }
    
    ShowWindow(hwnd, nCmdShow);
    
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    DeleteObject(hFont);
    return 0;
}
