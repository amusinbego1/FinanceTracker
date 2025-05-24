//
//  Created by Izudin Dzafic on 1 Dec 2022.
//  Copyright © 2022 IDz. All rights reserved.
//
#ifndef LOGINVIEW_H
#define LOGINVIEW_H


#include <gui/View.h>
#include <gui/Label.h>
#include <gui/LineEdit.h>
#include <gui/Button.h>
#include <gui/HorizontalLayout.h>
#include <gui/VerticalLayout.h>
#include <gui/PasswordEdit.h>
#include <gui/Application.h>
#include <repository/UserRepository.h>

class LoginView : public gui::View
{
    void arrangeElements();
    void setStyles();
    void arrangeButtonLayout();
    void arrangeVerticalInputLayout();
    void arrangeMainHorizontalLayout();
    bool handleClickOnSignInButton();
    void showInfoForValidCredentials(const User &loggedInUser);
    void showWarningForInvalidCredentials();
protected:
    gui::Label _lblUsername;
    gui::LineEdit _lnUsername;
    gui::Label _lblPassword;
    gui::Label _lblInvalidUserWarning;
    gui::PasswordEdit _lnPassword;
    gui::Button _btnSignIn;
    gui::Button _btnRegister;
    gui::HorizontalLayout _hLayout;
    gui::HorizontalLayout _buttonHLayout;
    gui::VerticalLayout _vLayout;
public:
    LoginView();

    bool onClick(gui::Button* pBtn) override;


};


#endif //LOGINVIEW_H