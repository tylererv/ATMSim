#ifndef ATM_H
#define ATM_H

#include "User.h"
#include <string>
#include <vector>

class ATM {
private:
  std::vector<User> users;
  const std::string filename = "users.csv";
  User *currentUser;

  void loadData();
  void saveData();
  User *authenticateUser(std::string id, std::string password);
  void createAccount();
  void displayMenu();
  void checkBalance();
  void deposit();
  void withdraw();

public:
  ATM();
  void start();
};

#endif
