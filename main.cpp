#include <windows.h>
#include <iostream>

// ====== Constants สำหรับ Main Menu ======
#define ID_LOGIN_BUTTON         1001
#define ID_SIGNUP_BUTTON        1002
#define ID_BOOKING_BUTTON       1003
#define ID_ZONE_SELECT_BUTTON   1004
#define ID_EXIT_BUTTON          1005

// ====== Constants สำหรับ Zone Selection Window ======
#define ID_ZONE1_BUTTON         9001
#define ID_ZONE2_BUTTON         9002
#define ID_ZONE3_BUTTON         9003
#define ID_ZONELOGOUT_BUTTON    9004

// ====== Constants สำหรับ Zone 1 Window ======
#define ID_Z1_BTN_HISTORY       101
#define ID_Z1_BTN_HOME          102
#define ID_Z1_BTN_LOGOUT        103
#define ID_Z1_BTN_UNL           104
#define ID_Z1_BTN_HH            105
#define ID_Z1_BTN_BAN           106
#define ID_Z1_BTN_ML            107
#define ID_Z1_BTN_KG            108

// ====== Constants สำหรับ Zone 2 Window ======
#define ID_Z2_BTN_HISTORY       201
#define ID_Z2_BTN_HOME          202
#define ID_Z2_BTN_LOGOUT        203
#define ID_Z2_BTN_PP            209
#define ID_Z2_BTN_GL            210
#define ID_Z2_BTN_PJ            211
#define ID_Z2_BTN_KD            212
#define ID_Z2_BTN_BAAN          213

// ====== Constants สำหรับ Zone 3 Window ======
#define ID_Z3_BTN_HISTORY       301
#define ID_Z3_BTN_HOME          302
#define ID_Z3_BTN_LOGOUT        303
#define ID_Z3_BTN_WARISA        314
#define ID_Z3_BTN_PS            315
#define ID_Z3_BTN_BAAAN         316
#define ID_Z3_BTN_TARNTHONG     317
#define ID_Z3_BTN_THONGTARA     318

// ----- Forward Declarations -----
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ZoneSelectWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone1WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone2WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone3WndProc(HWND, UINT, WPARAM, LPARAM);

void ShowZoneSelectWindow(HINSTANCE hInst, HWND parent);
void ShowZone1Window(HINSTANCE hInst, HWND parent);
void ShowZone2Window(HINSTANCE hInst, HWND parent);
void ShowZone3Window(HINSTANCE hInst, HWND parent);

// ====== Main Entry Point ======
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    // ลงทะเบียนคลาสหน้าต่างหลัก (Main Menu)
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = MainWndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "MainMenuWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&wc);
    
    HWND hwndMain = CreateWindow("MainMenuWindow", "Main Menu", 
                                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
                                 NULL, NULL, hInst, NULL);
    if (!hwndMain)
        return 0;
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// ====== Main Menu Window Procedure ======
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)ID_LOGIN_BUTTON, NULL, NULL);
            CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)ID_SIGNUP_BUTTON, NULL, NULL);
            CreateWindow("BUTTON", "Booking Window", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)ID_BOOKING_BUTTON, NULL, NULL);
            CreateWindow("BUTTON", "Zone Selection", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)ID_ZONE_SELECT_BUTTON, NULL, NULL);
            CreateWindow("BUTTON", "E
                xit", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)ID_EXIT_BUTTON, NULL, NULL);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_ZONE_SELECT_BUTTON:
                    ShowZoneSelectWindow(GetModuleHandle(NULL), hwnd);
                    break;
                case ID_EXIT_BUTTON:
                    PostQuitMessage(0);
                    break;
                // ส่วนของ Login, Sign Up, Booking Window ให้เติมโค้ดตามต้องการ
                default:
                    break;
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

// ====== Zone Selection Window Procedure ======
LRESULT CALLBACK ZoneSelectWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            CreateWindow("BUTTON", "Zone 1", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)ID_ZONE1_BUTTON, GetModuleHandle(NULL), NULL);
            CreateWindow("BUTTON", "Zone 2", WS_VISIBLE | WS_CHILD, 50, 110, 150, 40, hwnd, (HMENU)ID_ZONE2_BUTTON, GetModuleHandle(NULL), NULL);
            CreateWindow("BUTTON", "Zone 3", WS_VISIBLE | WS_CHILD, 50, 170, 150, 40, hwnd, (HMENU)ID_ZONE3_BUTTON, GetModuleHandle(NULL), NULL);
            CreateWindow("BUTTON", "Logout", WS_VISIBLE | WS_CHILD, 50, 230, 150, 40, hwnd, (HMENU)ID_ZONELOGOUT_BUTTON, GetModuleHandle(NULL), NULL);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_ZONE1_BUTTON:
                    ShowZone1Window(GetModuleHandle(NULL), hwnd);
                    break;
                case ID_ZONE2_BUTTON:
                    ShowZone2Window(GetModuleHandle(NULL), hwnd);
                    break;
                case ID_ZONE3_BUTTON:
                    ShowZone3Window(GetModuleHandle(NULL), hwnd);
                    break;
                case ID_ZONELOGOUT_BUTTON:
                    DestroyWindow(hwnd);
                    break;
            }
            break;
        case WM_DESTROY:
            // ไม่ต้อง PostQuitMessage เพราะ Main Menu ยังรันอยู่
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowZoneSelectWindow(HINSTANCE hInst, HWND parent)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = ZoneSelectWndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "ZoneSelectWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&wc);
    
    CreateWindow("ZoneSelectWindow", "Select a Zone", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                 parent, NULL, hInst, NULL);
}

// ====== Zone 1 Window ======
LRESULT CALLBACK Zone1WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                                      CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
            struct ButtonInfo { LPCSTR text; int id; } buttons[] = {
                {"Booking History", ID_Z1_BTN_HISTORY},
                {"Uniloft Chiangmai", ID_Z1_BTN_UNL},
                {"Home & Hills", ID_Z1_BTN_HH},
                {"Baan Im Rak", ID_Z1_BTN_BAN},
                {"Sanguanmalee Mansion", ID_Z1_BTN_ML},
                {"Kai Golden", ID_Z1_BTN_KG},
                {"Home", ID_Z1_BTN_HOME},
                {"Log Out", ID_Z1_BTN_LOGOUT}
            };
            for (int i = 0; i < 8; i++) {
                HWND hBtn = CreateWindow("BUTTON", buttons[i].text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                         0, 0, 0, 0, hwnd, (HMENU)buttons[i].id, hInst, NULL);
                SendMessage(hBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
        }
        break;
        case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            int buttonWidth = width / 6;
            int buttonHeight = 50;
            int yOffset = 10;
            HWND btns[6] = {
                GetDlgItem(hwnd, ID_Z1_BTN_HISTORY),
                GetDlgItem(hwnd, ID_Z1_BTN_UNL),
                GetDlgItem(hwnd, ID_Z1_BTN_HH),
                GetDlgItem(hwnd, ID_Z1_BTN_BAN),
                GetDlgItem(hwnd, ID_Z1_BTN_ML),
                GetDlgItem(hwnd, ID_Z1_BTN_KG)
            };
            for (int i = 0; i < 6; i++) {
                MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
            }
            MoveWindow(GetDlgItem(hwnd, ID_Z1_BTN_HOME), 50, height - 70, 150, 50, TRUE);
            MoveWindow(GetDlgItem(hwnd, ID_Z1_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
        }
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_Z1_BTN_UNL:
                    MessageBox(hwnd, "Uniloft Chiangmai Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_HH:
                    MessageBox(hwnd, "Home & Hills Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_BAN:
                    MessageBox(hwnd, "Baan Im Rak Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_ML:
                    MessageBox(hwnd, "Sanguanmalee Mansion Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_KG:
                    MessageBox(hwnd, "Kai Golden Place Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_HISTORY:
                    MessageBox(hwnd, "Booking History", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_HOME:
                    MessageBox(hwnd, "Home", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z1_BTN_LOGOUT:
                    MessageBox(hwnd, "Logging Out...", "Info", MB_OK | MB_ICONWARNING);
                    DestroyWindow(hwnd);
                    break;
            }
            break;
        case WM_DESTROY:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowZone1Window(HINSTANCE hInst, HWND parent)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = Zone1WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "Zone1Window";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&wc);
    CreateWindow("Zone1Window", "Zone 1", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                 parent, NULL, hInst, NULL);
}

// ====== Zone 2 Window ======
LRESULT CALLBACK Zone2WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                                      CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
            struct ButtonInfo { LPCSTR text; int id; } buttons[] = {
                {"Booking History", ID_Z2_BTN_HISTORY},
                {"Phufa Place Apartment", ID_Z2_BTN_PP},
                {"The Greenery Landmark", ID_Z2_BTN_GL},
                {"Pojai Apartment", ID_Z2_BTN_PJ},
                {"Kiang Doi Place", ID_Z2_BTN_KD},
                {"Baan Pranee (Jed Yod)", ID_Z2_BTN_BAAN},
                {"Home", ID_Z2_BTN_HOME},
                {"Log Out", ID_Z2_BTN_LOGOUT}
            };
            for (int i = 0; i < 8; i++) {
                HWND hBtn = CreateWindow("BUTTON", buttons[i].text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                         0, 0, 0, 0, hwnd, (HMENU)buttons[i].id, hInst, NULL);
                SendMessage(hBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
        }
        break;
        case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            int buttonWidth = width / 6;
            int buttonHeight = 50;
            int yOffset = 10;
            HWND btns[6] = {
                GetDlgItem(hwnd, ID_Z2_BTN_HISTORY),
                GetDlgItem(hwnd, ID_Z2_BTN_PP),
                GetDlgItem(hwnd, ID_Z2_BTN_GL),
                GetDlgItem(hwnd, ID_Z2_BTN_PJ),
                GetDlgItem(hwnd, ID_Z2_BTN_KD),
                GetDlgItem(hwnd, ID_Z2_BTN_BAAN)
            };
            for (int i = 0; i < 6; i++) {
                MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
            }
            MoveWindow(GetDlgItem(hwnd, ID_Z2_BTN_HOME), 50, height - 70, 150, 50, TRUE);
            MoveWindow(GetDlgItem(hwnd, ID_Z2_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
        }
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_Z2_BTN_PP:
                    MessageBox(hwnd, "Phufa Place Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_GL:
                    MessageBox(hwnd, "The Greenery Landmark Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_PJ:
                    MessageBox(hwnd, "Pojai Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_KD:
                    MessageBox(hwnd, "Kiang Doi Place Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_BAAN:
                    MessageBox(hwnd, "Baan Pranee (Jed Yod) Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_HISTORY:
                    MessageBox(hwnd, "Booking History", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_HOME:
                    MessageBox(hwnd, "Home", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z2_BTN_LOGOUT:
                    MessageBox(hwnd, "Logging Out...", "Info", MB_OK | MB_ICONWARNING);
                    DestroyWindow(hwnd);
                    break;
            }
            break;
        case WM_DESTROY:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowZone2Window(HINSTANCE hInst, HWND parent)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = Zone2WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "Zone2Window";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&wc);
    CreateWindow("Zone2Window", "Zone 2", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                 parent, NULL, hInst, NULL);
}

// ====== Zone 3 Window ======
LRESULT CALLBACK Zone3WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                                      CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
            struct ButtonInfo { LPCSTR text; int id; } buttons[] = {
                {"Booking History", ID_Z3_BTN_HISTORY},
                {"Warisa Apartment", ID_Z3_BTN_WARISA},
                {"P.S. Mansion", ID_Z3_BTN_PS},
                {"Baan Tarnkam", ID_Z3_BTN_BAAAN},
                {"Tarnthong Place", ID_Z3_BTN_TARNTHONG},
                {"Thongtara Monte", ID_Z3_BTN_THONGTARA},
                {"Home", ID_Z3_BTN_HOME},
                {"Log Out", ID_Z3_BTN_LOGOUT}
            };
            for (int i = 0; i < 8; i++) {
                HWND hBtn = CreateWindow("BUTTON", buttons[i].text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                         0, 0, 0, 0, hwnd, (HMENU)buttons[i].id, hInst, NULL);
                SendMessage(hBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
        }
        break;
        case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            int buttonWidth = width / 6;
            int buttonHeight = 50;
            int yOffset = 10;
            HWND btns[6] = {
                GetDlgItem(hwnd, ID_Z3_BTN_HISTORY),
                GetDlgItem(hwnd, ID_Z3_BTN_WARISA),
                GetDlgItem(hwnd, ID_Z3_BTN_PS),
                GetDlgItem(hwnd, ID_Z3_BTN_BAAAN),
                GetDlgItem(hwnd, ID_Z3_BTN_TARNTHONG),
                GetDlgItem(hwnd, ID_Z3_BTN_THONGTARA)
            };
            for (int i = 0; i < 6; i++) {
                MoveWindow(btns[i], i * buttonWidth, yOffset, buttonWidth, buttonHeight, TRUE);
            }
            MoveWindow(GetDlgItem(hwnd, ID_Z3_BTN_HOME), 50, height - 70, 150, 50, TRUE);
            MoveWindow(GetDlgItem(hwnd, ID_Z3_BTN_LOGOUT), width - 200, height - 70, 150, 50, TRUE);
        }
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_Z3_BTN_WARISA:
                    MessageBox(hwnd, "Warisa Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_PS:
                    MessageBox(hwnd, "P.S. Mansion Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_BAAAN:
                    MessageBox(hwnd, "Baan Tarnkam Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_TARNTHONG:
                    MessageBox(hwnd, "Tarnthong Place Apartment Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_THONGTARA:
                    MessageBox(hwnd, "Thongtara Monte Information", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_HISTORY:
                    MessageBox(hwnd, "Booking History", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_HOME:
                    MessageBox(hwnd, "Home", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case ID_Z3_BTN_LOGOUT:
                    MessageBox(hwnd, "Logging Out...", "Info", MB_OK | MB_ICONWARNING);
                    DestroyWindow(hwnd);
                    break;
            }
            break;
        case WM_DESTROY:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowZone3Window(HINSTANCE hInst, HWND parent)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = Zone3WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "Zone3Window";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&wc);
    CreateWindow("Zone3Window", "Zone 3", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
                 parent, NULL, hInst, NULL);
}