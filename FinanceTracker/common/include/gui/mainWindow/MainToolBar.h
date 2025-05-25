//
// Created by Amer on 25. 5. 2025..
//

#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include <domain/User.h>
#include <gui/ToolBar.h>
#include "gui/utils/languages/MultilingualToolBar.h"

class MainToolBar : public gui::ToolBar, private MultilingualToolBar {

    User _user;
protected:
    gui::Image _iconUsername;
public:
    MainToolBar(User user)
        : gui::ToolBar("mainTB", 4),
          _iconUsername(":username"),
          _user(user),
          MultilingualToolBar(this, &gui::ToolBar::addItem) {
        auto [m, f, l, a] = UiElements::Username.asTuple();
        addSpaceItem();
        addSpaceItem();
        addItem(_user.username, &_iconUsername, _user.username, m, f, l ,a);
    }
};


#endif //MAINTOOLBAR_H
