#include <iostream>
#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    User user{1, "amusinbego1", "amer1234"};
    std::cout << user.username << td::endl;
    UserRepository& repo = UserRepository::getInstance();

    std::cout << (repo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;
    auto optionalUser = repo.findUserByUsernameAndPassword(user.username, user.password);

    if (optionalUser.has_value())
        std::cout << optionalUser->id << " " << optionalUser->username << " " << optionalUser->password << td::endl;
    else
        std::cout << "There is NO such user..." << td::endl;
    return 0;
}
