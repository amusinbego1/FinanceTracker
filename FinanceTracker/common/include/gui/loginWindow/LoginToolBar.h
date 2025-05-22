//
// Created by Amer on 22. 5. 2025..
//

#ifndef LOGINTOOLBAR_H
#define LOGINTOOLBAR_H

#include <gui/ToolBar.h>
#include <gui/Image.h>

class LoginToolBar : public gui::ToolBar
{
protected:

    gui::Image _icon;
public:
    LoginToolBar()
    : gui::ToolBar("loginTB", 1),
    _icon(":languageSwitch")
    {
        addItem(td::String(), &_icon, tr("languageSwitch"), 10, 0, 0, 10);
    }

};

#endif //LOGINTOOLBAR_H
