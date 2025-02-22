#ifndef ZONE1_H
#define ZONE1_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Zone1 {
    int id;
    string name;
    string address;
    int price;
    bool available;
};

void displayZone1s(const vector<Zone1>& zone1s) {
    for (const auto& zone : zone1s) {
        cout << "ID: " << zone.id << endl;
        cout << "Name: " << zone.name << endl;
        cout << "Address: " << zone.address << endl;
        cout << "Price: " << zone.price << endl;
        cout << "Available: " << (zone.available ? "Yes" : "No") << endl;
        cout << "-----------------------------" << endl;
    }
}

void bookZone1(vector<Zone1>& zone1s);
void loadZone1Data(vector<Zone1>& zone1s);  // เพิ่มฟังก์ชันนี้

#endif
