#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Dormitory {
    string name;
    int availableRooms;
    string address;
    double price;

    string getStatus() const {
        return availableRooms > 0 ? "Available" : "Full";
    }
};

map<string, vector<Dormitory>> zones = {
    {"Zone 1", { {"Uniloft Chiangmai", 5, "Chiangmai Road 123", 5000}, {"Home Hills", 5, "Hillside Road 45", 4500}, {"Baan Im Rak", 5, "Rak Street 67", 4000}, {"Sanguanmalee Mansion", 5, "Sanguan Road 89", 5500}, {"Kai Golden Place", 5, "Golden Road 101", 6000} }},
    {"Zone 2", { {"Phufa Place", 5, "Phufa Lane 21", 4800}, {"The Greenery Landmark", 5, "Green Street 55", 5200}, {"Pojai Apartment", 5, "Pojai Road 32", 4300}, {"Kiang Doi Place", 5, "Doi Street 76", 4700}, {"Baan Pranee (Jed Yod)", 5, "Jed Yod 99", 4600} }},
    {"Zone 3", { {"Warisa Apartment", 5, "Warisa Road 12", 4900}, {"P.S. Mansion", 5, "PS Street 34", 5300}, {"Baan Tarnkam", 5, "Tarnkam Road 78", 4200}, {"Tarnthong Place Apartment Chiangmai", 5, "Tarnthong Road 90", 5100}, {"Thongtara Monte", 5, "Monte Street 109", 5700} }}
};

void saveBooking(string user, string dormName) {
    ofstream file("bookings.txt", ios::app);
    file << user << " booked " << dormName << endl;
    file.close();
}

void viewBookings(string user) {
    ifstream file("bookings.txt");
    string line;
    cout << "\n===== Booking History =====\n";
    while (getline(file, line)) {
        if (line.find(user) != string::npos) {
            cout << line << "\n";
        }
    }
    file.close();
}

void viewDormitoryDetails(string user, string zone, int dormIndex) {
    Dormitory& dorm = zones[zone][dormIndex];
    cout << "\n===== Dormitory Details =====\n";
    cout << "Name: " << dorm.name << "\n";
    cout << "Address: " << dorm.address << "\n";
    cout << "Price: " << dorm.price << " THB/month\n";
    cout << "Available Rooms: " << dorm.availableRooms << "\n";
    cout << "Status: " << dorm.getStatus() << "\n";
    if (dorm.availableRooms > 0) {
        char confirm;
        cout << "Do you want to book this dormitory? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            dorm.availableRooms--;
            saveBooking(user, dorm.name);
            cout << "Booking successful!\n";
        }
    }
}

void zonePage(string user, string zone) {
    int choice;
    cout << "\n===== " << zone << " =====\n";
    for (int i = 0; i < 5; i++) {
        cout << "[" << i + 1 << "] " << zones[zone][i].name << " (" << zones[zone][i].getStatus() << ")\n";
    }
    cout << "[0] Back\nSelect an option: ";
    cin >> choice;
    if (choice >= 1 && choice <= 5) {
        viewDormitoryDetails(user, zone, choice - 1);
    }
}

void homePage(string user) {
    int choice;
    while (true) {
        cout << "\n===== HOME PAGE =====\n";
        cout << "[1] Zone 1\n";
        cout << "[2] Zone 2\n";
        cout << "[3] Zone 3\n";
        cout << "[4] View Booking History\n";
        cout << "[0] Logout\nSelect an option: ";
        cin >> choice;
        if (choice == 1) zonePage(user, "Zone 1");
        else if (choice == 2) zonePage(user, "Zone 2");
        else if (choice == 3) zonePage(user, "Zone 3");
        else if (choice == 4) viewBookings(user);
        else if (choice == 0) return;
        else cout << "Invalid choice!\n";
    }
}

bool isUserExists(string username) {
    ifstream file("winna.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) return true;
    }
    return false;
}

void signUp() {
    string username, password, confirmPassword;

    while (true) {
        cout << "\n===== SIGN UP =====\n";
        cout << "Username: ";
        cin >> username;

        if (isUserExists(username)) {
            cout << " This username already exists! Try again\n";
            continue;
        }

        cout << "Password: ";
        cin >> password;
        cout << "Confirm Password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << " Passwords do not match! Try again\n";
            continue;
        }

        ofstream file("winna.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << " Sign-up successful!\n";
        return;
    }
}

bool login(string& user) {
    string username, password, userFile, passFile;
    cout << "\n===== LOGIN =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    ifstream file("winna.txt");
    while (file >> userFile >> passFile) {
        if (userFile == username && passFile == password) {
            user = username;
            return true;
        }
    }
    return false;
}

void startApp() {
    int choice;
    string loggedInUser;

    while (true) {
        cout << "\n===== Dormitory Booking System =====\n";
        cout << "[1] Login \n";
        cout << "[2] Sign Up \n";
        cout << "[0] Exit \n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (login(loggedInUser)) {
                    cout << " Login successful!\n";
                    homePage(loggedInUser);
                } else {
                    cout << " Invalid username or password!\n";
                }
                break;
            case 2:
                signUp();
                break;
            case 0:
                cout << " Exiting the program...\n";
                return;
            default:
                cout << " Please select a valid option!\n";
        }
    }
}

int main() {
    startApp();
    return 0;
}
