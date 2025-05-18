//
// Created by Amer on 17. 5. 2025..
//

#ifndef TRANSACTIONCACHE_H
#define TRANSACTIONCACHE_H

#include "repository/TransactionRepository.h"

class TransactionCache {
public:
    explicit TransactionCache()
        : cacheValid_(false) {
    }

    const std::vector<Transaction> &findAllTransactions(const User &user, TransactionSortField sortBy = TransactionSortField::NoSort) {
        if (!cacheValid_) {
            cache_ = TransactionRepository::getInstance().findTransactionsByUser(user);
            cacheValid_ = true;
            sortBy_ = sortBy;
            sortTransaction();
        } else if (sortBy_ != sortBy) {
            sortBy_ = sortBy;
            sortTransaction();
        }
        return cache_;
    }

    void invalidate() {
        cacheValid_ = false;
    }

private:
    std::vector<Transaction> cache_;
    TransactionSortField sortBy_;
    bool cacheValid_;

    void sortTransaction() {

        if (sortBy_ == TransactionSortField::NoSort)
            return;

        std::sort(cache_.begin(), cache_.end(), [&](const Transaction &a, const Transaction &b) {
            switch (sortBy_) {
                case TransactionSortField::DateDesc:
                    return a.date > b.date;
                case TransactionSortField::DateAsc:
                    return a.date < b.date;
                case TransactionSortField::AmountDesc:
                    return a.amount > b.amount;
                case TransactionSortField::AmountAsc:
                    return a.amount < b.amount;
                case TransactionSortField::CategoryNameAsc:
                    return a.category.name.cCompareNoCase(b.category.name.c_str()) < 0;
                case TransactionSortField::CategoryNameDesc:
                    return a.category.name.cCompareNoCase(b.category.name.c_str()) > 0;
                case TransactionSortField::CategoryTypeAsc:
                    return a.category.type > b.category.type;
                case TransactionSortField::CategoryTypeDesc:
                    return a.category.type < b.category.type;
                default:
                    return a.date > b.date;
            }
        });
    }
};


#endif //TRANSACTIONCACHE_H
