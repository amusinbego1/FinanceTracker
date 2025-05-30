//
// Created by Amer on 17. 5. 2025..
//

#ifndef SERVICEUTILS_H
#define SERVICEUTILS_H
#include <td/ColorID.h>
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

        [[nodiscard]] td::Decimal2 getIncome() const {return income_;}
        [[nodiscard]] td::Decimal2 getExpense() const {return expense_;}
        [[nodiscard]] td::Decimal2 getBalance() const {return income_ - expense_;}

    };

    static double getBalanceWrapper(const ServiceUtils::Summary& s) {
        return s.getBalance().getAsFloat();
    }

    static double getIncomeWrapper(const ServiceUtils::Summary& s) {
        return s.getIncome().getAsFloat();
    }

    static double getExpenseWrapper(const ServiceUtils::Summary& s) {
        return s.getExpense().getAsFloat();
    }

    static td::INT4 getDaysInMonth(td::INT4 year, td::INT4 month);
};

inline const char* formatDecimal2ToString(const td::Decimal2& number) {
    double value = number.getAsFloat();
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", value);
    const char* cstr = buffer;
    return cstr;
}

inline const char* to_string(td::ColorID color_id) {
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




#endif //SERVICEUTILS_H
