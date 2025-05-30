//
// Created by Amer on 30. 5. 2025..
//

#include "gui/mainWindow/ExpensePie.h"

double ExpensePie::calculateAngle(int i) const {
    try {
        return expenses.at(expenseNames[i].name)/totalExpense * 360;
    } catch(...) {
        return 0;
    }
}

void ExpensePie::drawPieData() {
    gui::Circle c(radius, radius, radius);
    expenses = _transactionService.getTotalExpensesByCategoryName();
    totalExpense = _transactionService.getSummary().getExpense();

    double acc = 0;
    for(int i=0; i<10; i++) {
        _pies[i].createPie(c, acc, acc + calculateAngle(i), 1.5);
        acc += calculateAngle(i);
        _pies[i].drawFillAndWire(_colors[i], td::ColorID::Black);
    }

}

ExpensePie::ExpensePie(const User& user) : _transactionService(TransactionService::getInstance(user)), _categoryRepository(CategoryRepository::getInstance()) {
    expenseNames = _categoryRepository.findAllExpenses();

    _colorRepr[0].createCircle(gui::Circle(2*radius + small_radius + 15,  2*small_radius + 2, small_radius));
    _colorLabels[0] = expenseNames[0].name;

    for(int i=1; i<10; i++) {
        _colorRepr[i].createCircle(gui::Circle(2*radius + small_radius + 15,  (2*small_radius + 2)*(i+1), small_radius));
        _colorLabels[i] = expenseNames[i].name;
    }

}

void ExpensePie::onDraw(const gui::Rect &rect) {
    for(int i=0; i<10; i++) {
        _colorRepr[i].drawFill(_colors[i]);
        _colorLabels[i].draw(gui::Point(2*radius + 2*small_radius + 20, (2*small_radius + 2)*i + 3), gui::Font::ID::SystemSmaller, td::ColorID::SysText);
    }
    drawPieData();
}

void ExpensePie::updateData() {
    reDraw();
}

