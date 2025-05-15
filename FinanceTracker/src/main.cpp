#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>
#include <repository/TransactionRepository.h>

#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    try {
        auto & transRepo = TransactionRepository::getInstance();
        auto & catRepo = CategoryRepository::getInstance();

        std::cout << (transRepo.isConnectionOK() ? "Connected" : "Ne valja") << td::endl;

        auto categ = catRepo.findCategoryByNameAndType("rent", CategoryType::EXPENSE).value_or(Category{0, "", CategoryType::INCOME});

        td::Date date;
        date.now();
        Transaction tr{0, User{2, "", ""}, categ, 500, "BAM", date, td::String()};

        transRepo.saveTransaction(tr);

    } catch (std::exception &e) {
        std::cout << e.what() << td::endl;
    }

    return 0;
}
