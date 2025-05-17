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

    class Summary{
        td::Decimal2 income_, expense_;

    public:
        Summary(): income_(0.0), expense_(0.0){}

        Summary& addIncome(td::Decimal2 income){
            income_ += income;
            return *this;
        }
        Summary& addExpense(td::Decimal2 expense){
            expense_ += expense;
            return *this;
        }

        td::Decimal2 getIncome() const {return income_;}
        td::Decimal2 getExpense() const {return expense_;}
        td::Decimal2 getBalance() const {return income_ - expense_;}

    };
    std::map<td::INT4, Summary> getMonthlyBreakdown(td::INT4 year);
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
