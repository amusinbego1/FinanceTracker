//
// Created by Amer on 23. 5. 2025..
//

#ifndef UIELEMENTID_H
#define UIELEMENTID_H

#include <td/String.h>

struct UiElementId {
    td::BYTE menuID;
    td::BYTE firstSubMenuID;
    td::BYTE lastSubMenuID;
    td::BYTE actionID;

    constexpr UiElementId(td::BYTE m, td::BYTE f, td::BYTE l, td::BYTE a)
        : menuID(m), firstSubMenuID(f), lastSubMenuID(l), actionID(a) {
    }

    [[nodiscard]] constexpr auto asTuple() const {
        return std::make_tuple(menuID, firstSubMenuID, lastSubMenuID, actionID);
    }
};

// Named constants (like enum entries)
namespace UiElements {
    constexpr UiElementId LanguageSwitch{10, 0, 0, 10};
    constexpr UiElementId LoginButton{11, 0, 0, 20};
    constexpr UiElementId LogoutButton{11, 0, 0, 21};

    inline bool checkUiElement(const std::tuple<td::BYTE, td::BYTE, td::BYTE, td::BYTE>& ids, const UiElementId& element_id) {
        return ids == element_id.asTuple();
    }


}


#endif //UIELEMENTID_H
