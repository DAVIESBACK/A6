#ifndef ZONE2_H
#define ZONE2_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Zone2 {
    int id;
    string name;
    string address;
    int price;
    bool available;
};

void displayZone2s(const vector<Zone2>& zone2s) {
    for (const auto& zone : zone2s) {
        cout << "ID: " << zone.id << endl;
        cout << "Name: " << zone.name << endl;
        cout << "Address: " << zone.address << endl;
        cout << "Price: " << zone.price << endl;
        cout << "Available: " << (zone.available ? "Yes" : "No") << endl;
        cout << "-----------------------------" << endl;
    }
}

void bookZone2(vector<Zone2>& zone2s);
void loadZone2Data(vector<Zone2>& zone2s);  // เพิ่มฟังก์ชันนี้

#endif
