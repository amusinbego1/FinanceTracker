//
// Created by Amer on 28. 5. 2025..
//

#ifndef GRAPH_H
#define GRAPH_H

#include <gui/Canvas.h>
#include <gui/Shape.h>
#include <gui/DrawableString.h>
#include <service/TransactionService.h>
#include <utility/ServiceUtils.h>

class Graph : public gui::Canvas {
    const int _y_max = 160, _x_max = 480 + 60, _step = 40, _radius = 4, _x_begin = 60;
    gui::Shape _xAxis;
    gui::Shape _yAxis;
    gui::Shape _circles;
    gui::Shape _dashes[5];
    TransactionService &_transactionService;
    std::map<int, ServiceUtils::Summary> _breakdown;
    gui::Circle points[12];
    const gui::DrawableString _months[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    gui::DrawableString _labels[5];

    td::String _dataType;
    using SummaryFunction = double(*)(const ServiceUtils::Summary &);
    std::map<td::String, SummaryFunction> getData = {
        {"Balance", &ServiceUtils::getBalanceWrapper},
        {"Income", &ServiceUtils::getIncomeWrapper},
        {"Expense", &ServiceUtils::getExpenseWrapper}
    };


    double getMaxOfData();
    void drawGraphData();

public:
    explicit Graph(const User& user);
    void onDraw(const gui::Rect &rect) override;
    void changeDataType(const td::String& dataType);
    void updateData();
};

#endif //GRAPH_H
