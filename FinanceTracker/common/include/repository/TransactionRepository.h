//
// Created by Amer on 15. 5. 2025..
//

#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H
#include "BaseRepository.h"
#include "domain/Transaction.h"

class TransactionRepository: public BaseRepository{

    dp::IDataSetPtr _dataSetPtr;

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
    std::vector<Transaction> findTransactionsByUser(const User&);
    dp::IDataSetPtr& findTransactionsByUserIDataSetPtr (const User&);
    void deleteTransactionByID(const Transaction&);
    //

private:
    static const char * INSERT_TRANSACTION_SQL;
    static const char * FIND_TRANSACTIONS_BY_USER_SQL;
    static const char * FIND_TRANSACTIONS_BY_USER_WITH_DATASET_SQL;
    static const char * DELETE_TRANSACTIONS_BY_ID_SQL;

    TransactionRepository() = default;


};

#endif //TRANSACTIONREPOSITORY_H
