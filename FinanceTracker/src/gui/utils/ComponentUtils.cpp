//
// Created by Amer on 26. 5. 2025..
//

#include "gui/utils/ComponentUtils.h"

std::vector<td::String> ComponentUtils::expenses;
std::vector<td::String> ComponentUtils::incomes;
CategoryRepository &ComponentUtils::category_repo = CategoryRepository::getInstance();

void ComponentUtils::setDefaultButtonStyle(gui::Control &button) {
    button.setSize(gui::Size(75, 40));
    button.setFont(gui::Font::ID::SystemBold);
}

void ComponentUtils::setOverviewButtonStyle(gui::Control &button) {
    button.setSize(gui::Size(170, 35));
    button.setFont(gui::Font::ID::SystemLargerBold);
    button.setBackgroundColor(td::ColorID::DodgerBlue);
}

void ComponentUtils::setTitleStyle(gui::Control &label) {
    label.setFont(gui::Font::ID::SystemLargestBold);
    label.setTextColor(td::Accent::Plain);
}

void ComponentUtils::setLabelWarningStyle(gui::Control &label) {
    label.setTextColor(td::Accent::Critical);
    label.hide(true, true);
}

void ComponentUtils::openWindow(gui::Window *parentWindow, gui::Window *window) {
    window->keepOnTopOfParent();
    // parentWindow->close();
    window->open();
}

const std::vector<td::String> ComponentUtils::getExpenses() {
    if (expenses.empty()) {
        auto exp = category_repo.findAllExpenses();

        for (const auto &category: exp)
            expenses.push_back(category.name);
    }
    return expenses;
}

const std::vector<td::String> ComponentUtils::getIncomes() {
    if (incomes.empty()) {
        auto exp = category_repo.findAllIncomes();

        for (const auto &category: exp)
            incomes.push_back(category.name);
    }
    return incomes;
}

const std::vector<td::String> ComponentUtils::getCategoriesTypes() {
    return {"INCOME", "EXPENSE"};
}

const std::vector<std::vector<td::String> > ComponentUtils::getCategories() {
    return {getIncomes(), getExpenses()};
}

