//
//  Created by Izudin Dzafic on 1 Dec 2022.
//  Copyright © 2022 IDz. All rights reserved.
//
#ifndef LOGINVIEW_H
#define LOGINVIEW_H


#include <gui/View.h>
#include <gui/Label.h>
#include <gui/LineEdit.h>
#include <gui/TextEdit.h>
#include <gui/Button.h>
#include <gui/HorizontalLayout.h>
#include <gui/VerticalLayout.h>
#include <gui/PasswordEdit.h>
#include <gui/Application.h>
#include <repository/UserRepository.h>

class LoginView : public gui::View
{
    void arrangeElements();
protected:
    gui::Label _lblUsername;
    gui::LineEdit _lnUsername;
    gui::Label _lblPassword;
    gui::PasswordEdit _lnPassword;
    gui::Button _btnSignIn;
    gui::Button _btnRegister;
    gui::HorizontalLayout _hLayout;
    gui::HorizontalLayout _buttonHLayout;
    gui::VerticalLayout _vLayout;
public:
    LoginView();


    bool onClick(gui::Button* pBtn) override
    {
        if (pBtn == &_btnSignIn)
        {
            td::Variant username, password;
            _lnUsername.getValue(username);
            _lnPassword.getValue(password);
            UserRepository& userRepo = UserRepository::getInstance();
            std::optional<User> user_optional = userRepo.findUserByUsernameAndPassword(username.strVal(), password.strVal());
            if(user_optional.has_value()) {
                showInfo("Success", "Successfully logged");
                return true;
            }
            showAlert("Fail", "No user with given credentials");
            _btnRegister.hide(false, true);
            _lnUsername.clean();
            _lnPassword.clean();
        }
        return false;
    }


};


#endif //LOGINVIEW_H