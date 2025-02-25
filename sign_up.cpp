#include <windows.h>
#include <string>
#include <fstream>
#include <vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LoginProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SignupProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ZoneSelectProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone1Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone2Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone3Proc(HWND, UINT, WPARAM, LPARAM);
void CreateLoginUI(HWND);
void CreateSignupUI(HWND);
void ShowLoginWindow(HINSTANCE, HWND);
void ShowSignupWindow(HINSTANCE, HWND);
void ShowZoneSelectWindow(HINSTANCE, HWND);
bool AuthenticateUser(const std::string&, const std::string&);
bool IsUserExists(const std::string&);
void RegisterUser(const std::string&, const std::string&);
void OnLoginSuccess(HWND);
void ShowZone1Images(HWND hwnd, HINSTANCE hInst);
void ShowZone2Images(HWND hwnd, HINSTANCE hInst);
void ShowZone3Images(HWND hwnd, HINSTANCE hInst);


#define ID_LOGIN 1
#define ID_SIGNUP 2
#define ID_EXIT 3
#define ID_USERNAME 4
#define ID_PASSWORD 5
#define ID_SUBMIT_LOGIN 6
#define ID_SUBMIT_SIGNUP 7
#define ID_CONFIRM_PASSWORD 8
#define ID_ZONE1 9
#define ID_ZONE2 10
#define ID_ZONE3 11
#define ID_IMAGE1 201
#define ID_IMAGE2 202
#define ID_IMAGE3 203
#define ID_IMAGE4 204
#define ID_IMAGE5 205
#define ID_IMAGE6 206
#define ID_IMAGE7 207
#define ID_IMAGE8 208
#define ID_IMAGE9 209
#define ID_IMAGE10 210
#define ID_IMAGE11 211
#define ID_IMAGE12 212
#define ID_IMAGE13 213
#define ID_IMAGE14 214
#define ID_IMAGE15 215


HWND hUsername, hPassword, hConfirmPassword, hMainWnd;
std::string loggedInUser;


void ShowSignupWindow(HINSTANCE hInstance, HWND parent) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = SignupProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SignupWindow";
    RegisterClass(&wc);
    
    HWND hSignupWnd = CreateWindow("SignupWindow", "Sign Up", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 300, 250,
                                   parent, NULL, hInstance, NULL);
    ShowWindow(hSignupWnd, SW_SHOW);
}

LRESULT CALLBACK SignupProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
            CreateWindow("STATIC", "Confirm Password:", WS_VISIBLE | WS_CHILD,
                         20, 100, 120, 25, hwnd, NULL, NULL, NULL);
            hConfirmPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                         110, 100, 150, 25, hwnd, (HMENU)ID_CONFIRM_PASSWORD, NULL, NULL);
            CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD,
                         20, 140, 80, 30, hwnd, (HMENU)ID_SUBMIT_SIGNUP, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_SUBMIT_SIGNUP) {
                DestroyWindow(hwnd);
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
