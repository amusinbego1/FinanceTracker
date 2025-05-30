//
// Created by Amer on 23. 5. 2025..
//

#include "gui/loginWindow/LoginWindow.h"
#include "gui/utils/UIElementId.h"
#include <gui/Application.h>

bool LoginWindow::onActionItem(gui::ActionItemDescriptor &aiDesc) {
    const auto &ids = aiDesc.getIDs();

    if (UiElements::checkUiElement(ids, UiElements::LanguageSwitch)) {
        changeLanguage();
    }

    return true;
}

LoginWindow::LoginWindow()
        : gui::Window(gui::Geometry(650, 400, 500, 400)),
        MultilingualWindow(this){
    td::String login = "Finance Tracker - ";
    login.append(tr("signIn"));
    setTitle(login);
    setToolBar(_toolBar);
    setCentralView(&_loginView);
}