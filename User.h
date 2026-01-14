#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
  std::string id;
  std::string password;
  double balance;

  User(std::string u, std::string p, double b)
      : id(u), password(p), balance(b) {}
};

#endif
