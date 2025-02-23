#include "zone1.h"
#include <windows.h>

#define ID_BTN_HISTORY 101
#define ID_BTN_HOME 102
#define ID_BTN_LOGOUT 103
#define ID_BTN_UNL 104
#define ID_BTN_HH 105
#define ID_BTN_BAN 106
#define ID_BTN_ML 107
#define ID_BTN_KG 108

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
                case ID_BTN_UNL:
                    MessageBox(hwnd, "Uniloft Chiangmai Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_HH:
                    MessageBox(hwnd, "Home & Hills Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_BAN:
                    MessageBox(hwnd, "Baan Im Rak Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_ML:
                    MessageBox(hwnd, "Sanguanmalee Mansion Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_KG:
                    MessageBox(hwnd, "Kai Golden Place Information", "Info", MB_OK | MB_ICONINFORMATION);
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
        {"Uniloft Chiangmai", ID_BTN_UNL, NULL},
        {"Home and Hills", ID_BTN_HH, NULL},
        {"Baan Im Rak", ID_BTN_BAN, NULL},
        {"Sanguanmalee Mansion Place", ID_BTN_ML, NULL},
        {"Kai Golden", ID_BTN_KG, NULL},
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
        GetDlgItem(hwnd, ID_BTN_UNL),
        GetDlgItem(hwnd, ID_BTN_HH),
        GetDlgItem(hwnd, ID_BTN_BAN),
        GetDlgItem(hwnd, ID_BTN_ML),
        GetDlgItem(hwnd, ID_BTN_KG)
    };
    
    for (int i = 0; i < 6; i++) {
        MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
    }
    
    MoveWindow(GetDlgItem(hwnd, ID_BTN_HOME), 50, height - 70, 150, 50, TRUE);
    MoveWindow(GetDlgItem(hwnd, ID_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
}