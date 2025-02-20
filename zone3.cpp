#include "zone3.h"

int main() {
    vector<Zone3> zone3s = {
        {1, "Warisa Apartment", "Warisa Road 12", 4900, true},
        {2, "P.S Mansion", "PS Street 34", 5300, true},
        {3, "Baan Tarnkam", "Tankam Road 78", 4200, true},
        {4, "Tarnthong Place Apartment Chiangmai", "Tarnthong Road 90", 5100, true},
        {5, "Thongtara Monte", "Monte Street 109", 5700 ,true }
    };

    int choice;
    do {
        cout << "\n=== zone Booking System ===\n";
        cout << "1. Display All zone Details\n";
        cout << "2. Book a zone\n";
        cout << "3. Exit\n";
        cout << "Please choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayzone3s(zone3s);
                break;
            case 2:
                bookzone3(zone3s);
                break;
            case 3:
                cout << "Thank you for using our service!\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (choice != 3);

    return 0;
}