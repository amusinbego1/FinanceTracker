//
// Created by Amer on 19. 5. 2025..
//

#ifndef FTAPPLICATION_H
#define FTAPPLICATION_H

#include <gui/Application.h>
#include "gui/mainWindow/MainWindow.h"
#include "gui/loginWindow/LoginWindow.h"

class FTApplication: public gui::Application {
protected:

    gui::Window* createInitialWindow() override
    {
        return new LoginWindow();
    }

public:
    FTApplication(int argc, const char** argv)
    : gui::Application(argc, argv)
    {
    }

};

#endif //FTAPPLICATION_H
