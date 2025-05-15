//
// Created by Amer on 15. 5. 2025..
//

#include "repository/TransactionRepository.h"

const char * TransactionRepository::INSERT_TRANSACTION_SQL = "INSERT INTO transactions ("
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



void TransactionRepository::saveTransaction(const Transaction& transaction) {
    dp::IStatementPtr saveStatPtr(_databasePtr->createStatement(INSERT_TRANSACTION_SQL));

    td::UINT4 b_user_id;
    td::UINT4 b_category_id;
    td::Decimal2 b_amount;
    td::Variant b_currency(td::string8, td::nch, 3);
    td::Date b_date;
    td::Variant b_description(td::string8, td::nch, 100);


    dp::Params params(saveStatPtr->allocParams());
    params << b_user_id << b_category_id << b_amount << b_currency << b_date << b_description;

    dp::Transaction dbTransaction(_databasePtr);
    b_user_id = transaction.user.id;
    b_category_id = transaction.category.id;
    b_amount = transaction.amount;
    b_currency = transaction.currency;
    b_date = transaction.date;
    b_description = transaction.description;

    executeStatementAndThrowErrorIfExists(saveStatPtr, dbTransaction);

    dbTransaction.commit();
}