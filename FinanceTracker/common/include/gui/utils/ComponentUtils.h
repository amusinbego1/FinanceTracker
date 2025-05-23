//
// Created by Amer on 24. 5. 2025..
//

#ifndef COMPONENTSTYLE_H
#define COMPONENTSTYLE_H

#include <gui/Control.h>

class ComponentUtils{

public:

    static void setDefaultButtonStyle(gui::Control& button){
        button.setSize(gui::Size(75, 40));
        button.setFont(gui::Font::ID::SystemBold);
    }

    static void setLabelWarningStyle(gui::Control& label) {
        label.setTextColor(td::Accent::Critical);
        label.hide(true, true);
    }

    static void openWindow(gui::Window* parentWindow, gui::Window* window) {
        parentWindow->close();
        window->keepOnTopOfParent();
        window->open();
    }

};

#endif //COMPONENTSTYLE_H
