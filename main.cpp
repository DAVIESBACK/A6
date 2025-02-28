#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// ฟังก์ชันและตัวแปรที่จำเป็น
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AuthWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ZoneSelectionWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone1WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone2WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Zone3WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
HWND hMainWnd;
HWND hUsername, hPassword, hConfirmPassword;

#define ID_LOGIN_BUTTON 201
#define ID_SIGNUP_BUTTON 202
#define ID_EXIT_BUTTON 203
#define ID_SUBMIT_LOGIN 204
#define ID_SUBMIT_SIGNUP 205

// ฟังก์ชันแสดงหน้าต่าง Login/Sign Up
void ShowAuthWindow(bool isSignUp);
// ฟังก์ชันบันทึกข้อมูลผู้ใช้
bool SaveUserData(const std::string& username, const std::string& password);
// ฟังก์ชันตรวจสอบข้อมูลผู้ใช้
bool AuthenticateUser(const std::string& username, const std::string& password);
// ฟังก์ชันแสดงหน้าต่างเลือก Zone
void ShowZoneSelectionWindow();
// ฟังก์ชันแสดงหน้าต่าง Zone
void ShowZoneWindow(int zoneNumber);
void ShowBookingInfo(HWND hwnd, const std::string& roomName);
void saveBooking(std::string user, std::string dormName);

std::string loadCurrentUser();
void viewBookings(HWND hwnd);

std::string loadCurrentUser() {
    std::ifstream file("users.txt");
    std::string User;

    if (!file) return ""; // ถ้าไฟล์ไม่มี ให้ return ค่าว่าง

    std::getline(file, User);
    return User;
}

std::map<std::string, int> roomAvailability = {
    {"Uniloft Chiangmai\r\nChiangmai Road 123\r\n5000 bath", 5},
    {"Home Hills\r\nHillside Road 45\r\n4500 bath", 5},
    {"Baan Im Rak\r\nRak Street 67\r\n4000 bath", 5},
    {"Sanguanmalee Mansion\r\nSanguan Road 89\r\n5500 bath", 5},
    {"Kai Golden Place\r\nGolden Road 101\r\n6000 bath", 5},

    {"Phufa Place\r\nPhufa Lane 21\r\n4800 bath", 5},
    {"The Greenery Landmark\r\nGreen Street 55\r\n5200 bath", 5},
    {"Pojai Apartment\r\nPojai Road 32\r\n4300 bath", 5},
    {"Kiang Doi Place\r\nDoi Street 76\r\n4700 bath", 5},
    {"Baan Pranee (Jed Yod)\r\nJed Yod 99\r\n4600 bath", 5},

    {"Warisa Apartment\r\nWarisa Road 12\r\n4900 bath", 5},
    {"Warisa Apartment\r\nWarisa Road 12\r\n4900 bath", 5},
    {"Baan Tarnkam\r\nTarnkam Road 78\r\n4200 bath", 5},
    {"Tarnthong Place Apartment Chiangmai\r\nTarnthong Road 90\r\n5100 bath", 5},
    {"Thongtara Monte\r\nMonte Street 109\r\n5700 bath", 5}

};

// ฟังก์ชันหลัก
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;

    // กำหนดคลาสหน้าต่างหลัก
    WNDCLASS wc = {};
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MainWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // สร้างหน้าต่างหลัก
    hMainWnd = CreateWindow("MainWindow", "Booking System", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);
    if (!hMainWnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // แสดงหน้าต่างหลัก
    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    // วนลูปรับข้อความจากระบบ
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// ฟังก์ชันจัดการหน้าต่างหลัก
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // สร้างปุ่ม Login, Sign Up, และ Exit
        CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)ID_LOGIN_BUTTON, NULL, NULL);
        CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)ID_SIGNUP_BUTTON, NULL, NULL);
        CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)ID_EXIT_BUTTON, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_LOGIN_BUTTON:
            ShowAuthWindow(false);  // เปิดหน้าต่าง Login
            break;
        case ID_SIGNUP_BUTTON:
            ShowAuthWindow(true);   // เปิดหน้าต่าง Sign Up
            break;
        case ID_EXIT_BUTTON:
            PostQuitMessage(0);    // ปิดโปรแกรม
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

// ฟังก์ชันแสดงหน้าต่าง Login/Sign Up
void ShowAuthWindow(bool isSignUp) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = AuthWndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "AuthWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!GetClassInfo(hInst, "AuthWindow", &wc)) {
        RegisterClass(&wc);
    }

    // สร้างหน้าต่าง Login/Sign Up
    HWND hAuthWnd = CreateWindow("AuthWindow", isSignUp ? "Sign Up" : "Login", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInst, (LPVOID)isSignUp);
    ShowWindow(hAuthWnd, SW_SHOW);
    UpdateWindow(hAuthWnd);
}

// ฟังก์ชันจัดการหน้าต่าง Login/Sign Up
LRESULT CALLBACK AuthWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static bool isSignUp;

    switch (msg) {
    case WM_CREATE: {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        isSignUp = (bool)pCreate->lpCreateParams;

        // สร้างช่องกรอกข้อมูลและปุ่ม
        CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hwnd, NULL, NULL, NULL);
        hUsername = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 20, 150, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD, 20, 50, 80, 20, hwnd, NULL, NULL, NULL);
        hPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 100, 50, 150, 20, hwnd, NULL, NULL, NULL);

        if (isSignUp) {
            CreateWindow("STATIC", "Confirm:", WS_VISIBLE | WS_CHILD, 20, 80, 80, 20, hwnd, NULL, NULL, NULL);
            hConfirmPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 100, 80, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD, 100, 120, 100, 30, hwnd, (HMENU)ID_SUBMIT_SIGNUP, NULL, NULL);
        } else {
            CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 100, 90, 100, 30, hwnd, (HMENU)ID_SUBMIT_LOGIN, NULL, NULL);
        }
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_SUBMIT_SIGNUP || LOWORD(wParam) == ID_SUBMIT_LOGIN) {
            char username[100], password[100], confirmPassword[100] = "";
            GetWindowText(hUsername, username, 100);
            GetWindowText(hPassword, password, 100);
            if (isSignUp) {
                GetWindowText(hConfirmPassword, confirmPassword, 100);
                if (strcmp(password, confirmPassword) != 0) {
                    MessageBox(hwnd, "Passwords do not match!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                if (SaveUserData(username, password)) {
                    MessageBox(hwnd, "Sign Up Successful!", "Success", MB_OK);
                    DestroyWindow(hwnd);
                }
            } else {
                if (AuthenticateUser(username, password)) {
                    MessageBox(hwnd, "Login Successful!", "Welcome", MB_OK);
                    DestroyWindow(hwnd);
                    ShowZoneSelectionWindow();  // แสดงหน้าต่างเลือก Zone หลังจาก Login สำเร็จ
                } else {
                    MessageBox(hwnd, "Invalid Username or Password", "Error", MB_OK | MB_ICONERROR);
                }
            }
        }
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ฟังก์ชันบันทึกข้อมูลผู้ใช้
bool SaveUserData(const std::string& username, const std::string& password) {
    if (password.length() < 8) {
        MessageBox(NULL, "Password must be at least 8 characters long!", "Error", MB_OK | MB_ICONERROR);
        return false;  // หยุดการบันทึก
    }

    std::ifstream inFile("users.txt");
    std::string user, pass;

    // ตรวจสอบว่า username มีอยู่แล้วหรือไม่
    while (inFile >> user >> pass) {
        if (user == username) {
            MessageBox(NULL, "Username already exists! Please choose another.", "Error", MB_OK | MB_ICONERROR);
            return false;
        }
    }
    inFile.close();

    // บันทึกข้อมูลถ้าไม่มี username ซ้ำ
    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile) return false;
    outFile << username << " " << password << "\n";
    outFile.close();

    return true;
}

// ฟังก์ชันตรวจสอบข้อมูลผู้ใช้
bool AuthenticateUser(const std::string& username, const std::string& password) {
    std::ifstream file("users.txt");
    std::string user, pass;
    while (file >> user >> pass) {
        if (user == username && pass == password) {
            return true;
        }
    }
    return false;
}

// ฟังก์ชันแสดงหน้าต่างเลือก Zone
void ShowZoneSelectionWindow() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = ZoneSelectionWndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "ZoneSelectionWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!GetClassInfo(hInst, "ZoneSelectionWindow", &wc)) {
        RegisterClass(&wc);
    }

    HWND hZoneSelectionWnd = CreateWindow("ZoneSelectionWindow", "Select Zone", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInst, NULL);
    ShowWindow(hZoneSelectionWnd, SW_SHOW);
    UpdateWindow(hZoneSelectionWnd);
}

// ฟังก์ชันจัดการหน้าต่างเลือก Zone
LRESULT CALLBACK ZoneSelectionWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow("BUTTON", "Zone 1", WS_VISIBLE | WS_CHILD, 50, 50, 200, 40, hwnd, (HMENU)301, NULL, NULL);
        CreateWindow("BUTTON", "Zone 2", WS_VISIBLE | WS_CHILD, 50, 100, 200, 40, hwnd, (HMENU)302, NULL, NULL);
        CreateWindow("BUTTON", "Zone 3", WS_VISIBLE | WS_CHILD, 50, 150, 200, 40, hwnd, (HMENU)303, NULL, NULL);
        CreateWindow("BUTTON", "veiwbook", WS_VISIBLE | WS_CHILD, 50, 200, 200, 40, hwnd, (HMENU)304, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 301:
            ShowZoneWindow(1);  // แสดงหน้าต่าง Zone 1
            DestroyWindow(hwnd);
            break;
        case 302:
            ShowZoneWindow(2);  // แสดงหน้าต่าง Zone 2
            DestroyWindow(hwnd);
            break;
        case 303:
            ShowZoneWindow(3);  // แสดงหน้าต่าง Zone 3
            DestroyWindow(hwnd);
            break;
        case 304:
            viewBookings(hwnd);
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ฟังก์ชันแสดงหน้าต่าง Zone
void ShowZoneWindow(int zoneNumber) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = (zoneNumber == 1) ? Zone1WndProc : (zoneNumber == 2) ? Zone2WndProc : Zone3WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = (zoneNumber == 1) ? "Zone1Window" : (zoneNumber == 2) ? "Zone2Window" : "Zone3Window";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!GetClassInfo(hInst, wc.lpszClassName, &wc)) {
        RegisterClass(&wc);
    }

    HWND hZoneWnd = CreateWindow(wc.lpszClassName, (zoneNumber == 1) ? "Zone 1" : (zoneNumber == 2) ? "Zone 2" : "Zone 3", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInst, NULL);
    ShowWindow(hZoneWnd, SW_SHOW);
    UpdateWindow(hZoneWnd);
}

// ฟังก์ชันจัดการหน้าต่าง Zone 1
LRESULT CALLBACK Zone1WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow("BUTTON", "1. Unilof", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)401, NULL, NULL);
        CreateWindow("BUTTON", "2. Home Hill", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)402, NULL, NULL);
        CreateWindow("BUTTON", "3. Baan Im Rak", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)403, NULL, NULL);
        CreateWindow("BUTTON", "4. Sang", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)404, NULL, NULL);
        CreateWindow("BUTTON", "5. Kai Golden", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)405, NULL, NULL);
        CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)306, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 401:
            saveBooking(loadCurrentUser(),"Uniloft Chiangmai\r\nChiangmai Road 123\r\n5000 bath");
            break;
        case 402:
            saveBooking(loadCurrentUser(),"Home Hills\r\nHillside Road 45\r\n4500 bath");
            break;
        case 403:
            saveBooking(loadCurrentUser(),"Baan Im Rak\r\nRak Street 67\r\n4000 bath");
            break;
        case 404:
             saveBooking(loadCurrentUser(),"Sanguanmalee Mansion\r\nSanguan Road 89\r\n5500 bath");
            break;
        case 405:
             saveBooking(loadCurrentUser(),"Kai Golden Place\r\nGolden Road 101\r\n6000 bath");
            break;
        case 306:  // ปุ่ม Back
            DestroyWindow(hwnd);  // ปิดหน้าต่าง Zone ปัจจุบัน
            ShowZoneSelectionWindow();  // แสดงหน้าต่างเลือก Zone ใหม่
        break;
        }
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ฟังก์ชันจัดการหน้าต่าง Zone 2
LRESULT CALLBACK Zone2WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow("BUTTON", "1. Phufa Place Information", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)501, NULL, NULL);
        CreateWindow("BUTTON", "2. The Greenery Landmark Information", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)502, NULL, NULL);
        CreateWindow("BUTTON", "3. Pojai Apartment Information", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)503, NULL, NULL);
        CreateWindow("BUTTON", "4. Kiang Doi Place Information", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)504, NULL, NULL);
        CreateWindow("BUTTON", "5. Baan Pranee (Jed Yod) Information", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)505, NULL, NULL);
        CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)506, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 501:
            saveBooking(loadCurrentUser(),"Phufa Place\r\nPhufa Lane 21\r\n4800 bath");
            break;
        case 502:
             saveBooking(loadCurrentUser(),"The Greenery Landmark\r\nGreen Street 55\r\n5200 bath");
            break;
        case 503:
             saveBooking(loadCurrentUser(),"Pojai Apartment\r\nPojai Road 32\r\n4300 bath");
            break;
        case 504:
             saveBooking(loadCurrentUser(),"Kiang Doi Place\r\nDoi Street 76\r\n4700 bath");
            break;
        case 505:
             saveBooking(loadCurrentUser(),"Baan Pranee (Jed Yod)\r\nJed Yod 99\r\n4600 bath");
            break;
        case 506:  // ปุ่ม Back
            DestroyWindow(hwnd);  // ปิดหน้าต่าง Zone ปัจจุบัน
            ShowZoneSelectionWindow();  // แสดงหน้าต่างเลือก Zone ใหม่
        break;
        }
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ฟังก์ชันจัดการหน้าต่าง Zone 3
LRESULT CALLBACK Zone3WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow("BUTTON", "1. Warisa Apartment Information", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)601, NULL, NULL);
        CreateWindow("BUTTON", "2. P.S. Mansion Information", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)602, NULL, NULL);
        CreateWindow("BUTTON", "3. Baan Tarnkam Information", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)603, NULL, NULL);
        CreateWindow("BUTTON", "4. Tarnthong Place Apartment Information", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)604, NULL, NULL);
        CreateWindow("BUTTON", "5. Thongtara Monte Information", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)605, NULL, NULL);
        CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)606, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 601:
             saveBooking(loadCurrentUser(),"Warisa Apartment\r\nWarisa Road 12\r\n4900 bath");
            break;
        case 602:
             saveBooking(loadCurrentUser(),"Warisa Apartment\r\nWarisa Road 12\r\n4900 bath");
            break;
        case 603:
             saveBooking(loadCurrentUser(),"Baan Tarnkam\r\nTarnkam Road 78\r\n4200 bath");
            break;
        case 604:
             saveBooking(loadCurrentUser(),"Tarnthong Place Apartment Chiangmai\r\nTarnthong Road 90\r\n5100 bath");
            break;
        case 605:
             saveBooking(loadCurrentUser(),"Thongtara Monte\r\nMonte Street 109\r\n5700 bath");
            break;
        case 606:  // ปุ่ม Back
            DestroyWindow(hwnd);  // ปิดหน้าต่าง Zone ปัจจุบัน
            ShowZoneSelectionWindow();  // แสดงหน้าต่างเลือก Zone ใหม่
        break;
        }
        break;
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowBookingInfo(HWND hwnd, const std::string& roomName) {
    std::ifstream file("booking_history.txt");
    std::string history, line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find(roomName) != std::string::npos) {
                history += line + "\n";
            }
        }
        file.close();
    }

    if (history.empty()) {
        history = "No booking history.";
    }

    std::string message = "Information about " + roomName + "\n\nBooking History:\n" + history;
    MessageBox(hwnd, message.c_str(), "Room Information", MB_OK);
}

void saveBooking(std::string user, std::string dormName) {
    // โหลดข้อมูลจำนวนห้องที่เหลือจากไฟล์ (ถ้ามี)
    std::ifstream inFile("rooms.txt");
    if (inFile) {
        std::string name;
        int count;
        while (inFile >> name >> count) {
            roomAvailability[name] = count;
        }
    }
    inFile.close();

    // เช็คว่าห้องเต็มหรือยัง
    if (roomAvailability[dormName] == 0) {
        MessageBox(NULL, "This dorm is full!", "Booking Failed", MB_OK);
        return;
    }

    // ลดจำนวนห้องลง 1
    roomAvailability[dormName]--;

    // บันทึกลงไฟล์ bookings.txt
    std::ofstream file("bookings.txt", std::ios::app);
    file << user << " booked " << dormName << std::endl;
    file.close();

    // อัปเดตไฟล์ rooms.txt เพื่อบันทึกจำนวนห้องที่เหลือ
    std::ofstream outFile("rooms.txt");
    for (const auto& pair : roomAvailability) {
        outFile << pair.first << " " << pair.second << std::endl;
    }
    outFile.close();

    // แสดงข้อความยืนยัน
    std::string msg = "You booked " + dormName + "\nRooms left: " + std::to_string(roomAvailability[dormName]);
    MessageBox(NULL, msg.c_str(), "Booking Confirmed", MB_OK);
}


void viewBookings(HWND hwnd) {
    std::ifstream file("bookings.txt");
    std::string user = loadCurrentUser(); // โหลดผู้ใช้ปัจจุบัน
    std::string history, line;

    if (!file) {
        MessageBox(hwnd, "Error opening file!", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    while (std::getline(file, line)) {
        if (line.find(user) != std::string::npos) {
            history += line + "\n";
        }
    }
    file.close();

    if (history.empty()) {
        history = "No booking history found.";
    }

    MessageBox(hwnd, history.c_str(), "Booking History", MB_OK);
}