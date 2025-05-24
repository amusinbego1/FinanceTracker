//
// Created by Amer on 24. 5. 2025..
//

#ifndef REGISTERTOOLBAR_H
#define REGISTERTOOLBAR_H

#include <gui/ToolBar.h>
#include "gui/utils/languages/MultilingualToolBar.h"

class RegisterToolBar : public gui::ToolBar, private MultilingualToolBar {
public:
    RegisterToolBar()
        : gui::ToolBar("loginTB", 1),
          MultilingualToolBar(this, &gui::ToolBar::addItem) {
    }
};

#endif //REGISTERTOOLBAR_H
