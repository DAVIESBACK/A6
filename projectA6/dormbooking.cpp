#include "dormbooking.h"

const int ID_USERNAME = 1;
const int ID_PASSWORD = 2;
const int ID_LOGIN = 3;
const int ID_CREATE_ACCOUNT = 4;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hUsername, hPassword, hLogin, hCreateAccount;
    switch (uMsg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("Username:"), WS_VISIBLE | WS_CHILD, 50, 50, 100, 25, hwnd, NULL, NULL, NULL);
        hUsername = CreateWindow(_T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 200, 25, hwnd, (HMENU)ID_USERNAME, NULL, NULL);

        CreateWindow(_T("STATIC"), _T("Password:"), WS_VISIBLE | WS_CHILD, 50, 100, 100, 25, hwnd, NULL, NULL, NULL);
        hPassword = CreateWindow(_T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 100, 200, 25, hwnd, (HMENU)ID_PASSWORD, NULL, NULL);

        hLogin = CreateWindow(_T("BUTTON"), _T("Login"), WS_VISIBLE | WS_CHILD, 100, 150, 100, 30, hwnd, (HMENU)ID_LOGIN, NULL, NULL);
        hCreateAccount = CreateWindow(_T("BUTTON"), _T("Create Account"), WS_VISIBLE | WS_CHILD, 210, 150, 140, 30, hwnd, (HMENU)ID_CREATE_ACCOUNT, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_LOGIN) {
            MessageBox(hwnd, _T("Redirecting to Login..."), _T("Login"), MB_OK);
        }
        else if (LOWORD(wParam) == ID_CREATE_ACCOUNT) {
            MessageBox(hwnd, _T("Redirecting to Create Account..."), _T("Create Account"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void CreateDormBookingWindow(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("DormBookingWindow");
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(wc.lpszClassName, _T("Dormitory Booking"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 400, 250, NULL, NULL, hInstance, NULL);
    if (!hwnd) return;

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
