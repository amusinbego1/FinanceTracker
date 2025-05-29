//
// Created by Amer on 28. 5. 2025..
//

#ifndef GRAPH_H
#define GRAPH_H

#include <gui/Canvas.h>
#include <gui/Shape.h>
#include <gui/DrawableString.h>

class Graph : public gui::Canvas {
    const int _y_max = 160, _x_max = 480 + 60, _step = 40, _radius = 4, _x_begin = 60;
    gui::Shape _xAxis;
    gui::Shape _yAxis;
    gui::Shape _circles;
    gui::Shape _dashes[5];
    TransactionService &_transactionService;
    std::map<int, ServiceUtils::Summary> _breakdown;
    gui::Circle points[12];
    gui::DrawableString _months[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    gui::DrawableString _labels[5];

    td::String _dataType;
    using SummaryFunction = double(*)(const ServiceUtils::Summary &);
    std::map<td::String, SummaryFunction> getData = {
        {"Balance", &ServiceUtils::getBalanceWrapper},
        {"Income", &ServiceUtils::getIncomeWrapper},
        {"Expense", &ServiceUtils::getExpenseWrapper}
    };


    double getMaxOfData() {
        double max = getData[_dataType](_breakdown[1]);
        for (int i = 2; i <= 12; i++)
            if (getData[_dataType](_breakdown[i]) > max)
                max = getData[_dataType](_breakdown[i]);
        return max + _radius;
    }

    const char *formatDecimal2ToString(const td::Decimal2 &number) {
        double value = number.getAsFloat();
        char buffer[32];
        sprintf_s(buffer, sizeof(buffer), "%.2f", value);
        const char *cstr = buffer;
        return cstr;
    }

public:
    Graph(User user): _transactionService(TransactionService::getInstance(user)), _dataType("Balance") {
        _xAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, 0), gui::Point(_x_begin, _y_max)}, 2);
        _yAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, _y_max), gui::Point(_x_max, _y_max)}, 2);
        for (int i = 0; i < 5; i++) {
            _dashes[i].createLines(new gui::Point[2]{gui::Point(_x_begin - _radius, i * _step), gui::Point(_x_begin + _radius, i * _step)}, 2);
        }

    }


    void onDraw(const gui::Rect &rect) override {
        _xAxis.drawWire(td::ColorID::Black, 2.5);
        _yAxis.drawWire(td::ColorID::Black, 2.5);
        for (int i = 0; i < 12; i++) {
            if (i < 5)
                _dashes[i].drawWire(td::ColorID::Black, 4);
            _months[i].draw(gui::Point(_x_begin + i * _step - 5, _y_max + 5), gui::Font::ID::SystemSmaller, td::ColorID::DodgerBlue);
        }

        drawGraphData();

        _circles.createCircles(points, 12);
        _circles.drawFill(td::ColorID::DodgerBlue);
    }

    void changeDataType(const td::String& dataType) {
        _dataType = dataType;
        reDraw();
    }

    void drawGraphData() {
        td::Date date; date.now();
        _breakdown = _transactionService.getMonthlyBreakdown(date.getYear());
        double maxData = getMaxOfData();

        for (int i = 0; i < 12; i++) {
            if (i < 5) {
                _labels[i] = formatDecimal2ToString(maxData - maxData / 4 * (i));
                _labels[i].draw(gui::Point(0, i * _step), gui::Font::ID::SystemSmaller, td::ColorID::DodgerBlue);
            }
            points[i] = gui::Circle(gui::Point(_x_begin + i * _step, _y_max * (1 - getData[_dataType](_breakdown[i + 1]) / maxData)), _radius);
        }
    }
};

#endif //GRAPH_H
