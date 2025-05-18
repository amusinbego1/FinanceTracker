//
// Created by Amer on 18. 5. 2025..
//

#include "service/TransactionXmlWriter.h"

void TransactionXmlWriter::write(const std::vector<Transaction>& transactions) {
    writer_.startDocument();
        writer_.startNode("Transactions");
        for(const Transaction& transaction: transactions)
            writeTransaction(transaction);
        writer_.endNode();
    writer_.endDocument();
}

void TransactionXmlWriter::writeTransaction(const Transaction& transaction) {
    writer_.startNode("Transaction");
        writer_.attribute("date", transaction.date);
        writer_.attribute("category", transaction.category.name);
        writer_.attribute("type", to_string(transaction.category.type));
        writer_.attribute("currency", transaction.currency);
        writer_.nodeString(formatDecimal2ToString(transaction.amount));
    writer_.endNode();
}

const char* TransactionXmlWriter::formatDecimal2ToString(const td::Decimal2& number) {
    double value = number.getAsFloat();
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", value);
    const char* cstr = buffer;
    return cstr;
}