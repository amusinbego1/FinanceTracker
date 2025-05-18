//
// Created by Amer on 16. 5. 2025..
//

#include "service/TransactionService.h"

#include <map>

const std::vector<Transaction>& TransactionService::getAllTransactions(TransactionSortField sortBy) {
    return cache_.findAllTransactions(user_, sortBy);
}


ServiceUtils::Summary TransactionService::getSummary() {
    const auto& transactions = cache_.findAllTransactions(user_);
    ServiceUtils::Summary summary;
    for(const auto& transaction: transactions) {

        if (transaction.category.type == CategoryType::INCOME)
            summary.addIncome(transaction.amount);
        else
            summary.addExpense(transaction.amount);
    }
    return summary;
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
