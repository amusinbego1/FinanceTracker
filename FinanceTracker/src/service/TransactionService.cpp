//
// Created by Amer on 16. 5. 2025..
//

#include "service/TransactionService.h"

cnt::PushBackVector<Transaction> TransactionService::findAllTransactions(TransactionSortField sortBy) {
    auto transactions = cache_.findAllTransactions(user_);

    // cnt::PushBackVector<Transaction> sorted = transactions;

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
