//
// Created by Amer on 24. 5. 2025..
//

#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <gui/Window.h>
#include "RegisterToolBar.h"
#include "gui/utils/languages/MultilingualWindow.h"
#include "RegisterView.h"

class RegisterWindow : public gui::Window, private MultilingualWindow {
protected:
    RegisterToolBar _toolBar;
    RegisterView _registerView;

    bool onActionItem(gui::ActionItemDescriptor &aiDesc) override ;

public:
    RegisterWindow();

    virtual ~RegisterWindow() = default;
};


#endif //REGISTERWINDOW_H
