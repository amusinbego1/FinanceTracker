#include <iostream>
#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    User user{1, "Nest", "Mest"};
    std::cout << user.username << td::endl;
    UserRepository& repo = UserRepository::getInstance();

    std::cout << (repo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;

    return 0;
}
