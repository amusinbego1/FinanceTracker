//
// Created by Amer on 24. 5. 2025..
//

#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

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

class RegisterView : public gui::View
{
    void arrangeElements();
    void setStyles();
    void arrangeButtonLayout();
    void arrangeVerticalInputLayout();
    void arrangeMainHorizontalLayout();
    bool handleClickOnRegisterButton();
    bool isValidRegisterInput(const td::String& username, const td::String& password, const td::String& confirmPassword);
    void showWarningForInvalidUsername();
    void hideWarningForInvalidUsername();
    void showWarningForInvalidPassword();
    void hideWarningForInvalidPassword();
    void registerNewUser(const td::String& username, const td::String& password);
    void showInfoForValidCredentials(const td::String& username);
    void cleanInputs();
protected:
    gui::Label _lblUsername;
    gui::Label _lblTooShortUsername;
    gui::LineEdit _lnUsername;

    gui::Label _lblPassword;
    gui::Label _lblConfirmPassword;
    gui::Label _lblInvalidPassword;
    gui::PasswordEdit _lnPassword;
    gui::PasswordEdit _lnConfirmPassword;

    gui::Button _btnCancel;
    gui::Button _btnRegister;

    gui::HorizontalLayout _hLayout;
    gui::HorizontalLayout _buttonHLayout;
    gui::VerticalLayout _vLayout;
public:
    RegisterView();


    bool onClick(gui::Button* pBtn) override;


};

#endif //REGISTERVIEW_H
