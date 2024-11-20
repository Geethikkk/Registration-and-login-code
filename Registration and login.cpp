#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream infile("users.txt");
    string username, password;
    while (infile >> username >> password) {
        users[username] = password;
    }
    infile.close();
    return users;
}

void saveUsers(const unordered_map<string, string>& users) {
    ofstream outfile("users.txt");
    for (const auto& user : users) {
        outfile << user.first << " " << user.second << endl;
    }
    outfile.close();
}

void registerUser(unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Try another one.\n";
        return;
    }
    cout << "Enter a new password: ";
    cin >> password;
    users[username] = password;
    saveUsers(users);
    cout << "Registration successful!\n";
}


void loginUser(const unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users.at(username) == password) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void resetPassword(unordered_map<string, string>& users) {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    if (users.find(username) == users.end()) {
        cout << "Username not found.\n";
        return;
    }

    string newPassword;
    cout << "Enter a new password: ";
    cin >> newPassword;

    users[username] = newPassword;
    saveUsers(users);
    cout << "Password reset successful!\n";
}

int main() {
    unordered_map<string, string> users = loadUsers();
    int choice;

    do {
        cout << "\n=== Menu ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                loginUser(users);
                break;
            case 3:
                resetPassword(users);
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

