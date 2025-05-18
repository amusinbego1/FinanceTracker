//
// Created by Amer on 18. 5. 2025..
//

#ifndef TRANSACTIONXMLWRITER_H
#define TRANSACTIONXMLWRITER_H

#include <xml/Writer.h>
#include "domain/Transaction.h"

class TransactionXmlWriter{
public:

    explicit TransactionXmlWriter(const td::String& fileName): writer_(fileName){}

    void write(const std::vector<Transaction>& );

private:
    xml::Writer writer_;
    void writeTransaction(const Transaction&);
    const char* formatDecimal2ToString(const td::Decimal2& number);
};

#endif //TRANSACTIONXMLWRITER_H
