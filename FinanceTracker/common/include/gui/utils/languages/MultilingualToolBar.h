//
// Created by Amer on 23. 5. 2025..
//

#ifndef MULTILINGUALTOOLBAR_H
#define MULTILINGUALTOOLBAR_H

#include <gui/Image.h>
#include "gui/utils/UIElementId.h"

class MultilingualToolBar {
    gui::Image _icon;

protected:
    template<typename T>
    explicit MultilingualToolBar(
        T *instance,
        td::WORD (gui::ToolBar::*method)(const td::String &, gui::Image *, const td::String &, td::BYTE, td::BYTE, td::BYTE, td::BYTE)
    ) : _icon(":languageSwitch") {
        auto [m, f, l, a] = UiElements::LanguageSwitch.asTuple(); // Unpack 4 bytes
        (instance->*method)(td::String(), &_icon, gui::tr("languageSwitch"), m, f, l, a);
    }
};

#endif //MULTILINGUALTOOLBAR_H
