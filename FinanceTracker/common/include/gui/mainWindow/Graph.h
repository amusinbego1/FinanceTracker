//
// Created by Amer on 28. 5. 2025..
//

#ifndef GRAPH_H
#define GRAPH_H

#include <gui/Canvas.h>
#include <gui/Shape.h>
#include <gui/DrawableString.h>

class Graph : public gui::Canvas{
    const int _y_max = 160, _x_max = 480 + 60, _step = 40, _radius = 4, _x_begin = 60;
    gui::Shape _xAxis;
    gui::Shape _yAxis;
    gui::Shape _circles;
    gui::Shape _dashes[5];
    TransactionService& _transactionService;
    std::map<int, ServiceUtils::Summary> _breakdown;
    gui::Circle points[12];
    gui::DrawableString _months[12]{"Jan", "Feb" , "Mar" , "Apr", "May", "Jun", "Jul", "Aug", "Sep" ,"Oct", "Nov", "Dec"};
    gui::DrawableString _labels[5];


    double maxBalance() {
        td::Decimal2 max = _breakdown[1].getBalance();
        for(int i=2; i<=12; i++)
            if (_breakdown[i].getBalance() > max)
                max = _breakdown[i].getBalance();
        return max.getAsFloat() + _radius;
    }

    const char* formatDecimal2ToString(const td::Decimal2& number) {
        double value = number.getAsFloat();
        char buffer[32];
        sprintf_s(buffer, sizeof(buffer), "%.2f", value);
        const char* cstr = buffer;
        return cstr;
    }


 public:
     Graph(User user): _transactionService(TransactionService::getInstance(user)){
        _breakdown = _transactionService.getMonthlyBreakdown(2025);
         double max_balance = maxBalance();
        _xAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, 0), gui::Point(_x_begin, _y_max)}, 2);
        _yAxis.createLines(new gui::Point[2]{gui::Point(_x_begin, _y_max), gui::Point(_x_max, _y_max)}, 2);
         for(int i = 0; i<5; i++) {
             _dashes[i].createLines(new gui::Point[2]{gui::Point(_x_begin - _radius, i*_step), gui::Point(_x_begin +_radius, i*_step)}, 2);
             _labels[i] = formatDecimal2ToString(max_balance - max_balance/4 * (i));

         }
         for(int i=0; i<12; i++) {
            points[i] = gui::Circle(gui::Point(_x_begin + i*_step, _y_max*(1 - _breakdown[i+1].getBalance()/max_balance)), _radius);
         }
         _circles.createCircles(points, 12);
      }


    void onDraw(const gui::Rect &rect) override {
         _xAxis.drawWire(td::ColorID::Black, 2.5);
         _yAxis.drawWire(td::ColorID::Black, 2.5);
         _circles.drawFill(td::ColorID::DodgerBlue);
         for(int i=0; i<5; i++) {
             _dashes[i].drawWire(td::ColorID::Black, 4);
             _labels[i].draw(gui::Point(0, i*_step), gui::Font::ID::SystemSmaller, td::ColorID::DodgerBlue);
         }
         for(int i=0; i<12; i++)
             _months[i].draw(gui::Point(_x_begin + i*_step - 5, _y_max + 5), gui::Font::ID::SystemSmaller, td::ColorID::DodgerBlue);

     }
};

#endif //GRAPH_H
