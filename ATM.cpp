#include "ATM.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

ATM::ATM() {
  currentUser = nullptr;
  loadData();
}

void ATM::loadData() {
  users.clear();
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Could not open data file. Starting with empty database." << endl;
    return;
  }

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    string id, pass, balanceStr;

    if (getline(ss, id, ',') && getline(ss, pass, ',') &&
        getline(ss, balanceStr, ',')) {
      try {
        double balance = stod(balanceStr);
        users.emplace_back(id, pass, balance);
      } catch (...) {
        continue;
      }
    }
  }
  file.close();
}

void ATM::saveData() {
  ofstream file(filename);
  if (!file.is_open()) {
    cout << "Error saving data!" << endl;
    return;
  }

  for (const auto &user : users) {
    file << user.id << "," << user.password << "," << fixed << setprecision(2)
         << user.balance << endl;
  }
  file.close();
}

User *ATM::authenticateUser(string id, string password) {
  for (auto &user : users) {
    if (user.id == id && user.password == password) {
      return &user;
    }
  }
  return nullptr;
}

void ATM::start() {
  cout << "Welcome to the ATM Simulation" << endl;

  while (true) {
    cout << "\n1. Login" << endl;
    cout << "2. Create Account" << endl;
    cout << "3. Exit" << endl;
    cout << "Select an option: ";

    int choice;
    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input." << endl;
      continue;
    }

    if (choice == 1) {
      cout << "\nPlease Login" << endl;
      cout << "User ID: ";
      string id;
      cin >> id;

      cout << "Password: ";
      string pass;
      cin >> pass;

      currentUser = authenticateUser(id, pass);

      if (currentUser != nullptr) {
        cout << "Login Successful!" << endl;
        displayMenu();
        currentUser = nullptr; // Logout after menu returns
      } else {
        cout << "Invalid User ID or Password. Please try again." << endl;
      }
    } else if (choice == 2) {
      createAccount();
    } else if (choice == 3) {
      cout << "Exiting..." << endl;
      cout << "Successfully exited." << endl;
      break;
    } else {
      cout << "Invalid option." << endl;
    }
  }
}

void ATM::createAccount() {
  cout << "\n--- Create Account ---" << endl;
  string id;
  cout << "Enter User ID: ";
  cin >> id;

  for (const auto &user : users) {
    if (user.id == id) {
      cout << "User ID already exists! Please try a different ID." << endl;
      return;
    }
  }

  string pass1, pass2;
  cout << "Enter Password: ";
  cin >> pass1;
  cout << "Confirm Password: ";
  cin >> pass2;

  if (pass1 == pass2) {
    users.emplace_back(id, pass1, 0.0);
    saveData();
    cout << "Account created successfully! You can now login." << endl;
  } else {
    cout << "Passwords do not match! Account creation failed." << endl;
  }
}

void ATM::displayMenu() {
  int choice = 0;
  do {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Logout" << endl;
    cout << "Select an option: ";

    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input." << endl;
      continue;
    }

    switch (choice) {
    case 1:
      checkBalance();
      break;
    case 2:
      deposit();
      break;
    case 3:
      withdraw();
      break;
    case 4:
      cout << "Logging out..." << endl;
      break;
    default:
      cout << "Invalid option." << endl;
    }
  } while (choice != 4);
}

void ATM::checkBalance() {
  cout << "Current Balance: $" << fixed << setprecision(2)
       << currentUser->balance << endl;
}

void ATM::deposit() {
  double amount;
  cout << "Enter amount to deposit: ";
  if (cin >> amount) {
    if (amount > 0) {
      currentUser->balance += amount;
      saveData();
      cout << "Deposit successful. New Balance: $" << currentUser->balance
           << endl;
    } else {
      cout << "Invalid amount. Must be positive." << endl;
    }
  } else {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input." << endl;
  }
}

void ATM::withdraw() {
  double amount;
  cout << "Enter amount to withdraw: ";
  if (cin >> amount) {
    if (amount > 0) {
      if (currentUser->balance >= amount) {
        currentUser->balance -= amount;
        saveData();
        cout << "Withdrawal successful. New Balance: $" << currentUser->balance
             << endl;
      } else {
        cout << "Insufficient funds." << endl;
      }
    } else {
      cout << "Invalid amount. Must be positive." << endl;
    }
  } else {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input." << endl;
  }
}
