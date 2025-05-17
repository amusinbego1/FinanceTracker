//
// Created by Amer on 17. 5. 2025..
//

#ifndef TRANSACTIONCACHE_H
#define TRANSACTIONCACHE_H

#include "repository/TransactionRepository.h"

class TransactionCache {
public:
    explicit TransactionCache()
        :cacheValid_(false) {}

    const std::vector<Transaction>& findAllTransactions(const User& user) {
        if (!cacheValid_) {
            cache_ = TransactionRepository::getInstance().findTransactionsByUser(user);
            cacheValid_ = true;
        }
        return cache_;
    }

    void invalidate() {
        cacheValid_ = false;
    }

private:
    std::vector<Transaction> cache_;
    bool cacheValid_;
};


#endif //TRANSACTIONCACHE_H
