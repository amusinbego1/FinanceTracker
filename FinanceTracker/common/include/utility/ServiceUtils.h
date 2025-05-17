//
// Created by Amer on 17. 5. 2025..
//

#ifndef SERVICEUTILS_H
#define SERVICEUTILS_H
#include <td/Decimal.h>

class ServiceUtils{
public:
    class Summary{
        td::Decimal2 income_, expense_;

    public:
        Summary(): income_(0.0), expense_(0.0){}

        Summary& addIncome(td::Decimal2 income){
            income_ += income;
            return *this;
        }
        Summary& addExpense(td::Decimal2 expense){
            expense_ += expense;
            return *this;
        }

        td::Decimal2 getIncome() const {return income_;}
        td::Decimal2 getExpense() const {return expense_;}
        td::Decimal2 getBalance() const {return income_ - expense_;}

    };

    static td::UINT4 getDaysInMonth(td::UINT4 year, td::UINT4 month);
};



#endif //SERVICEUTILS_H
