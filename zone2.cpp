#include "zone2.h"
#include <windows.h>

#define ID_BTN_HISTORY 101
#define ID_BTN_HOME 102
#define ID_BTN_LOGOUT 103
#define ID_BTN_PP 109
#define ID_BTN_GL 110
#define ID_BTN_PJ 111
#define ID_BTN_KD 112
#define ID_BTN_BAAN 113

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateAppButtons(HWND hwnd, HINSTANCE hInstance);
void ResizeButtons(HWND hwnd, int width, int height);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "HotelApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindow("HotelApp", "Hotel Management", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE, 
                             CW_USEDEFAULT, CW_USEDEFAULT, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                             NULL, NULL, hInstance, NULL);
    
    if (!hwnd) return 0;
    
    ShowWindow(hwnd, nCmdShow);
    
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateAppButtons(hwnd, ((LPCREATESTRUCT)lParam)->hInstance);
            break;
        case WM_SIZE:
            ResizeButtons(hwnd, LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_PP:
                    MessageBox(hwnd, "Phufa Place Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_GL:
                    MessageBox(hwnd, "The Greenery Landmark Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_PJ:
                    MessageBox(hwnd, "Pojai Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_KD:
                    MessageBox(hwnd, "Kiang Doi Place Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_BAAN:
                    MessageBox(hwnd, "Baan Pranee (Jed Yod) Information", "Info", MB_OK | MB_ICONINFORMATION);
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

void CreateAppButtons(HWND hwnd, HINSTANCE hInstance) {
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                             OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    
    struct ButtonInfo {
        LPCSTR text;
        int id;
        HWND hWnd;
    } buttons[] = {
        {"Booking History", ID_BTN_HISTORY, NULL},
        {"Phufa Place Apartment", ID_BTN_PP, NULL},
        {"The Greenery Landmark", ID_BTN_GL, NULL},
        {"Pojai Apartment", ID_BTN_PJ, NULL},
        {"Kiang Doi Place", ID_BTN_KD, NULL},
        {"Baan Pranee (Jed Yod)", ID_BTN_BAAN, NULL},
        {"Home", ID_BTN_HOME, NULL},
        {"Log Out", ID_BTN_LOGOUT, NULL}
    };

    for (int i = 0; i < 8; i++) {
        buttons[i].hWnd = CreateWindow("BUTTON", buttons[i].text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
                                       0, 0, 0, 0, hwnd, (HMENU)(UINT_PTR)buttons[i].id, hInstance, NULL);
        SendMessage(buttons[i].hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}

void ResizeButtons(HWND hwnd, int width, int height) {
    int buttonWidth = width / 6;
    int buttonHeight = 50;
    int yOffset = 10;
    
    HWND btns[] = {
        GetDlgItem(hwnd, ID_BTN_HISTORY),
        GetDlgItem(hwnd, ID_BTN_PP),
        GetDlgItem(hwnd, ID_BTN_GL),
        GetDlgItem(hwnd, ID_BTN_PJ),
        GetDlgItem(hwnd, ID_BTN_KD),
        GetDlgItem(hwnd, ID_BTN_BAAN)
    };
    
    for (int i = 0; i < 6; i++) {
        MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
    }
    
    MoveWindow(GetDlgItem(hwnd, ID_BTN_HOME), 50, height - 70, 150, 50, TRUE);
    MoveWindow(GetDlgItem(hwnd, ID_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
}