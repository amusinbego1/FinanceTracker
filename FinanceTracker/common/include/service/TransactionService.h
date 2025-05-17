//
// Created by Amer on 16. 5. 2025..
//

#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include <map>

#include "domain/Transaction.h"
#include "repository/TransactionRepository.h"
#include "domain/TransactionSortField.h"
#include "repository/cache/TransactionCache.h"
#include "utility/ServiceUtils.h"

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
        TransactionRepository::getInstance().saveTransaction(transaction);
        cache_.invalidate();
    }
    void deleteTransaction(const Transaction& transaction) {
        TransactionRepository::getInstance().deleteTransaction(transaction);
        cache_.invalidate();
    }
    std::vector<Transaction> getAllTransactions(TransactionSortField sortBy = TransactionSortField::DateDesc);
    td::Decimal2 getBalance();
    td::Decimal2 getTotalIncome();
    td::Decimal2 getTotalExpense();
    std::map<td::String, td::Decimal2> getTotalExpensesByCategoryName();
    std::map<td::UINT4, ServiceUtils::Summary> getMonthlyBreakdown(td::INT4 year);
    std::map<td::UINT4, ServiceUtils::Summary> getDailyBreakdown(td::INT4 year, td::UINT4 month);
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
    TransactionCache cache_;

    explicit TransactionService(const User& user)
        : user_(user) {}


};



#endif //TRANSACTIONSERVICE_H
