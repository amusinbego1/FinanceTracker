#include <iostream>
#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    User user{1, "hop", "cup"};
    UserRepository& repo = UserRepository::getInstance();

    std::cout << (repo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;

    repo.saveUser(user);

    auto optionalUser = repo.findUserByUsernameAndPassword(user.username, user.password);

    if (optionalUser.has_value())
        std::cout << optionalUser->id << " " << optionalUser->username << " " << optionalUser->password << td::endl;
    else
        std::cout << "There is NO such user..." << td::endl;

    std::cout << "Press any key to continue...";
    std::cin.get();

    repo.deleteUserByUsernameAndPassword(user.username, user.password);

    auto optionalUser2 = repo.findUserByUsernameAndPassword(user.username, user.password);

    if (optionalUser2.has_value())
        std::cout << optionalUser2->id << " " << optionalUser2->username << " " << optionalUser2->password << td::endl;
    else
        std::cout << "There is NO such user..." << td::endl;


    return 0;
}
