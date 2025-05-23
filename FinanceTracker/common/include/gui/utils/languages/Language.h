//
// Created by Amer on 23. 5. 2025..
//

#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <type_traits>
#include <td/String.h>

enum class Language : unsigned char {
    BA,
    EN,
    COUNT  // Helper to know number of languages
};

// Circular ++ operator overload
inline Language& operator++(Language& lang) {
    using IntType = std::underlying_type_t<Language>;
    lang = static_cast<Language>((static_cast<IntType>(lang) + 1) % static_cast<IntType>(Language::COUNT));
    return lang;
}

// Optional: Postfix ++ (returns old value)
inline Language operator++(Language& lang, int) {
    Language old = lang;
    ++lang;
    return old;
}

inline td::String toString(Language lang) {
    switch (lang) {
        case Language::EN: return "EN";
        case Language::BA: return "BA";
        default: return "EN";
    }
}


#endif //LANGUAGES_H
