#include "home.h"

int main() {
    int choice;
    while (true) {
        cout << "\n1. Login\n2. Create an account\n3. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (login()) {
                    // Logic after successful login (can be added here)
                }
                break;
            case 2: 
                signUp(); 
                break;
            case 3: 
                cout << "Goodbye!\n"; 
                return 0;
            default: 
                cout << "Invalid choice. Try again.\n";
        }
    }
}
