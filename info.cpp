#include <windows.h>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>

#define ID_EDIT_NAME 101
#define ID_EDIT_CHECKIN 102
#define ID_EDIT_CHECKOUT 103
#define ID_EDIT_PEOPLE 104
#define ID_BUTTON_CONFIRM 105
#define ID_BUTTON_HISTORY 106

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

struct Booking {
    char name[100];
    char checkIn[20];
    char checkOut[20];
    char people[10];
};

std::vector<Booking> bookingHistory;

void saveBookingToFile(const Booking& booking) {
    std::ofstream file("booking_data.txt", std::ios::app);
    if (file.is_open()) {
        file << booking.name << "|" << booking.checkIn << "|" << booking.checkOut << "|" << booking.people << "\n";
        file.close();
    }
}

void loadBookingFromFile() {
    bookingHistory.clear();
    std::ifstream file("booking_data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Booking booking;
            sscanf(line.c_str(), "%99[^|]|%19[^|]|%19[^|]|%9[^|]", booking.name, booking.checkIn, booking.checkOut, booking.people);
            bookingHistory.push_back(booking);
        }
        file.close();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "HotelBookingClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);
    HWND hwnd = CreateWindow("HotelBookingClass", "Hotel Booking", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEditName, hEditCheckIn, hEditCheckOut, hEditPeople, hButtonConfirm, hButtonHistory;
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hwnd, NULL, NULL, NULL);
            hEditName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 20, 200, 20, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);

            CreateWindow("STATIC", "Check-in:", WS_VISIBLE | WS_CHILD, 20, 50, 80, 20, hwnd, NULL, NULL, NULL);
            hEditCheckIn = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 50, 200, 20, hwnd, (HMENU)ID_EDIT_CHECKIN, NULL, NULL);

            CreateWindow("STATIC", "Check-out:", WS_VISIBLE | WS_CHILD, 20, 80, 80, 20, hwnd, NULL, NULL, NULL);
            hEditCheckOut = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 80, 200, 20, hwnd, (HMENU)ID_EDIT_CHECKOUT, NULL, NULL);

            CreateWindow("STATIC", "People:", WS_VISIBLE | WS_CHILD, 20, 110, 80, 20, hwnd, NULL, NULL, NULL);
            hEditPeople = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 110, 200, 20, hwnd, (HMENU)ID_EDIT_PEOPLE, NULL, NULL);

            hButtonConfirm = CreateWindow("BUTTON", "Confirm Booking", WS_VISIBLE | WS_CHILD, 100, 150, 200, 30, hwnd, (HMENU)ID_BUTTON_CONFIRM, NULL, NULL);
            hButtonHistory = CreateWindow("BUTTON", "Booking History", WS_VISIBLE | WS_CHILD, 100, 200, 200, 30, hwnd, (HMENU)ID_BUTTON_HISTORY, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON_CONFIRM) {
                Booking newBooking;
                GetWindowText(hEditName, newBooking.name, sizeof(newBooking.name));
                GetWindowText(hEditCheckIn, newBooking.checkIn, sizeof(newBooking.checkIn));
                GetWindowText(hEditCheckOut, newBooking.checkOut, sizeof(newBooking.checkOut));
                GetWindowText(hEditPeople, newBooking.people, sizeof(newBooking.people));
                
                saveBookingToFile(newBooking);
                
                char message[300];
                sprintf(message, "Booking Details:\nName: %s\nCheck-in: %s\nCheck-out: %s\nPeople: %s", newBooking.name, newBooking.checkIn, newBooking.checkOut, newBooking.people);
                MessageBox(hwnd, message, "Booking Confirmation", MB_OK);
            }
            else if (LOWORD(wParam) == ID_BUTTON_HISTORY) {
                loadBookingFromFile();
                if (bookingHistory.empty()) {
                    MessageBox(hwnd, "No booking history available.", "Booking History", MB_OK);
                } else {
                    std::string history = "Booking History:\n";
                    for (const auto& booking : bookingHistory) {
                        char entry[300];
                        sprintf(entry, "\nName: %s\nCheck-in: %s\nCheck-out: %s\nPeople: %s\n", booking.name, booking.checkIn, booking.checkOut, booking.people);
                        history += entry;
                    }
                    MessageBox(hwnd, history.c_str(), "Booking History", MB_OK);
                }
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
