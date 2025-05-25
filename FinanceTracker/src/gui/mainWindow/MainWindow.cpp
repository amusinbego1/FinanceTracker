//
// Created by Amer on 25. 5. 2025..
//

#include "gui/mainWindow/MainWindow.h"
#include "gui/utils/UIElementId.h"
#include <gui/Application.h>

#include <utility>

bool MainWindow::onActionItem(gui::ActionItemDescriptor &aiDesc) {
    const auto &ids = aiDesc.getIDs();

    if (UiElements::checkUiElement(ids, UiElements::LanguageSwitch)) {
        changeLanguage();
    }

    return true;
}

MainWindow::MainWindow(User user)
        : gui::Window(gui::Geometry(300, 100, 1300, 800)),
         _user(user),
         _toolBar(user),
         _mainView(user),
         MultilingualWindow(this){
    setTitle("Finance Tracker");
    setToolBar(_toolBar);
    setCentralView(&_mainView);
}