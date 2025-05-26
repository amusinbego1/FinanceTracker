//
// Created by Amer on 14. 5. 2025..
//

#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include "BaseRepository.h"
#include "domain/Category.h"

class CategoryRepository: public BaseRepository{
public:
    static CategoryRepository& getInstance() {
        static CategoryRepository instance;
        return instance;
    }

    CategoryRepository(const CategoryRepository&) = delete;
    CategoryRepository& operator=(const CategoryRepository&) = delete;
    CategoryRepository(CategoryRepository&&) = delete;
    CategoryRepository& operator=(CategoryRepository&&) = delete;

    //Interface
    void saveCategory(const Category&);
    std::optional<Category> findCategoryByNameAndType(const td::String& name, const CategoryType& type);
    std::vector<Category> findAllExpenses();
    std::vector<Category> findAllIncomes();
    //

private:
	static const char * INSERT_CATEGORY_SQL;
    static const char * FIND_CATEGORY_BY_NAME_AND_TYPE_SQL;
    static const char * FIND_CATEGORIES_BY_CATEGORY_TYPE_SQL;

    CategoryRepository() = default;

    std::vector<Category> findAllCategories(const CategoryType&);

};

#endif //CATEGORYREPOSITORY_H
