#include "zone3.h"
#include <windows.h>

#define ID_BTN_HISTORY 101
#define ID_BTN_HOME 102
#define ID_BTN_LOGOUT 103
#define ID_BTN_WARISA 114
#define ID_BTN_PS 115
#define ID_BTN_BAAAN 116
#define ID_BTN_TARNTHONG 117
#define ID_BTN_THONGTARA 118

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
                case ID_BTN_WARISA:
                    MessageBox(hwnd, "Warisa Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_PS:
                    MessageBox(hwnd, "P.S. Mansion Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_BTN_BAAAN:
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

void CreateAppButtons(HWND hwnd, HINSTANCE hInstance) {
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                             OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    
    struct ButtonInfo {
        LPCSTR text;
        int id;
        HWND hWnd;
    } buttons[] = {
        {"Booking History", ID_BTN_HISTORY, NULL},
        {"Warisa Apartment", ID_BTN_WARISA, NULL},
        {"P.S. Mansion", ID_BTN_PS, NULL},
        {"Baan Tarnkam", ID_BTN_BAAAN, NULL},
        {"Tarnthong Place", ID_BTN_TARNTHONG, NULL},
        {"Thongtara Monte", ID_BTN_THONGTARA, NULL},
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
        GetDlgItem(hwnd, ID_BTN_WARISA),
        GetDlgItem(hwnd, ID_BTN_PS),
        GetDlgItem(hwnd, ID_BTN_BAAAN),
        GetDlgItem(hwnd, ID_BTN_TARNTHONG),
        GetDlgItem(hwnd, ID_BTN_THONGTARA)
    };
    
    for (int i = 0; i < 6; i++) {
        MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
    }
    
    MoveWindow(GetDlgItem(hwnd, ID_BTN_HOME), 50, height - 70, 150, 50, TRUE);
    MoveWindow(GetDlgItem(hwnd, ID_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
}