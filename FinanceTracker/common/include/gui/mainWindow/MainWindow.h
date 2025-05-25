//
// Created by Amer on 19. 5. 2025..
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gui/Window.h>
#include <gui/utils/languages/MultilingualWindow.h>
#include "gui/mainWindow/MainToolBar.h"
#include "gui/mainWindow/MainView.h"
#include "domain/User.h"

class MainWindow : public gui::Window, private MultilingualWindow {

    User _user;
protected:
    MainToolBar _toolBar;
    MainView _mainView;

    bool onActionItem(gui::ActionItemDescriptor &aiDesc) override ;

public:
    MainWindow(User user);

    virtual ~MainWindow() = default;
};




#endif //MAINWINDOW_H
