#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>
#include <repository/TransactionRepository.h>
#include <service/TransactionService.h>

#include "domain/User.h"
#include "repository/UserRepository.h"

int main() {
    try {
        auto &userRepo = UserRepository::getInstance();
        auto &catRepo = CategoryRepository::getInstance();

        std::cout << (userRepo.isConnectionOK() ? "UserRepo Connected" : "Ne valja") << td::endl;
        std::cout << (catRepo.isConnectionOK() ? "CategoryRepo Connected" : "Ne valja") << td::endl;

        User user = userRepo.findUserByUsernameAndPassword("amusinbego1", "amer1234").value();

       TransactionService& service = TransactionService::getInstance(user);

        auto transactions = service.getAllTransactions();
        std::cout << td::endl;
        for (auto &tr: transactions)
            std::cout << to_string(tr.category.type)
                    << " (" << tr.category.name << ") "
                    << ": " << tr.amount << " (" << tr.currency << ") "
                    << "User = " << tr.user.username << " "
                    << "UserId = " << tr.user.id << " "
                    << tr.date << td::endl;

        service.getAllTransactions();
        service.getAllTransactions();
        transactions = service.getAllTransactions(TransactionSortField::NoSort);
        std::cout << td::endl;
        for (auto &tr: transactions)
            std::cout << to_string(tr.category.type)
                    << " (" << tr.category.name << ") "
                    << ": " << tr.amount << " (" << tr.currency << ") "
                    << "User = " << tr.user.username << " "
                    << "UserId = " << tr.user.id << " "
                    << tr.date << td::endl;

        transactions = service.getAllTransactions(TransactionSortField::CategoryNameDesc);
        std::cout << td::endl;
        for (auto &tr: transactions)
            std::cout << to_string(tr.category.type)
                    << " (" << tr.category.name << ") "
                    << ": " << tr.amount << " (" << tr.currency << ") "
                    << "User = " << tr.user.username << " "
                    << "UserId = " << tr.user.id << " "
                    << tr.date << td::endl;

        auto summary = service.getSummary();
        std::cout << td::endl << summary.getBalance() << td::endl;
        std::cout << td::endl << summary.getIncome() << td::endl;
        std::cout << td::endl << summary.getExpense() << td::endl;

        auto expenses = service.getTotalExpensesByCategoryName();
        for (const auto& [category, amount] : expenses) {
            std::cout << category << ": " << amount << " BAM" << td::endl;
        }

        std::cout << "---------------------------------------" << td::endl;

        auto monthlyBreakdown = service.getMonthlyBreakdown(2025);
        for (const auto& [month, summary] : monthlyBreakdown) {
            std::cout << month << " -> Income: " << summary.getIncome()
                      << ", Expense: " << summary.getExpense()
                      << ", Balance: " << summary.getBalance() << " BAM" << td::endl;
        }
        std::cout << "---------------------------------------" << td::endl;

        auto breakdown = service.getDailyBreakdown(2025, 2);

        for (const auto& [date, summary] : breakdown) {
            std::cout << date << ": "
                      << "Income=" << summary.getIncome()
                      << ", Expense=" << summary.getExpense()
                      << ", Balance=" << summary.getBalance() << std::endl;
        }


    } catch (std::exception &e) {
        std::cout << e.what() << td::endl;
    }

    return 0;
}
