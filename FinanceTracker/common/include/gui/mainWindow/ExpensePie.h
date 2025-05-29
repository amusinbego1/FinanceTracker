//
// Created by Amer on 29. 5. 2025..
//

#ifndef PIE_H
#define PIE_H

#include <gui/Canvas.h>
#include <gui/Shape.h>
#include <gui/DrawableString.h>

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
    td::ColorID _colors[10] = {
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

    const char* to_string(td::ColorID color_id) {
        switch (color_id) {
            case td::ColorID::Tomato: return "Tomato";
            case td::ColorID::Gold: return "Gold";
            case td::ColorID::MediumSeaGreen: return "MediumSeaGreen";
            case td::ColorID::DodgerBlue: return "DodgerBlue";
            case td::ColorID::Orchid: return "Orchid";
            case td::ColorID::SandyBrown: return "SandyBrown";
            case td::ColorID::SlateBlue: return "SlateBlue";
            case td::ColorID::MediumTurquoise: return "MediumTurquoise";
            case td::ColorID::HotPink: return "HotPink";
            case td::ColorID::DarkOliveGreen: return "DarkOliveGreen";
            default: return "Unknown";
        }
    }


    double calculateAngle(int i) {
        try {
            return expenses.at(expenseNames[i].name)/totalExpense * 360;
        } catch(...) {
            return 0;
        }
    }

    void drawPieData() {
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

public:
    ExpensePie(User user) : _transactionService(TransactionService::getInstance(user)), _categoryRepository(CategoryRepository::getInstance()) {
        expenseNames = _categoryRepository.findAllExpenses();

        _colorRepr[0].createCircle(gui::Circle(2*radius + small_radius + 15,  2*small_radius + 2, small_radius));
        _colorLabels[0] = expenseNames[0].name;

        for(int i=1; i<10; i++) {
            _colorRepr[i].createCircle(gui::Circle(2*radius + small_radius + 15,  (2*small_radius + 2)*(i+1), small_radius));
            _colorLabels[i] = expenseNames[i].name;
        }

    }

    void onDraw(const gui::Rect &rect) override {
        for(int i=0; i<10; i++) {
            _colorRepr[i].drawFill(_colors[i]);
            _colorLabels[i].draw(gui::Point(2*radius + 2*small_radius + 20, (2*small_radius + 2)*i + 3), gui::Font::ID::SystemSmaller, td::ColorID::SysText);
        }
        drawPieData();
    }


    void updateData() {
        reDraw();
    }
};

#endif //PIE_H
