//
// Created by Amer on 12. 5. 2025..
//

#ifndef CATEGORY_H
#define CATEGORY_H

#include <td/String.h>

enum class CategoryType {
    INCOME,
    EXPENSE
};

inline td::String to_string(CategoryType type) {
    switch (type) {
        case CategoryType::INCOME: return "INCOME";
        case CategoryType::EXPENSE: return "EXPENSE";
        default: return "";
    }
}

struct Category {
    td::UINT4 id;
    td::String name;
    CategoryType type;
};


#endif //CATEGORY_H
