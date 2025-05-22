//
// Created by Amer on 22. 5. 2025..
//

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <gui/Window.h>
#include "LoginToolBar.h"

class LoginWindow : public gui::Window
{
protected:
    LoginToolBar _toolBar;
    std::vector<td::String> supportedLanguages;
    int currentLanguagePos = 0;

    bool onActionItem(gui::ActionItemDescriptor& aiDesc) override
    {
        auto [menuID, firstSubMenuID, lastSubMenuID, actionID] = aiDesc.getIDs();
        auto pAI = aiDesc.getActionItem();

        if (menuID == 10 && firstSubMenuID== 0 && lastSubMenuID == 0)
        {
            switch (actionID)
            {
                case 10: {
                    // TODO: nagodi da se promijeni jezik
                    this->getApplication()->setLanguage("EN");
                    this->getToolBar()->show(true);
                    this->showInfo(tr("success"), tr("languageSwitched"));
                    return true;
                }
                default:
                    return false;
            }
        }
        return true;
    }


public:
    LoginWindow()
    : gui::Window(gui::Geometry(650, 400, 600, 300)),
    supportedLanguages({"BA", "EN"})
    {
        td::String login = "Finance Tracker - ";
        login.append(tr("login"));
        setTitle(login);

        setToolBar(_toolBar);
        //        composeContent();
    }

    ~LoginWindow()
    {
    }
};


#endif //LOGINWINDOW_H
