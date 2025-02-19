#ifndef ZONE1_H
#define ZONE1_H

#include <iostream>
#include <vector>
#include <algorithm>  // สำหรับ begin() และ end()
using namespace std;

// Structure for Dorm information
struct Zone1 {
    int id;
    string name;
    string location;
    double price;
    bool isAvailable;
};

// Function prototypes
void displayzone1s(const vector<Zone1> &Zone1s) {
    cout << "\n=== All zone Details ===\n";
    for (const auto &Zone1 : Zone1s) {
        cout << "ID: " << Zone1.id << endl;
        cout << "Name: " << Zone1.name << endl;
        cout << "Location: " << Zone1.location << endl;
        cout << "Price: " << Zone1.price << " Baht/month" << endl;
        cout << "Status: " << (Zone1.isAvailable ? "Available" : "Not Available") << endl;
        cout << "-----------------------------" << endl;
    }
}


void bookzone1(vector<Zone1> &Zone1s) {
    int id;
    cout << "\nEnter the zone ID you want to book: ";
    cin >> id;

    for (auto &Zone1 : Zone1s) {
        if (Zone1.id == id) {
            if (Zone1.isAvailable) {
                Zone1.isAvailable = false;
                cout << "Successfully booked " << Zone1.name << "!\n";
            } else {
                cout << "Sorry! This zone is already booked.\n";
            }
            return;
        }
    }
    cout << "No zone found with this ID.\n";
}


#endif
