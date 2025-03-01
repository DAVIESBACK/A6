#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include <sstream>  // สำหรับ std::ostringstream
#include <vector>   // สำหรับ std::vector

std::map<std::string, std::string> placeDescriptions = {
    {"Unilof", "Location: 147 Ban Mai Behind Mo1 Suthep Subdistrict Mueang Chiang Mai District Chiang Mai 50200\nInformation\n5000 baht/month\nPhone : 053-328-181\tRating 5/5"},
    {"Home Hill", "Location: 143 Soi 7 Suthep Road Suthep Muang Chiang Mai 50200\nInformation\n4500 baht/month\nPhone : 0947402458\nRating 4/5"},
    {"Baan Im Rak", "Location: Ban Mai Road behind Mo Suthep Subdistrict Mueang Chiang Mai District 50200\nInformation\n4000 baht/month\nPhone : 053-328-421\nRating 4/5"},
    {"Sang","Location 145 Moo 14 Soi Suthep 7 Chiang Mai 50200\nInformation\n5500 baht/month\nPhone: 0953468524\nRating 5/5"},
    {"Kai Golden","Location: 192/1 Moo 14 Suthep Subdistrict Mueang District Chiang Mai Thailand\nInformation\n6000 baht/month\nPhone : 082 556 5353\nRating 5/5"},
    {"Phufa Place","Location: 177/1 Moo 1 Khan Klong Chonlaprathan Road Chang Phueak Subdistrict Chiang Mai Municipality Chiang Mai Province 50300\nInformation\n4800 baht/month\nPhone: 084 611 1154\tRating 4/5"},
    {"The Greenery Landmark","Location: 99/2 M.2 T.Chang Phuek Amphoe Muang Chiang Mai Thailand Chiang Mai\nInformation\n5200 baht/month\nPhone: 083 567 7117\nRating 5/5"},
    {"Porjai Apartment","Location: Chang Khian-Ched Yot Road Chang Phueak Subdistrict Mueang Chiang Mai District 50300\nInformation\n4300 baht/month\nPhone : 084-357-6079\tRating 4/5"},
    {"Kiang Doi Place","Location: 176 Moo 1 Chang Phueak Mueang Chiang Mai District 50300\nInformation\n4700 baht/month\nPhone: 053-400-402\nRating 4/5"},
    {"Baan Pranee(JedYod)","Location: JedYod Chang Khian Road Chang Phueak Mueang Chiang Mai Chiang Mai\nInformation\n4600 baht/month\nPhone : 0812888585\nRating 4/5"},
    {"Warisa Apartment","Location: 60 Khunklong Chonprathan Rd Tambon Su Thep Amphoe Mueang Chiang Mai Chang Wat Chiang Mai 50200 Chiang Mai Thailand Chiang Mai\nInformation\n4900 baht/month\nPhone : 0847431149\tRating 5/5"},
    {"P.S Mansion","Location: 689/1-5 Chang Phueak Muang Chiang Mai 50300\nInformation\n5300 baht/month\nPhone : 098-9565639\nRating 4/5"},
    {"Baan Tarnkam","Location: 456 Chiang Mai-Hang Dong Road  Mueang Chiang Mai District Chiang Mai\nInformation\n4200 baht/month\nPhone : 053-461-351\nRating 4/5"},
    {"Tarnthong Place Apartment","Location: 188/8 Village No.10 Mueang Chiang Mai District Chiang Mai 50200\nInformation\n5100 baht/month\nPhone : 098-824-2223\nRating 5/5"},
    {"Thongtara Monte","Location: Suthep Rd. Soi 2 Suthep Mueang Chiang Mai Chiang Mai\nInformation\n5700 baht/month\nPhone : 062-845-4665\nRating 4/5"}
};
std::multimap<std::string, std::string> bookings;
std::map<std::string, int> roomAvailability = {
<<<<<<< HEAD
    {"Unilof",10}, {"Home Hill",10}, {"Baan Im Rak",10}, {"Sang",10}, {"Kai Golden",10},
    {"Phufa Place",10}, {"The Greenery Landmark",2}, {"Porjai Apartment",1}, {"Kiang Doi Place",10}, {"Baan Pranee(JedYod)",10},
    {"Warisa Apartment",10}, {"P.S Mansion",10}, {"Baan Tarnkam",10}, {"Tarnthong Place Apartment",10}, {"Thongtara Monte",10}
=======
    {"Unilof",5}, {"Home Hill",6}, {"Baan Im Rak",7}, {"Sang",8}, {"Kai Golden",2},
    {"Phufa Place",3}, {"The Greenery Landmark",2}, {"Porjai Apartment",1}, {"Kiang Doi Place",5}, {"Baan Pranee(JedYod)",8},
    {"Warisa Apartment",5}, {"P.S Mansion",2}, {"Baan Tarnkam",3}, {"Tarnthong Place Apartment",6}, {"Thongtara Monte",4}
>>>>>>> 81ef3717e6d1c8ce56bac8588f42d43f3afec4b2
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
        CW_USEDEFAULT, CW_USEDEFAULT, 1600, 1600, NULL, NULL, hInstance, NULL);
    
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
        1600, 1600, NULL, NULL, hInst, (LPVOID)userParam
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
            DestroyWindow(hwnd);
            break;
        case 302:
            ShowZoneWindow(2, currentUser); // แก้ไขให้ส่ง username
            DestroyWindow(hwnd);
            break;
        case 303:
            ShowZoneWindow(3, currentUser); // แก้ไขให้ส่ง username
            DestroyWindow(hwnd);
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
        1600, 1600, NULL, NULL, hInst, params
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
            CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)406, NULL, NULL);
            
        } else if (zoneNumber == 2) {
            CreateWindow("BUTTON", "1. Phufa Place", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)501, NULL, NULL);
            CreateWindow("BUTTON", "2. The Greenery Landmark", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)502, NULL, NULL);
            CreateWindow("BUTTON", "3. Porjai Apartment", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)503, NULL, NULL);
            CreateWindow("BUTTON", "4. Kiang Doi Place", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)504, NULL, NULL);
            CreateWindow("BUTTON", "5. Baan Pranee", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)505, NULL, NULL);
<<<<<<< HEAD
            CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)506, NULL, NULL);
=======
>>>>>>> 81ef3717e6d1c8ce56bac8588f42d43f3afec4b2
        } else if (zoneNumber == 3) {
            // เพิ่มปุ่มสำหรับ Zone 3
            CreateWindow("BUTTON", "1. Warisa Apartment", WS_VISIBLE | WS_CHILD, 50, 50, 150, 40, hwnd, (HMENU)601, NULL, NULL);
            CreateWindow("BUTTON", "2. P.S Mansion", WS_VISIBLE | WS_CHILD, 50, 100, 150, 40, hwnd, (HMENU)602, NULL, NULL);
            CreateWindow("BUTTON", "3. Baan Tarnkam", WS_VISIBLE | WS_CHILD, 50, 150, 150, 40, hwnd, (HMENU)603, NULL, NULL);
            CreateWindow("BUTTON", "4. Tarnthong Place Apartment", WS_VISIBLE | WS_CHILD, 50, 200, 150, 40, hwnd, (HMENU)604, NULL, NULL);
            CreateWindow("BUTTON", "5. Thongtara Monte", WS_VISIBLE | WS_CHILD, 50, 250, 150, 40, hwnd, (HMENU)605, NULL, NULL);
<<<<<<< HEAD
            CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD, 50, 300, 150, 40, hwnd, (HMENU)606, NULL, NULL);
=======
>>>>>>> 81ef3717e6d1c8ce56bac8588f42d43f3afec4b2
        }
        break;}
    case WM_COMMAND: {
        int buttonId = LOWORD(wParam);
        std::string placeName;
        
        // Map button IDs ไปยังชื่อสถานที่
        if (zoneNumber == 1) {
            switch(buttonId) {
                case 401: placeName = "Unilof"; DestroyWindow(hwnd); break;
                case 402: placeName = "Home Hill"; DestroyWindow(hwnd); break;
                case 403: placeName = "Baan Im Rak"; DestroyWindow(hwnd); break;
                case 404: placeName = "Sang"; DestroyWindow(hwnd); break;
                case 405: placeName = "Kai Golden"; DestroyWindow(hwnd); break;
                case 406: ShowZoneSelectionWindow(currentUser); DestroyWindow(hwnd); break;
            }
        } else if (zoneNumber == 2) {
            switch(buttonId) {
<<<<<<< HEAD
                case 501: placeName = "Phufa Place"; DestroyWindow(hwnd); break;
                case 502: placeName = "The Greenery Landmark"; DestroyWindow(hwnd); break;
                case 503: placeName = "Porjai Apartment"; DestroyWindow(hwnd); break;
                case 504: placeName = "Kiang Doi Place"; DestroyWindow(hwnd); break;
                case 505: placeName = "Baan Pranee(JedYod)"; DestroyWindow(hwnd); break;
                case 506: ShowZoneSelectionWindow(currentUser); DestroyWindow(hwnd); break;
            }
        } else if (zoneNumber == 3) {
            switch(buttonId) {
                case 601: placeName = "Warisa Apartment"; DestroyWindow(hwnd); break;
                case 602: placeName = "P.S Mansion"; DestroyWindow(hwnd); break;
                case 603: placeName = "Baan Tarnkam"; DestroyWindow(hwnd); break;
                case 604: placeName = "Tarnthong Place Apartment"; DestroyWindow(hwnd); break;
                case 605: placeName = "Thongtara Monte"; DestroyWindow(hwnd); break;
                case 606: ShowZoneSelectionWindow(currentUser); DestroyWindow(hwnd); break;
=======
                case 501: placeName = "Phufa Place"; break;
                case 502: placeName = "The Greenery Landmark"; break;
                case 503: placeName = "Porjai Apartment"; break;
                case 504: placeName = "Kiang Doi Place"; break;
                case 505: placeName = "Baan Pranee(JedYod)"; break;
            }
        } else if (zoneNumber == 3) {
            switch(buttonId) {
                case 601: placeName = "Warisa Apartment"; break;
                case 602: placeName = "P.S Mansion"; break;
                case 603: placeName = "Baan Tarnkam"; break;
                case 604: placeName = "Tarnthong Place Apartment"; break;
                case 605: placeName = "Thongtara Monte"; break;
>>>>>>> 81ef3717e6d1c8ce56bac8588f42d43f3afec4b2
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
        1600, 1600, NULL, NULL, hInst, params // ปรับขนาดเป็น 400x400
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
            {"Unilof",10}, {"Home Hill",10}, {"Baan Im Rak",10}, {"Sang",10}, {"Kai Golden",10},
            {"Phufa Place",10}, {"The Greenery Landmark",10}, {"Pojai Apartment",10}, {"Kiang Doi Place",10}, {"Baan Pranee (Jed Yod)",10},
            {"Warisa Apartment",10}, {"P.S. Mansion",10}, {"Baan Tarnkam",10}, {"Tarnthong Place Apartment Chiangmai",10}, {"Thongtara Monte",10}
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