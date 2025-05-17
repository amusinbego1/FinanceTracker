#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>
#include <repository/TransactionRepository.h>
#include <service/TransactionService.h>

#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    try {
        auto &userRepo = UserRepository::getInstance();
        auto &catRepo = CategoryRepository::getInstance();

        std::cout << (userRepo.isConnectionOK() ? "UserRepo Connected" : "Ne valja") << td::endl;
        std::cout << (catRepo.isConnectionOK() ? "CategoryRepo Connected" : "Ne valja") << td::endl;

        User user = userRepo.findUserByUsernameAndPassword("amusinbego1", "amer1234").value();

       TransactionService& service = TransactionService::getInstance(user);
        // auto &service = TransactionRepository::getInstance();

        auto transactions = service.findAllTransactions();
        // auto transactions = service.findTransactionsByUser(user);
        std::cout << td::endl;
        for (auto &tr: transactions)
            std::cout << to_string(tr.category.type)
                    << " (" << tr.category.name << ") "
                    << ": " << tr.amount << " (" << tr.currency << ") "
                    << "User = " << tr.user.username << " "
                    << "UserId = " << tr.user.id << " "
                    << tr.date << td::endl;


        transactions = service.findAllTransactions(TransactionSortField::AmountAsc);
        std::cout << td::endl;
        for (auto &tr: transactions)
            std::cout << to_string(tr.category.type)
                    << " (" << tr.category.name << ") "
                    << ": " << tr.amount << " (" << tr.currency << ") "
                    << "User = " << tr.user.username << " "
                    << "UserId = " << tr.user.id << " "
                    << tr.date << td::endl;


    } catch (std::exception &e) {
        std::cout << e.what() << td::endl;
    }

    return 0;
}
