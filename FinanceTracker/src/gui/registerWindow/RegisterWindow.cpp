//
// Created by Amer on 24. 5. 2025..
//

#include "gui/registerWindow/RegisterWindow.h"
#include "gui/utils/UIElementId.h"
#include <gui/Application.h>

bool RegisterWindow::onActionItem(gui::ActionItemDescriptor &aiDesc) {
    const auto &ids = aiDesc.getIDs();

    if (UiElements::checkUiElement(ids, UiElements::LanguageSwitch)) {
        changeLanguage();
    }

    return true;
}

RegisterWindow::RegisterWindow()
        : gui::Window(gui::Geometry(650, 300, 500, 600)),
        MultilingualWindow(this){
    td::String registerStr = "Finance Tracker - ";
    registerStr.append(tr("register"));
    setTitle(registerStr);
    setToolBar(_toolBar);
    setCentralView(&_registerView);
}