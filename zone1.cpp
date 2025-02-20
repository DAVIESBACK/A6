#include "zone1.h"

int main() {
    vector<Zone1> zone1s = {
        {1, "Uniloft Chiangmai", "Chiangmai Road 123", 6300, true},
        {2, "Home Hills", "Hillside Road 45", 4500, true},
        {3, "Baan Im Rak", "Rak Street 67", 4000, true},
        {4, "Sanguanmalee Mansion", "Sanguan Road 89", 5500, true},
        {5, "Kai Golden Place", "Golden Road 101", 6000, true }
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
                displayzone1s(zone1s);
                break;
            case 2:
                bookzone1(zone1s);
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