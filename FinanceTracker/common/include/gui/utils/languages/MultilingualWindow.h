//
// Created by Amer on 23. 5. 2025..
//

#ifndef MULTILINGUALWINDOW_H
#define MULTILINGUALWINDOW_H

#include <gui/Window.h>
#include <gui/Application.h>
#include <gui/ToolBar.h>
#include "gui/utils/languages/Language.h"

class MultilingualWindow{
    gui::Window* _instance;

protected:

    explicit MultilingualWindow(gui::Window *instance)
        : _instance(instance){}

    bool changeLanguage();

public:
    static Language _currentLanguage;
};

#endif //MULTILINGUALWINDOW_H
