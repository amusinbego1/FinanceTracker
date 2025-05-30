//
// Created by Amer on 29. 5. 2025..
//

#ifndef PIE_H
#define PIE_H

#include <domain/Category.h>
#include <gui/Canvas.h>
#include <gui/Shape.h>
#include <gui/DrawableString.h>
#include <repository/CategoryRepository.h>
#include <service/TransactionService.h>

class ExpensePie : public gui::Canvas {
    TransactionService& _transactionService;
    CategoryRepository& _categoryRepository;

    std::vector<Category> expenseNames;
    std::map<td::String, td::Decimal2> expenses;
    td::Decimal2 totalExpense;

    gui::Shape _pies[10];
    gui::Shape _colorRepr[10];
    gui::DrawableString _colorLabels[10];

    const double radius = 65;
    const double small_radius = 5;
    const td::ColorID _colors[10] = {
        td::ColorID::Tomato,
        td::ColorID::Gold,
        td::ColorID::MediumSeaGreen,
        td::ColorID::DodgerBlue,
        td::ColorID::Orchid,
        td::ColorID::SandyBrown,
        td::ColorID::SlateBlue,
        td::ColorID::MediumTurquoise,
        td::ColorID::HotPink,
        td::ColorID::DarkOliveGreen
    };


    double calculateAngle(int i) const;
    void drawPieData();

public:
    explicit ExpensePie(const User& user);
    void onDraw(const gui::Rect &rect) override;
    void updateData();
};

#endif //PIE_H
