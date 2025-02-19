#include <windows.h>
#include <vector>
#include <string>
#include "zone1.h"
using namespace std;



vector<Zone1> zones = {
    {1, "Zone A", "Near University", 3000, true},
    {2, "Zone B", "Near Shopping Mall", 3500, true},
    {3, "Zone C", "In the City Center", 4000, false}
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DisplayZones(HWND);
void BookZone(HWND);

HWND hwndList, hwndBookButton, hwndExitButton;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ZoneBookingClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("ZoneBookingClass", "Zone Booking System", 
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
                             NULL, NULL, hInstance, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            hwndList = CreateWindow("LISTBOX", NULL, 
                                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
                                    20, 20, 440, 200, hwnd, (HMENU)1, NULL, NULL);
            
            hwndBookButton = CreateWindow("BUTTON", "Book Selected Zone", 
                                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                          150, 240, 200, 30, hwnd, (HMENU)2, NULL, NULL);

            hwndExitButton = CreateWindow("BUTTON", "Exit", 
                                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                          150, 280, 200, 30, hwnd, (HMENU)3, NULL, NULL);
            
            DisplayZones(hwnd);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 2) { 
                BookZone(hwnd);
            }
            else if (LOWORD(wParam) == 3) { 
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

void DisplayZones(HWND hwnd) {
    SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
    
    for (const auto& zone : zones) {
        string status = zone.isAvailable ? "Available" : "Booked";
        string item = "ID: " + to_string(zone.id) + " | " + zone.name + " | " + zone.location + " | $" + to_string(zone.price) + " | " + status;
        SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)item.c_str());
    }
}

void BookZone(HWND hwnd) {
    int index = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) {
        MessageBox(hwnd, "Please select a zone to book!", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    if (!zones[index].isAvailable) {
        MessageBox(hwnd, "This zone is already booked!", "Not Available", MB_OK | MB_ICONINFORMATION);
    } else {
        zones[index].isAvailable = false;
        MessageBox(hwnd, "You have successfully booked this zone!", "Success", MB_OK | MB_ICONINFORMATION);
        DisplayZones(hwnd);
    }
}
  