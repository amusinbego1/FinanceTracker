//
// Created by Amer on 16. 5. 2025..
//

#include "service/TransactionService.h"

#include <map>

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

td::Decimal2 TransactionService::getTotalIncome() {
    const auto& transactions = cache_.findAllTransactions(user_);
    td::Decimal2 totalIncome = 0.0;
    for(const auto& transaction: transactions)
        totalIncome += (transaction.category.type == CategoryType::INCOME ? transaction.amount : 0.0);
    return totalIncome;
}

td::Decimal2 TransactionService::getTotalExpense() {
    const auto& transactions = cache_.findAllTransactions(user_);
    td::Decimal2 totalExpense = 0.0;
    for(const auto& transaction: transactions)
        totalExpense += (transaction.category.type == CategoryType::EXPENSE ? transaction.amount : 0.0);
    return totalExpense;
}

std::map<td::String, td::Decimal2> TransactionService::getTotalExpensesByCategoryName() {
    std::map<td::String, td::Decimal2> expensesByCategory;
    const auto& transactions = cache_.findAllTransactions(user_);

    for (const auto& transaction : transactions) {
        if (transaction.category.type == CategoryType::EXPENSE) {
            const td::String& categoryName = transaction.category.name;
            if (expensesByCategory.count(categoryName) == 0)
                expensesByCategory[categoryName] = 0.0;
            expensesByCategory[categoryName] += transaction.amount;
        }
    }

    return expensesByCategory;
}

std::map<td::UINT4, ServiceUtils::Summary> TransactionService::getMonthlyBreakdown(td::INT4 year) {
    std::map<td::UINT4, ServiceUtils::Summary> monthlyData;
    const auto& transactions = cache_.findAllTransactions(user_);

    for (const auto& transaction : transactions) {
        if (transaction.date.getYear() == year) {
            if (transaction.category.type == CategoryType::INCOME) {
                monthlyData[transaction.date.getMonth()].addIncome(transaction.amount);
            } else if (transaction.category.type == CategoryType::EXPENSE) {
                monthlyData[transaction.date.getMonth()].addExpense(transaction.amount);
            }
        }
    }

    for (int i = 1; i<=12; i++) monthlyData[i];

    return monthlyData;
}


std::map<td::UINT4, ServiceUtils::Summary> TransactionService::getDailyBreakdown(td::INT4 year, td::UINT4 month) {
    std::map<td::UINT4, ServiceUtils::Summary> dailyData;
    const auto& transactions = cache_.findAllTransactions(user_);

    for (const auto& transaction : transactions) {
        if (transaction.date.getYear() == year && transaction.date.getMonth() == month) {
            if (transaction.category.type == CategoryType::INCOME) {
                dailyData[transaction.date.getDay()].addIncome(transaction.amount);
            } else if (transaction.category.type == CategoryType::EXPENSE) {
                dailyData[transaction.date.getDay()].addExpense(transaction.amount);
            }
        }
    }

    for (int i = 1; i <= ServiceUtils::getDaysInMonth(year, month); i++) dailyData[i];

    return dailyData;
}
