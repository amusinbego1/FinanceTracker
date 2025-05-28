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

inline CategoryType from_string(const std::string& str) {
    if (str == "INCOME") {
        return CategoryType::INCOME;
    } else if (str == "EXPENSE") {
        return CategoryType::EXPENSE;
    } else {
        throw std::invalid_argument("Invalid CategoryType string: " + str);
    }
}

struct Category {
    td::INT4 id;
    td::String name;
    CategoryType type;
};


#endif //CATEGORY_H
