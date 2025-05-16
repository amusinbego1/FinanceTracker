#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>
#include <repository/TransactionRepository.h>

#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    try {
        auto & transRepo = TransactionRepository::getInstance();
        auto & userRepo = UserRepository::getInstance();

        std::cout << (transRepo.isConnectionOK() ? "TransactionRepo Connected" : "Ne valja") << td::endl;
        std::cout << (userRepo.isConnectionOK() ? "UserRepo Connected" : "Ne valja") << td::endl;

        User user = userRepo.findUserByUsernameAndPassword("amusinbego1", "amer1234").value();
        cnt::PushBackVector<Transaction> transactionsAmer = transRepo.findTransactionsByUser(user);

        for(auto& tr: transactionsAmer)
            std::cout << to_string(tr.category.type) << ": " << tr.amount + 1 << " (" << tr.currency << ")"
                      << tr.date.getDay() << td::endl;


    } catch (std::exception &e) {
        std::cout << e.what() << td::endl;
    }

    return 0;
}
