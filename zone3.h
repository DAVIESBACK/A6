#ifndef ZONE3_H
#define ZONE3_H

#include <iostream>
#include <vector>
#include <algorithm>  // สำหรับ begin() และ end()
using namespace std;

// Structure for Dorm information
struct Zone3 {
    int id;
    string name;
    string location;
    double price;
    bool isAvailable;
};

// Function prototypes
void displayzone3s(const vector<Zone3> &Zone3s) {
    cout << "\n=== All zone Details ===\n";
    for (const auto &Zone3 : Zone3s) {
        cout << "ID: " << Zone3.id << endl;
        cout << "Name: " << Zone3.name << endl;
        cout << "Location: " << Zone3.location << endl;
        cout << "Price: " << Zone3.price << " Baht/month" << endl;
        cout << "Status: " << (Zone3.isAvailable ? "Available" : "Not Available") << endl;
        cout << "-----------------------------" << endl;
    }
}


void bookzone3(vector<Zone3> &Zone3s) {
    int id;
    cout << "\nEnter the zone ID you want to book: ";
    cin >> id;

    for (auto &Zone3 : Zone3s) {
        if (Zone3.id == id) {
            if (Zone3.isAvailable) {
                Zone3.isAvailable = false;
                cout << "Successfully booked " << Zone3.name << "!\n";
            } else {
                cout << "Sorry! This zone is already booked.\n";
            }
            return;
        }
    }
    cout << "No zone found with this ID.\n";
}


#endif
