#include "sign_up.h"
#include "zone1.h"
#include "zone2.h"
#include "zone3.h"
#include "home.h"
#include "hotel.h"
#include "info.h"
#include "zoneMenu.h"
#include "result.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int choice;
   
    while (true) {
        cout << "\n1. Login\n2. Create an account\n3. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (login()) {
                    
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
