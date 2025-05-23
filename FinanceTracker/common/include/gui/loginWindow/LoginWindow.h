//
// Created by Amer on 22. 5. 2025..
//

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <gui/Window.h>
#include "LoginToolBar.h"
#include "gui/utils/UIElementId.h"
#include "gui/utils/languages/MultilingualWindow.h"

class LoginWindow : public gui::Window, private MultilingualWindow {
protected:
    LoginToolBar _toolBar;

    bool onActionItem(gui::ActionItemDescriptor &aiDesc) override ;

public:
    LoginWindow();

    ~LoginWindow() {
    }
};


#endif //LOGINWINDOW_H
