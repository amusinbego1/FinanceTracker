//
// Created by Amer on 16. 5. 2025..
//

#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include "domain/Transaction.h"
#include "repository/TransactionRepository.h"
#include "domain/TransactionSortField.h"
#include "repository/cache/TransactionCache.h"

class TransactionService {
public:
    static TransactionService& getInstance(const User& user) {
        static TransactionService instance(user);
        return instance;
    }

    TransactionService(const TransactionService&) = delete;
    TransactionService& operator=(const TransactionService&) = delete;
    TransactionService(TransactionService&&) = delete;
    TransactionService& operator=(TransactionService&&) = delete;

    // ----------Interface-----------
    void addNewTransaction(const Transaction& transaction) {
        repository_.saveTransaction(transaction);
        cache_.invalidate();
    }

    void deleteTransaction(const Transaction& transaction) {
        repository_.deleteTransaction(transaction);
        cache_.invalidate();
    }

    cnt::PushBackVector<Transaction> findAllTransactions(TransactionSortField sortBy = TransactionSortField::DateDesc);
    // -------------------------------

    const User& getUser() const {
        return user_;
    }

    void setUser(const User& user) {
        user_ = user;
        cache_.invalidate();
    }

private:
    User user_;
    TransactionRepository& repository_;
    TransactionCache cache_;

    explicit TransactionService(const User& user)
        : user_(user),
          repository_(TransactionRepository::getInstance()),
          cache_(repository_) {}
};



#endif //TRANSACTIONSERVICE_H
