//
// Created by Amer on 24. 5. 2025..
//

#ifndef COMPONENTSTYLE_H
#define COMPONENTSTYLE_H

#include <gui/Control.h>
#include <gui/Window.h>
#include <repository/CategoryRepository.h>

class ComponentUtils{
    static std::vector<td::String> expenses;
    static std::vector<td::String> incomes;
    static CategoryRepository &category_repo;
public:

    static void setDefaultButtonStyle(gui::Control& button);
    static void setOverviewButtonStyle(gui::Control& button);
    static void setTitleStyle(gui::Control& label);
    static void setLabelWarningStyle(gui::Control& label);
    static void openWindow(gui::Window* parentWindow, gui::Window* window);
    static const std::vector<td::String> getExpenses();
    static const std::vector<td::String> getIncomes();
    static const std::vector<td::String> getCategoriesTypes();
    static const std::vector<std::vector<td::String>> getCategories();
};

#endif //COMPONENTSTYLE_H
