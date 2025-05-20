//
// Created by Amer on 19. 5. 2025..
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gui/Window.h>

class MainWindow : public gui::Window
{
public:
    MainWindow()
    : gui::Window(gui::Geometry(50, 50, 1200, 480))
    {
        setTitle("First App");
        //        composeContent();
    }

    ~MainWindow()
    {
    }
};




#endif //MAINWINDOW_H
