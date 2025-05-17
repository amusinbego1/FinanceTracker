//
// Created by Amer on 17. 5. 2025..
//

#ifndef TRANSACTIONCACHE_H
#define TRANSACTIONCACHE_H

#include "repository/TransactionRepository.h"

class TransactionCache {
public:
    explicit TransactionCache(TransactionRepository& repo)
        : repository_(repo), cacheValid_(false) {}

    const cnt::PushBackVector<Transaction>& findAllTransactions(const User& user) {
        if (!cacheValid_) {
            cache_ = repository_.findTransactionsByUser(user);
            cacheValid_ = true;
        }
        return cache_;
    }

    void invalidate() {
        cacheValid_ = false;
    }

private:
    TransactionRepository& repository_;
    cnt::PushBackVector<Transaction> cache_;
    bool cacheValid_;
};


#endif //TRANSACTIONCACHE_H
