// ใน zoneMenu.cpp
#include "zoneMenu.h"
#include "zone1.h"
#include <iostream>
#include <vector>

using namespace std;

void displayZone1s(vector<Zone1>& zone1s) {
    // ฟังก์ชันแสดงข้อมูล Zone1
}

void bookZone1(vector<Zone1>& zone1s) {
    // ฟังก์ชันจอง Zone1
}

void zoneMenu(vector<Zone1>& zone1s) {
    int zoneChoice;
    while (true) {
        cout << "\n=== Select a Zone ===\n";
        cout << "1. Zone 1\n";
        cout << "2. Zone 2\n";
        cout << "3. Zone 3\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> zoneChoice;

        switch (zoneChoice) {
            case 1:
                displayZone1s(zone1s);
                bookZone1(zone1s);
                break;
            case 2:
                cout << "Zone 2 is under development...\n";
                break;
            case 3:
                cout << "Zone 3 is under development...\n";
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
int main() {
    vector<Zone1> zone1s = { Zone1(), Zone1(), Zone1() };  // เพิ่มตัวอย่างข้อมูล Zone1
    zoneMenu(zone1s);
    return 0;
}
