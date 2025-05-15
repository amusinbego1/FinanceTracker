//
// Created by Amer on 15. 5. 2025..
//

#include "repository/CategoryRepository.h"

const char* CategoryRepository::INSERT_CATEGORY_SQL = "INSERT INTO categories (name, type) VALUES (?, ?)";
const char* CategoryRepository::FIND_CATEGORY_BY_NAME_AND_TYPE_SQL = "SELECT id FROM categories WHERE name = ? AND type = ?";
const char* CategoryRepository::FIND_CATEGORIES_BY_CATEGORY_TYPE = "SELECT * FROM categories WHERE type = ?";

void CategoryRepository::saveCategory(const Category& category){
    dp::IStatementPtr saveStatPtr(_databasePtr->createStatement(INSERT_CATEGORY_SQL));

    td::Variant b_name(td::string8, td::nch, 30);
    td::Variant b_type(td::string8, td::nch, 10);


    dp::Params params(saveStatPtr->allocParams());
    params << b_name << b_type;

    dp::Transaction transaction(_databasePtr);
    b_name = category.name;
    b_type = to_string(category.type);

    executeStatementAndThrowErrorIfExists(saveStatPtr, transaction);

    transaction.commit();
}

std::optional<Category> CategoryRepository::findCategoryByNameAndType(const td::String& name, const CategoryType& type) {
    td::UINT4 category_id;

    dp::IStatementPtr pStatPtr(_databasePtr->createStatement(FIND_CATEGORY_BY_NAME_AND_TYPE_SQL));

    td::Variant b_name(td::string8, td::nch, 30);
    td::Variant b_type(td::string8, td::nch, 10);

    dp::Columns columns(pStatPtr->allocBindColumns(1));
    columns << "id" << category_id;

    dp::Params params(pStatPtr->allocParams());
    params << b_name << b_type;

    b_name = name;
    b_type = to_string(type);

    if (!pStatPtr->execute() || !pStatPtr->moveNext())
        return std::nullopt;

    return Category{category_id, name, type};
}

cnt::PushBackVector<Category> CategoryRepository::findAllCategories(const CategoryType& type){
    cnt::PushBackVector<Category> categories;
    Category category;
    category.type = type;

    dp::IStatementPtr selectPtr(_databasePtr->createStatement(FIND_CATEGORIES_BY_CATEGORY_TYPE));

    td::Variant b_type(td::string8, td::nch, 10);

    dp::Columns columns(selectPtr->allocBindColumns(2));
    columns << "id" << category.id << "name" << category.name;

    dp::Params params(selectPtr->allocParams());
    params << b_type;
    b_type = to_string(type);

    if (!selectPtr->execute())
        throw std::exception("Something went wrong getting categories...");

    while (selectPtr -> moveNext()) {
        categories.push_back(category);
    }

    return categories;
}

cnt::PushBackVector<Category> CategoryRepository::findAllExpenses() {
    return findAllCategories(CategoryType::EXPENSE);
}

cnt::PushBackVector<Category> CategoryRepository::findAllIncomes() {
    return findAllCategories(CategoryType::INCOME);
}