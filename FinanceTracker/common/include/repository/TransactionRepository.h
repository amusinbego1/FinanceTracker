//
// Created by Amer on 15. 5. 2025..
//

#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H
#include "BaseRepository.h"
#include "domain/Transaction.h"

class TransactionRepository: public BaseRepository{
public:
    static TransactionRepository& getInstance() {
        static TransactionRepository instance;
        return instance;
    }

    TransactionRepository(const TransactionRepository&) = delete;
    TransactionRepository& operator=(const TransactionRepository&) = delete;
    TransactionRepository(TransactionRepository&&) = delete;
    TransactionRepository& operator=(TransactionRepository&&) = delete;

    //Interface
    void saveTransaction(const Transaction&);
    cnt::PushBackVector<Transaction> findTransactionsByUser(const User&);
    //

private:
    static const char * INSERT_TRANSACTION_SQL;
    static const char * FIND_TRANSACTIONS_BY_USER_SQL;
    static const char * FIND_CATEGORIES_BY_CATEGORY_TYPE_S;

    TransactionRepository() = default;


};

#endif //TRANSACTIONREPOSITORY_H
