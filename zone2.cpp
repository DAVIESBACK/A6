#include "zone2.h"

int main() {
    vector<Zone2> zone2s = {
        {1, "Phufa Place", "Phufa Lane 21", 4800, true},
        {2, "The Greeny Landmark", "Green Street 55", 5200, true},
        {3, "Pojai Apartment", "Pojai Road 32", 4300, true},
        {4, "Kiang Doi Place", "Doi Street 76", 4700, true},
        {5, "Baan Pranee(Jed Yod)", "Jed Yod 99", 4600 ,true }
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
                displayzone2s(zone2s);
                break;
            case 2:
                bookzone2(zone2s);
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