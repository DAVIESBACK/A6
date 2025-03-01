#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include <sstream>  // สำหรับ std::ostringstream
#include <vector>   // สำหรับ std::vector

std::map<std::string, std::string> placeDescriptions = {
    {"Unilof", "Uniloft Chiangmai\nLocation:147 VillageNo. 14 Soi Ban Mai Behind Mo1 Suthep Subdistrict"},
    {"Home Hill", "Home Hill \n:\n-\n- "},
    {"Baan Im Rak", "Baan Im Rak "},
    // ...
};
std::multimap<std::string, std::string> bookings;
std::map<std::string, int> roomAvailability = {
    {"Unilof",5}, {"Home Hill",6}, {"Baan Im Rak",7}, {"Sang",8}, {"Kai Golden",2},
    {"Place A",3}, {"Place B",2}, {"Place C",1}, {"Place D",5}, {"Place E",8},
    {"Spot X",5}, {"Spot Y",2}, {"Spot Z",3}, {"Spot W",6}, {"Spot V",4}
};

HINSTANCE hInst;
HWND hMainWnd;
HWND hUsername, hPassword, hConfirmPassword;

#define ID_LOGIN_BUTTON 201
#define ID_SIGNUP_BUTTON 202
#define ID_EXIT_BUTTON 203
#define ID_SUBMIT_LOGIN 204
#define ID_SUBMIT_SIGNUP 205
#define ID_CANCEL_BOOKING 704

// ฟังก์ชันหลัก
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AuthWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ZoneSelectionWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ZoneWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PlaceWndProc(HWND, UINT, WPARAM, LPARAM);

void ShowAuthWindow(bool isSignUp);
bool SaveUserData(const std::string& username, const std::string& password);
bool AuthenticateUser(const std::string& username, const std::string& password);
bool CancelBooking(HWND hwnd, const std::string& place, const std::string& username);
void ShowZoneSelectionWindow(const std::string& username); // เพิ่มพารามิเตอร์
void ShowZoneWindow(int zoneNumber, const std::string& username); // เพิ่มพารามิเตอร์ username
void ShowPlaceWindow(std::pair<std::string, std::string>* params); // เปลี่ยนพารามิเตอร์

bool HasUserBooked(const std::string& username);
bool BookPlace(HWND hwnd, const std::string& place, const std::string& username);
std::string GetBookingStatus(const std::string& place);
int GetRemainingRooms(const std::string& place);
void SaveBookingsToFile();
void LoadBookingsFromFile();

// ฟังก์ชันหลัก
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;  
    (void)lpCmdLine;      
    hInst = hInstance;
    LoadBookingsFromFile();

    // 1. ประกาศและลงทะเบียนคลาสหน้าต่างหลักก่อน
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

    // 2. ลงทะเบียนคลาสอื่นๆ หลังจากนี้
    // ลงทะเบียนคลาส ZoneWindow
    WNDCLASS zoneWc = {};
    zoneWc.lpfnWndProc = ZoneWndProc;
    zoneWc.hInstance = hInstance;
    zoneWc.lpszClassName = "ZoneWindow";
    zoneWc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    zoneWc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&zoneWc);

    // ลงทะเบียนคลาส PlaceWindow
    WNDCLASS placeWc = {};
    placeWc.lpfnWndProc = PlaceWndProc;
    placeWc.hInstance = hInstance;
    placeWc.lpszClassName = "PlaceWindow";
    placeWc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    placeWc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&placeWc);

    // 3. สร้างหน้าต่างหลัก
    hMainWnd = CreateWindow("MainWindow", "Booking System", WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL);
    
    if (!hMainWnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

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
        break;
    case WM_CREATE:
        CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)ID_LOGIN_BUTTON, NULL, NULL);
        CreateWindow("BUTTON", "Sign Up", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)ID_SIGNUP_BUTTON, NULL, NULL);
        CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)ID_EXIT_BUTTON, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_LOGIN_BUTTON:
            ShowAuthWindow(false);
            break;
        case ID_SIGNUP_BUTTON:
            ShowAuthWindow(true);
            break;
        case ID_EXIT_BUTTON:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        SaveBookingsToFile();
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
                    ShowZoneSelectionWindow(username); // ส่ง username ต่อ
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
    std::ifstream inFile("users.txt");
    std::string user, pass;

    while (inFile >> user >> pass) {
        if (user == username) {
            MessageBox(NULL, "Username already exists! Please choose another.", "Error", MB_OK | MB_ICONERROR);
            return false;
        }
    }
    inFile.close();

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
void ShowZoneSelectionWindow(const std::string& username) { // ใส่พารามิเตอร์
    WNDCLASS wc = {};
    wc.lpfnWndProc = ZoneSelectionWndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "ZoneSelectionWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!GetClassInfo(hInst, "ZoneSelectionWindow", &wc)) {
        RegisterClass(&wc);
    }
    char* userParam = new char[username.size() + 1];
    strcpy(userParam, username.c_str());
    // หน่วยความจำจะถูกลบใน ZoneSelectionWndProc

    HWND hZoneSelectionWnd = CreateWindow(
        "ZoneSelectionWindow", "Select Zone", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        300, 300, NULL, NULL, hInst, (LPVOID)userParam
    );
    ShowWindow(hZoneSelectionWnd, SW_SHOW);
}
// ฟังก์ชันจัดการหน้าต่างเลือก Zone
LRESULT CALLBACK ZoneSelectionWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static std::string currentUser; // ประกาศ static variable
    switch (msg) {
    case WM_CREATE:{
        // ดึง username จากพารามิเตอร์
        char* userParam = (char*)((CREATESTRUCT*)lParam)->lpCreateParams;
        currentUser = userParam; // กำหนดค่าให้ static variable
        delete[] userParam;
        CreateWindow("BUTTON", "Zone 1", WS_VISIBLE | WS_CHILD, 50, 50, 200, 40, hwnd, (HMENU)301, NULL, NULL);
        CreateWindow("BUTTON", "Zone 2", WS_VISIBLE | WS_CHILD, 50, 100, 200, 40, hwnd, (HMENU)302, NULL, NULL);
        CreateWindow("BUTTON", "Zone 3", WS_VISIBLE | WS_CHILD, 50, 150, 200, 40, hwnd, (HMENU)303, NULL, NULL);
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
            case 301:
            ShowZoneWindow(1, currentUser); // ส่ง username ไปด้วย
            break;
        case 302:
            ShowZoneWindow(2, currentUser); // แก้ไขให้ส่ง username
            break;
        case 303:
            ShowZoneWindow(3, currentUser); // แก้ไขให้ส่ง username
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

// ฟังก์ชันแสดงหน้าต่าง Zone
void ShowZoneWindow(int zoneNumber, const std::string& username) {
    // สร้าง struct เพื่อเก็บข้อมูลโซนและผู้ใช้
    struct ZoneParams {
        int zone;
        std::string user;
    };
    ZoneParams* params = new ZoneParams{zoneNumber, username};

    HWND hZoneWnd = CreateWindow(
        "ZoneWindow", ("Zone " + std::to_string(zoneNumber)).c_str(), // เปลี่ยนชื่อหน้าต่าง
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300, NULL, NULL, hInst, params
    );
    ShowWindow(hZoneWnd, SW_SHOW);
}
// ฟังก์ชันจัดการหน้าต่าง Zone
// ต่อจากส่วน ZoneWndProc ในโค้ดที่ให้มา
// ประกาศโครงสร้างนอกฟังก์ชัน (ก่อน ZoneWndProc)
struct ZoneParams {
    int zone;
    std::string user;
};

LRESULT CALLBACK ZoneWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static std::string currentUser;
    static int zoneNumber;

    switch (msg) {
    case WM_CREATE:{
        // ใน ZoneWndProc
        ZoneParams* params = (ZoneParams*)((CREATESTRUCT*)lParam)->lpCreateParams;
        zoneNumber = params->zone; // ใช้ค่าจาก params โดยตรง
        currentUser = params->user;
        delete params;

       
        if (zoneNumber == 1) {
            CreateWindow("BUTTON", "1. Unilof", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)401, NULL, NULL);
            CreateWindow("BUTTON", "2. Home Hill", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)402, NULL, NULL);
            CreateWindow("BUTTON", "3. Baan Im Rak", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)403, NULL, NULL);
            CreateWindow("BUTTON", "4. Sang", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)404, NULL, NULL);
            CreateWindow("BUTTON", "5. Kai Golden", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)405, NULL, NULL);
        } else if (zoneNumber == 2) {
            CreateWindow("BUTTON", "1. Place A", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)501, NULL, NULL);
            CreateWindow("BUTTON", "2. Place B", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)502, NULL, NULL);
            CreateWindow("BUTTON", "3. Place C", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)503, NULL, NULL);
            CreateWindow("BUTTON", "4. Place D", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)504, NULL, NULL);
            CreateWindow("BUTTON", "5. Place E", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)505, NULL, NULL);
        } else if (zoneNumber == 3) {
            // เพิ่มปุ่มสำหรับ Zone 3
            CreateWindow("BUTTON", "1. Spot X", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)601, NULL, NULL);
            CreateWindow("BUTTON", "2. Spot Y", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)602, NULL, NULL);
            CreateWindow("BUTTON", "3. Spot Z", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)603, NULL, NULL);
            CreateWindow("BUTTON", "4. Spot W", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)604, NULL, NULL);
            CreateWindow("BUTTON", "5. Spot V", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)605, NULL, NULL);
        }
        break;}
    case WM_COMMAND: {
        int buttonId = LOWORD(wParam);
        std::string placeName;
        
        // Map button IDs ไปยังชื่อสถานที่
        if (zoneNumber == 1) {
            switch(buttonId) {
                case 401: placeName = "Unilof"; break;
                case 402: placeName = "Home Hill"; break;
                case 403: placeName = "Baan Im Rak"; break;
                case 404: placeName = "Sang"; break;
                case 405: placeName = "Kai Golden"; break;
            }
        } else if (zoneNumber == 2) {
            switch(buttonId) {
                case 501: placeName = "Place A"; break;
                case 502: placeName = "Place B"; break;
                case 503: placeName = "Place C"; break;
                case 504: placeName = "Place D"; break;
                case 505: placeName = "Place E"; break;
            }
        } else if (zoneNumber == 3) {
            switch(buttonId) {
                case 601: placeName = "Spot X"; break;
                case 602: placeName = "Spot Y"; break;
                case 603: placeName = "Spot Z"; break;
                case 604: placeName = "Spot W"; break;
                case 605: placeName = "Spot V"; break;
            }
        }
    
        if (!placeName.empty()) {
            auto bookingParams = new std::pair<std::string, std::string>(placeName, currentUser);
            ShowPlaceWindow(bookingParams);
        }
        break; }
    case WM_DESTROY:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ฟังก์ชันแสดงหน้าต่างสถานที่
void ShowPlaceWindow(std::pair<std::string, std::string>* params) {
    // ตรวจสอบการลงทะเบียนคลาสก่อนสร้างหน้าต่าง
    WNDCLASS wc = {};
    if (!GetClassInfo(hInst, "PlaceWindow", &wc)) {
        MessageBox(NULL, "Place Window Class Not Registered!", "Error", MB_ICONERROR);
        return;
    }
    HWND hPlaceWnd = CreateWindow(
        "PlaceWindow", params->first.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 400, NULL, NULL, hInst, params // ปรับขนาดเป็น 400x400
    );
    ShowWindow(hPlaceWnd, SW_SHOW);
}

// ฟังก์ชันจัดการหน้าต่างสถานที่
LRESULT CALLBACK PlaceWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static std::string currentUser;
    static std::string placeName;
    static HWND hStatusText;

    switch (msg) {
        case WM_CREATE: {
            auto params = (std::pair<std::string, std::string>*)((CREATESTRUCT*)lParam)->lpCreateParams;
            placeName = params->first;
            currentUser = params->second;
            delete params;
            // ตรวจสอบข้อมูลจาก Map
            std::string description = placeDescriptions.count(placeName) 
            ? placeDescriptions[placeName] 
            : "No additional information available";

            // สร้าง Static Text สำหรับแสดงข้อมูลห้องพัก
            CreateWindow("STATIC", description.c_str(), 
            WS_VISIBLE | WS_CHILD | SS_LEFT, 
            20, 20, 340, 100, hwnd, NULL, NULL, NULL);

            // ปรับตำแหน่งปุ่มและข้อความสถานะให้อยู่ด้านล่าง
            CreateWindow("BUTTON", "Book", WS_VISIBLE | WS_CHILD, 50, 140, 150, 40, hwnd, (HMENU)701, NULL, NULL);
            CreateWindow("BUTTON", "Check Status", WS_VISIBLE | WS_CHILD, 50, 190, 150, 40, hwnd, (HMENU)702, NULL, NULL);
            CreateWindow("BUTTON", "Cancel Booking", WS_VISIBLE | WS_CHILD, 50, 240, 150, 40, hwnd, (HMENU)704, NULL, NULL);
            CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 290, 150, 40, hwnd, (HMENU)703, NULL, NULL);

            hStatusText = CreateWindow("STATIC", GetBookingStatus(placeName).c_str(), 
            WS_VISIBLE | WS_CHILD | SS_CENTER, 
            50, 340, 250, 60, hwnd, NULL, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 701: // Book
                if (BookPlace(hwnd, placeName, currentUser)) {
                MessageBox(hwnd, "Booking successful!", "Success", MB_OK);
                // อัปเดตสถานะ
                SetWindowText(hStatusText, GetBookingStatus(placeName).c_str());
            }
            break;
                case 702: // Check Status
                    MessageBox(hwnd, 
                        ("=== Current Status ===\n" + 
                        GetBookingStatus(placeName) + 
                        "\n\nYour Account: " + currentUser).c_str(), 
                        "Booking Details", MB_OK);
                    break;
                case 703: // Back
                    ShowZoneSelectionWindow(currentUser);
                    DestroyWindow(hwnd);
                    break;
                case 704: // Cancel Booking
                    if (CancelBooking(hwnd, placeName, currentUser)) {
                        MessageBox(hwnd, "Booking canceled!", "Success", MB_OK);
                        SetWindowText(hStatusText, GetBookingStatus(placeName).c_str());
                    }
                    break;
            }
            break;
        }
        case WM_DESTROY:
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


bool BookPlace(HWND hwnd, const std::string& place, const std::string& username) {
    // ตรวจสอบห้องว่าง
    if (roomAvailability[place] <= 0) {
        MessageBox(hwnd, "This place is fully booked!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

   
   // เพิ่มการจองและอัปเดตห้องว่าง
   bookings.insert(std::make_pair(place, username));
   roomAvailability[place]--;
   SaveBookingsToFile();
   return true;
}

void SaveBookingsToFile() {
    std::ofstream file("bookings.txt", std::ios::trunc);
    
    // บันทึกจำนวนห้องคงเหลือ
    file << "[Rooms]\n";
    for (const auto& room : roomAvailability) {
        file << room.first << "|" << room.second << "\n";
    }

    // บันทึกข้อมูลการจอง
    file << "[Bookings]\n";
    for (const auto& booking : bookings) {
        file << booking.first << "|" << booking.second << "\n";
    }
}

void LoadBookingsFromFile() {
    std::ifstream file("bookings.txt");
    std::string line;
    bookings.clear();

    if (!file) {
        // ตั้งค่าเริ่มต้นเฉพาะเมื่อไม่มีไฟล์
        roomAvailability = {
            {"Unilof",5}, {"Home Hill",6}, {"Baan Im Rak",7}, {"Sang",8}, {"Kai Golden",2},
            {"Place A",3}, {"Place B",2}, {"Place C",1}, {"Place D",5}, {"Place E",8},
            {"Spot X",5}, {"Spot Y",2}, {"Spot Z",3}, {"Spot W",6}, {"Spot V",4}
        };
        return;
    }

    // โหลดข้อมูลห้อง
    if (std::getline(file, line) && line == "[Rooms]") {
        while (std::getline(file, line)) {
            if (line == "[Bookings]") break;
            size_t delimiterPos = line.find('|');
            if (delimiterPos != std::string::npos) {
                std::string place = line.substr(0, delimiterPos);
                int rooms = std::stoi(line.substr(delimiterPos + 1));
                roomAvailability[place] = rooms;
            }
        }
    }

    // โหลดข้อมูลการจอง
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != std::string::npos) {
            std::string place = line.substr(0, delimiterPos);
            std::string user = line.substr(delimiterPos + 1);
            bookings.insert({place, user});
        }
    }
}
std::string GetBookingStatus(const std::string& place) {
    std::ostringstream oss;
    int remaining = roomAvailability[place];
    auto range = bookings.equal_range(place);

    oss << "Place: " << place << "\n";
    oss << "Remaining Rooms: " << remaining << "\n";
    oss << "Booked by:\n";

    for (auto it = range.first; it != range.second; ++it) {
        oss << "- " << it->second << "\n";
    }

    return oss.str();
}
bool CancelBooking(HWND hwnd, const std::string& place, const std::string& username) {
    auto range = bookings.equal_range(place);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == username) {
            bookings.erase(it);
            roomAvailability[place]++;
            SaveBookingsToFile();
            return true;
        }
    }
    MessageBox(hwnd, "You have not booked this place.", "Error", MB_OK | MB_ICONERROR);
    return false;
}