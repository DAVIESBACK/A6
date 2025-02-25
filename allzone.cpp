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

void ShowZoneSelectWindow(HINSTANCE hInstance, HWND parent) {
    MessageBox(parent, "Inside ShowZoneSelectWindow", "Debug", MB_OK);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = ZoneSelectProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ZoneSelectWindow";
    
    if (!RegisterClass(&wc)) {
        MessageBox(parent, "Failed to register ZoneSelectWindow!", "Error", MB_OK | MB_ICONERROR);
        return;
    }
    
    HWND hZoneWnd = CreateWindow("ZoneSelectWindow", "Select a Dormitory Zone", WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
                                 NULL, NULL, hInstance, NULL);  // **แก้ไข parent เป็น NULL**
    
    if (!hZoneWnd) {
        MessageBox(parent, "Failed to create ZoneSelectWindow!", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(hZoneWnd, SW_SHOW);
}

LRESULT CALLBACK ZoneSelectProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "Zone 1", WS_VISIBLE | WS_CHILD,
                         50, 50, 200, 30, hwnd, (HMENU)ID_ZONE1, NULL, NULL);
            CreateWindow("BUTTON", "Zone 2", WS_VISIBLE | WS_CHILD,
                         50, 90, 200, 30, hwnd, (HMENU)ID_ZONE2, NULL, NULL);
            CreateWindow("BUTTON", "Zone 3", WS_VISIBLE | WS_CHILD,
                         50, 130, 200, 30, hwnd, (HMENU)ID_ZONE3, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_ZONE1) {
                ShowZone1Images(hwnd, GetModuleHandle(NULL));
            } else if (LOWORD(wParam) == ID_ZONE2) {
                ShowZone2Images(hwnd, GetModuleHandle(NULL));
            } else if (LOWORD(wParam) == ID_ZONE3) {
                ShowZone3Images(hwnd, GetModuleHandle(NULL));
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

void OnLoginSuccess(HWND parent) {
    MessageBox(parent, "OnLoginSuccess Called", "Debug", MB_OK);
    ShowZoneSelectWindow(GetModuleHandle(NULL), parent);
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

void ShowZone1Images(HWND hwnd, HINSTANCE hInst) {  
    WNDCLASS wc1 = {0};
    wc1.hInstance = hInst;
    wc1.lpszClassName = "Zone1ImagesClass";

    RegisterClass(&wc1);

    HWND hwndImages = CreateWindow("Zone1ImagesClass", "Zone 1 Images", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   100, 100, 400, 400, hwnd, NULL, hInst, NULL);

    if (!hwndImages) {
        MessageBox(NULL, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
    }
}



LRESULT CALLBACK Zone1Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hBitmap5;
    
    switch (msg) {
        case WM_CREATE:
            hBitmap1 = (HBITMAP)LoadImage(NULL, "room1.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap2 = (HBITMAP)LoadImage(NULL, "room2.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap3 = (HBITMAP)LoadImage(NULL, "room3.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap4 = (HBITMAP)LoadImage(NULL, "room4.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap5 = (HBITMAP)LoadImage(NULL, "room5.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         50, 50, 100, 100, hwnd, (HMENU)ID_IMAGE1, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         170, 50, 100, 100, hwnd, (HMENU)ID_IMAGE2, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         290, 50, 100, 100, hwnd, (HMENU)ID_IMAGE3, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         410, 50, 100, 100, hwnd, (HMENU)ID_IMAGE4, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         530, 50, 100, 100, hwnd, (HMENU)ID_IMAGE5, NULL, NULL);
            break;
        
        case WM_DESTROY:
            DeleteObject(hBitmap1);
            DeleteObject(hBitmap2);
            DeleteObject(hBitmap3);
            DeleteObject(hBitmap4);
            DeleteObject(hBitmap5);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowZone2Images(HWND hwnd, HINSTANCE hInst) {  
    WNDCLASS wc1 = {0};
    wc1.hInstance = hInst;
    wc1.lpszClassName = "Zone2ImagesClass";

    RegisterClass(&wc1);

    HWND hwndImages = CreateWindow("Zone2ImagesClass", "Zone 2 Images", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   100, 100, 400, 400, hwnd, NULL, hInst, NULL);

    if (!hwndImages) {
        MessageBox(NULL, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
    }
}



LRESULT CALLBACK Zone2Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hBitmap5;
    
    switch (msg) {
        case WM_CREATE:
            hBitmap1 = (HBITMAP)LoadImage(NULL, "room1.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap2 = (HBITMAP)LoadImage(NULL, "room2.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap3 = (HBITMAP)LoadImage(NULL, "room3.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap4 = (HBITMAP)LoadImage(NULL, "room4.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap5 = (HBITMAP)LoadImage(NULL, "room5.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         50, 50, 100, 100, hwnd, (HMENU)ID_IMAGE6, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         170, 50, 100, 100, hwnd, (HMENU)ID_IMAGE7, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         290, 50, 100, 100, hwnd, (HMENU)ID_IMAGE8, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         410, 50, 100, 100, hwnd, (HMENU)ID_IMAGE9, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         530, 50, 100, 100, hwnd, (HMENU)ID_IMAGE10, NULL, NULL);
            break;
        
        case WM_DESTROY:
            DeleteObject(hBitmap1);
            DeleteObject(hBitmap2);
            DeleteObject(hBitmap3);
            DeleteObject(hBitmap4);
            DeleteObject(hBitmap5);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void ShowZone3Images(HWND hwnd, HINSTANCE hInst) {  
    WNDCLASS wc1 = {0};
    wc1.hInstance = hInst;
    wc1.lpszClassName = "Zone3ImagesClass";

    RegisterClass(&wc1);

    HWND hwndImages = CreateWindow("Zone3ImagesClass", "Zone 3 Images", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   100, 100, 400, 400, hwnd, NULL, hInst, NULL);

    if (!hwndImages) {
        MessageBox(NULL, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
    }
}



LRESULT CALLBACK Zone3Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4, hBitmap5;
    
    switch (msg) {
        case WM_CREATE:
            hBitmap1 = (HBITMAP)LoadImage(NULL, "room1.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap2 = (HBITMAP)LoadImage(NULL, "room2.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap3 = (HBITMAP)LoadImage(NULL, "room3.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap4 = (HBITMAP)LoadImage(NULL, "room4.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            hBitmap5 = (HBITMAP)LoadImage(NULL, "room5.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         50, 50, 100, 100, hwnd, (HMENU)ID_IMAGE11, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         170, 50, 100, 100, hwnd, (HMENU)ID_IMAGE12, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         290, 50, 100, 100, hwnd, (HMENU)ID_IMAGE13, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         410, 50, 100, 100, hwnd, (HMENU)ID_IMAGE14, NULL, NULL);
            CreateWindow("STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
                         530, 50, 100, 100, hwnd, (HMENU)ID_IMAGE15, NULL, NULL);
            break;
        
        case WM_DESTROY:
            DeleteObject(hBitmap1);
            DeleteObject(hBitmap2);
            DeleteObject(hBitmap3);
            DeleteObject(hBitmap4);
            DeleteObject(hBitmap5);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
