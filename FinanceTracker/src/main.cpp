#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>

#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    try {
        auto &repo = CategoryRepository::getInstance();

        std::cout << (repo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;

        cnt::PushBackVector<Category> categories = repo.findAllIncomes();
        for(auto& cat: categories)
            std::cout << cat.id << ": " << cat.name << " " << to_string(cat.type) << td::endl;

    } catch (std::exception &e) {
        std::cout << e.what() << td::endl;
    }

    return 0;
}
