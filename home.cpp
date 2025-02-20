#include "home.h"

int main() {
    int choice;
    while (true) {
        cout << "\n1. Login\n2. Sign Up\n3. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: login(); break;
            case 2: signUp(); break;
            case 3: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}
