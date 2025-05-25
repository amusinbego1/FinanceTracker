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
    gui::Image _iconSignout;
public:
    MainToolBar(User user)
        : gui::ToolBar("mainTB", 7),
          _iconUsername(":username"),
          _iconSignout(":logout"),
          _user(user),
          MultilingualToolBar(this, &gui::ToolBar::addItem) {
        auto [m_u, f_u, l_u, a_u] = UiElements::Username.asTuple();
        auto [m_l, f_l, l_l, a_l] = UiElements::SignoutButton.asTuple();

        addSpaceItem();
        addSpaceItem();
        addItem(_user.username, &_iconUsername, _user.username, m_u, f_u, l_u, a_u);

        addSpaceItem();
        addSpaceItem();
        addItem("", &_iconSignout, tr("signOut"),m_l, f_l, l_l, a_l );
    }
};


#endif //MAINTOOLBAR_H
