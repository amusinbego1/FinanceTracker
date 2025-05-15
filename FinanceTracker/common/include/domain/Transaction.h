//
// Created by Amer on 12. 5. 2025..
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "User.h"
#include "Category.h"

struct Transaction {
    td::UINT4 id;
    User user;                         // full User object instead of just userId
    Category category;                 // full Category object instead of categoryId
    td::Decimal2 amount = 0.0;
    td::String currency = "BAM";
    td::Date date;
    td::String description;
};

#endif //TRANSACTION_H
