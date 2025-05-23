//
// Created by Amer on 22. 5. 2025..
//

#ifndef LOGINTOOLBAR_H
#define LOGINTOOLBAR_H

#include <gui/ToolBar.h>
#include "gui/utils/languages/MultilingualToolBar.h"

class LoginToolBar : public gui::ToolBar, private MultilingualToolBar {
public:
    LoginToolBar()
        : gui::ToolBar("loginTB", 1),
          MultilingualToolBar(this, &gui::ToolBar::addItem) {
    }
};

#endif //LOGINTOOLBAR_H
