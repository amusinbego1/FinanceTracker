//
// Created by Amer on 23. 5. 2025..
//

#include "gui/utils/languages/MultilingualWindow.h"

Language MultilingualWindow::_currentLanguage = Language::EN;

bool MultilingualWindow::changeLanguage(){
    // TODO: nagodi da se promijeni jezik
    _instance->getApplication()->setLanguage(toString(++_currentLanguage));
    _instance->showInfo(gui::tr("success"), gui::tr("languageSwitched"));
    return true;
}