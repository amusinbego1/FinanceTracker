//
// Created by Amer on 15. 5. 2025..
//

#include "repository/TransactionRepository.h"

const char *TransactionRepository::INSERT_TRANSACTION_SQL = "INSERT INTO transactions ("
        "user_id,"
        "category_id,"
        "amount,"
        "currency,"
        "date,"
        "description"
        ") VALUES ("
        "?,"
        "?,"
        "?,"
        "?,"
        "?,"
        "?"
        ")";

const char *TransactionRepository::FIND_TRANSACTIONS_BY_USER_SQL = "SELECT "
        "tr.id, "
        "cat.id cat_id, "
        "cat.name cat_name, "
        "cat.type cat_type, "
        "tr.amount, "
        "tr.currency, "
        "tr.date, "
        "tr.description "
        "FROM transactions tr "
        "JOIN categories cat "
        "ON (cat.id = tr.category_id) "
        "WHERE user_id = ?";

const char * TransactionRepository::DELETE_TRANSACTIONS_BY_ID_SQL = "DELETE FROM transactions WHERE id = ?";

void TransactionRepository::saveTransaction(const Transaction &transaction) {
    dp::IStatementPtr saveStatPtr(_databasePtr->createStatement(INSERT_TRANSACTION_SQL));

    td::UINT4 b_user_id;
    td::UINT4 b_category_id;
    td::Decimal2 b_amount;
    td::Variant b_currency(td::string8, td::nch, 3);
    td::Date b_date;
    b_date.now();
    td::Variant b_description(td::string8, td::nch, 100);


    dp::Params params(saveStatPtr->allocParams());
    params << b_user_id << b_category_id << b_amount << b_currency << b_date << b_description;

    dp::Transaction dbTransaction(_databasePtr);
    b_user_id = transaction.user.id;
    b_category_id = transaction.category.id;
    b_amount = transaction.amount;
    b_currency = transaction.currency;
    if (!transaction.date.isNull())
        b_date = transaction.date;
    b_description = transaction.description;

    executeStatementAndThrowErrorIfExists(saveStatPtr, dbTransaction);

    dbTransaction.commit();
}


std::vector<Transaction> TransactionRepository::findTransactionsByUser(const User &user) {
    std::vector<Transaction> transactions;
    Transaction transaction;
    td::String tr_cat_type_str;
    transaction.user = user;

    dp::IDataSetPtr selectPtr(_databasePtr->createDataSet(FIND_TRANSACTIONS_BY_USER_SQL));

    td::Variant b_user_id(td::int4);

    dp::DSColumns columns(selectPtr->allocBindColumns(8));
    columns << "id" << transaction.id
            << "cat_id" << transaction.category.id
            << "cat_name" << transaction.category.name
            << "cat_type" << tr_cat_type_str
            << "amount" << transaction.amount
            << "currency" << transaction.currency
            << "date" << transaction.date
            << "description" << transaction.description;

    dp::Params params(selectPtr->allocParams());
    params << b_user_id;
    b_user_id = user.id;

    if (!selectPtr->execute())
        throw std::exception("Something went wrong getting transactions by user...");

    while (selectPtr->moveNext()) {
        transaction.category.type = from_string(tr_cat_type_str.c_str());
        transactions.push_back(transaction);
    }

    return transactions;
}

void TransactionRepository::deleteTransaction(const Transaction & transaction) {
    dp::IStatementPtr deletePtr(_databasePtr->createStatement(DELETE_TRANSACTIONS_BY_ID_SQL));

    td::Variant b_id(td::int4);

    dp::Params params(deletePtr->allocParams());
    params << b_id;

    dp::Transaction dbTransaction(_databasePtr);
    b_id = transaction.id;
    executeStatementAndThrowErrorIfExists(deletePtr, dbTransaction);

    dbTransaction.commit();

}

