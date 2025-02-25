#include <windows.h>
#include <string>
#include <fstream>
#include <vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LoginProc(HWND, UINT, WPARAM, LPARAM);
void CreateLoginUI(HWND);
void ShowLoginWindow(HINSTANCE, HWND);


#define ID_LOGIN 1
#define ID_SIGNUP 2
#define ID_EXIT 3
#define ID_USERNAME 4
#define ID_PASSWORD 5
#define ID_SUBMIT_LOGIN 6
#define ID_SUBMIT_SIGNUP 7
#define ID_CONFIRM_PASSWORD 8

HWND hUsername, hPassword, hConfirmPassword, hMainWnd;
std::string loggedInUser;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DormBookingApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    hMainWnd = CreateWindow("DormBookingApp", "Dormitory Booking System", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);
    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD,
                         50, 100, 200, 30, hwnd, (HMENU)ID_LOGIN, NULL, NULL);
            CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD,
                         50, 150, 200, 30, hwnd, (HMENU)ID_SIGNUP, NULL, NULL);
            CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD,
                         50, 200, 200, 30, hwnd, (HMENU)ID_EXIT, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_LOGIN) {
                ShowLoginWindow(GetModuleHandle(NULL), hwnd);
            } else if (LOWORD(wParam) == ID_SIGNUP) {
                ShowSignupWindow(GetModuleHandle(NULL), hwnd);
            } else if (LOWORD(wParam) == ID_EXIT) {
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void ShowLoginWindow(HINSTANCE hInstance, HWND parent) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = LoginProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "LoginWindow";
    RegisterClass(&wc);
    
    HWND hLoginWnd = CreateWindow("LoginWindow", "Login", WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
                                  parent, NULL, hInstance, NULL);
    ShowWindow(hLoginWnd, SW_SHOW);
}

void ShowLoginWindow(HINSTANCE hInstance, HWND parent) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = LoginProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "LoginWindow";
    RegisterClass(&wc);
    
    HWND hLoginWnd = CreateWindow("LoginWindow", "Login", WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
                                  parent, NULL, hInstance, NULL);
    ShowWindow(hLoginWnd, SW_SHOW);
}

LRESULT CALLBACK LoginProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD,
                         20, 20, 80, 25, hwnd, NULL, NULL, NULL);
            hUsername = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     110, 20, 150, 25, hwnd, (HMENU)ID_USERNAME, NULL, NULL);
            CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD,
                         20, 60, 80, 25, hwnd, NULL, NULL, NULL);
            hPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                                     110, 60, 150, 25, hwnd, (HMENU)ID_PASSWORD, NULL, NULL);
            CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD,
                         110, 100, 80, 30, hwnd, (HMENU)ID_SUBMIT_LOGIN, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_SUBMIT_LOGIN) {
                char username[30], password[30];
                GetWindowText(hUsername, username, 30);
                GetWindowText(hPassword, password, 30);

                if (AuthenticateUser(username, password)) {
                    MessageBox(hwnd, "Login Successful!", "Success", MB_OK);
                    OnLoginSuccess(hwnd);
                    DestroyWindow(hwnd);
                } else {
                    MessageBox(hwnd, "Invalid username or password!", "Error", MB_OK | MB_ICONERROR);
                }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

bool AuthenticateUser(const std::string& username, const std::string& password) {
    std::ifstream file("users.txt");
    if (!file) {
        MessageBox(NULL, "Cannot open users.txt!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    std::string storedUser, storedPass;
    while (file >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == password) {
            MessageBox(NULL, "User authenticated!", "Debug", MB_OK);
            return true;
        }
    }
    
    MessageBox(NULL, "User not found!", "Debug", MB_OK);
    return false;
}