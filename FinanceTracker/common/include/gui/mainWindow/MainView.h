//
// Created by Amer on 25. 5. 2025..
//

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <gui/View.h>

class MainView : public gui::View
{
User _user;

public:
    MainView(User user): _user(user){}
};

#endif //MAINVIEW_H
