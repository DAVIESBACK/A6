#ifndef ZONE2_H
#define ZONE2_H

#include <iostream>
#include <vector>
#include <algorithm>  // สำหรับ begin() และ end()
using namespace std;

// Structure for Dorm information
struct Zone2 {
    int id;
    string name;
    string location;
    double price;
    bool isAvailable;
};

// Function prototypes
void displayzone2s(const vector<Zone2> &Zone2s) {
    cout << "\n=== All zone Details ===\n";
    for (const auto &Zone2 : Zone2s) {
        cout << "ID: " << Zone2.id << endl;
        cout << "Name: " << Zone2.name << endl;
        cout << "Location: " << Zone2.location << endl;
        cout << "Price: " << Zone2.price << " Baht/month" << endl;
        cout << "Status: " << (Zone2.isAvailable ? "Available" : "Not Available") << endl;
        cout << "-----------------------------" << endl;
    }
}


void bookzone2(vector<Zone2> &Zone2s) {
    int id;
    cout << "\nEnter the zone ID you want to book: ";
    cin >> id;

    for (auto &Zone2 : Zone2s) {
        if (Zone2.id == id) {
            if (Zone2.isAvailable) {
                Zone2.isAvailable = false;
                cout << "Successfully booked " << Zone2.name << "!\n";
            } else {
                cout << "Sorry! This zone is already booked.\n";
            }
            return;
        }
    }
    cout << "No zone found with this ID.\n";
}


#endif
