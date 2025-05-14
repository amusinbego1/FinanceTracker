#include <iostream>
#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    User user{1, "Nest", "amer1234"};
    std::cout << user.username << td::endl;
    UserRepository& repo = UserRepository::getInstance();

    std::cout << (repo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;
    repo.saveUser(user);
    std::cout << "OK";
    return 0;
}
