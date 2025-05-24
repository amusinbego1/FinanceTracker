//
// Created by Amer on 22. 5. 2025..
//

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <gui/Window.h>
#include "LoginToolBar.h"
#include "gui/utils/languages/MultilingualWindow.h"
#include "LoginView.h"

class LoginWindow : public gui::Window, private MultilingualWindow {
protected:
    LoginToolBar _toolBar;
    LoginView _loginView;

    bool onActionItem(gui::ActionItemDescriptor &aiDesc) override ;

public:
    LoginWindow();

    virtual ~LoginWindow() = default;
};


#endif //LOGINWINDOW_H
