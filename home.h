#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
};


bool userExists(const string& username) {
    ifstream file("users.txt");
    string storedUser, storedPass;
    while (file >> storedUser >> storedPass) {
        if (storedUser == username) {
            return true;
        }
    }
    return false;
}

void signUp() {
    User newUser;
    cout << "Enter new username: ";
    cin >> newUser.username;
    
    if (userExists(newUser.username)) {
        cout << "Username already exists. Try again.\n";
        return;
    }
    
    cout << "Enter new password: ";
    cin >> newUser.password;
    
    // Password confirmation
    string confirmPassword;
    cout << "Confirm password: ";
    cin >> confirmPassword;

    if (newUser.password != confirmPassword) {
        cout << "Passwords do not match. Try again.\n";
        return;
    }
    
    ofstream file("users.txt", ios::app);
    file << newUser.username << " " << newUser.password << "\n";
    file.close();
    
    cout << "Sign-up successful!\n";
}


bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    ifstream file("users.txt");
    string storedUser, storedPass;
    while (file >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == password) {
            cout << "Login successful!\n";
            return true;
        }
    }
    
    cout << "Invalid username or password.\n";
    return false;
}


#endif
