#ifndef ZONE3_H
#define ZONE3_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Zone3 {
    int id;
    string name;
    string address;
    int price;
    bool available;
};

void displayZone3s(const vector<Zone3>& zone3s) {
    for (const auto& zone : zone3s) {
        cout << "ID: " << zone.id << endl;
        cout << "Name: " << zone.name << endl;
        cout << "Address: " << zone.address << endl;
        cout << "Price: " << zone.price << endl;
        cout << "Available: " << (zone.available ? "Yes" : "No") << endl;
        cout << "-----------------------------" << endl;
    }
}

void bookZone3(vector<Zone3>& zone3s);
void loadZone3Data(vector<Zone3>& zone3s);  // เพิ่มฟังก์ชันนี้

#endif
