//
// Created by Amer on 30. 5. 2025..
//


#include "gui/mainWindow/Graph.h"
#include "service/TransactionService.h"
#include "domain/User.h"

double Graph::getMaxOfData() {
    double max = getData[_dataType](_breakdown[1]);
    for (int i = 2; i <= 12; i++)
        if (getData[_dataType](_breakdown[i]) > max)
            max = getData[_dataType](_breakdown[i]);
    return max + _radius;
}

void Graph::drawGraphData() {
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


Graph::Graph(const User& user): _transactionService(TransactionService::getInstance(user)), _dataType("Balance") {
    _xAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, 0), gui::Point(_x_begin, _y_max)}, 2);
    _yAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, _y_max), gui::Point(_x_max, _y_max)}, 2);
    for (int i = 0; i < 5; i++) {
        _dashes[i].createLines(new gui::Point[2]{gui::Point(_x_begin - _radius, i * _step), gui::Point(_x_begin + _radius, i * _step)}, 2);
    }

}

void Graph::onDraw(const gui::Rect &rect)  {
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


void Graph::changeDataType(const td::String& dataType) {
    _dataType = dataType;
    reDraw();
}

void Graph::updateData() {
    reDraw();
}