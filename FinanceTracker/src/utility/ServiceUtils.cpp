//
// Created by Amer on 17. 5. 2025..
//

#include "utility/ServiceUtils.h"

td::UINT4 ServiceUtils::getDaysInMonth(td::UINT4 year, td::UINT4 month){
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 1 and 12.");
    }

    // Handle February separately
    if (month == 2) {
        // Leap year if divisible by 4 AND (not divisible by 100 OR divisible by 400)
        bool isLeap = (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
        return isLeap ? 29 : 28;
    }

    // April, June, September, November have 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    // All others have 31 days
    return 31;
}