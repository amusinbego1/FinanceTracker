//
// Created by Amer on 16. 5. 2025..
//

#include "service/TransactionService.h"

std::vector<Transaction> TransactionService::getAllTransactions(TransactionSortField sortBy) {
    auto transactions = cache_.findAllTransactions(user_);

    std::sort(transactions.begin(), transactions.end(), [&](const Transaction& a, const Transaction& b) {
   switch (sortBy) {
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

    return transactions;
}

td::Decimal2 TransactionService::getBalance() {
    const auto& transactions = cache_.findAllTransactions(user_);
    td::Decimal2 balance = 0.0;
    for(const auto& transaction: transactions)
        balance += (transaction.category.type == CategoryType::INCOME ? transaction.amount : transaction.amount*-1);
    return balance;
}
