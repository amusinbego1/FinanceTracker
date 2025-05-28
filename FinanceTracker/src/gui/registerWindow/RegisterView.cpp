//
// Created by Amer on 23. 5. 2025..
//
#include "gui/registerWindow/RegisterView.h"

#include <gui/loginWindow/LoginWindow.h>
#include <gui/mainWindow/MainWindow.h>

#include "gui/utils/ComponentUtils.h"

RegisterView::RegisterView()
    : _lblUsername(tr("username"))
    , _lblTooShortUsername(tr("tooShortUsername"))

    , _lblPassword(tr("password"))
    , _lblConfirmPassword(tr("confirmPassword"))
    , _lblInvalidPassword(tr("invalidPassword"))

    , _btnCancel(tr("cancel"))
    , _btnRegister(tr("register"))

    , _hLayout(3)
    , _buttonHLayout(2)
    , _vLayout(10)
{
   arrangeElements();
}

void RegisterView::arrangeElements() {
    setStyles();
    arrangeButtonLayout();
    arrangeVerticalInputLayout();
    arrangeMainHorizontalLayout();
}

void RegisterView::setStyles() {
    ComponentUtils::setDefaultButtonStyle(_btnCancel);
    ComponentUtils::setDefaultButtonStyle(_btnRegister);
    _btnRegister.setAsDefault();
    ComponentUtils::setLabelWarningStyle(_lblInvalidPassword);
    ComponentUtils::setLabelWarningStyle(_lblTooShortUsername);
}

void RegisterView::arrangeButtonLayout() {
    _buttonHLayout.append(_btnCancel);
    _buttonHLayout.append(_btnRegister);
}

void RegisterView::arrangeVerticalInputLayout() {
    _vLayout.appendSpacer(4);

    _vLayout.append(_lblUsername, td::HAlignment::Left);
    _vLayout.append(_lnUsername);
    _vLayout.append(_lblTooShortUsername, td::HAlignment::Left);

    _vLayout.appendSpacer(1);

    _vLayout.append(_lblPassword, td::HAlignment::Left);
    _vLayout.append(_lnPassword);

    _vLayout.appendSpacer(1);

    _vLayout.append(_lblConfirmPassword, td::HAlignment::Left);
    _vLayout.append(_lnConfirmPassword);

    _vLayout.appendSpacer(1);
    _vLayout.append(_lblInvalidPassword, td::HAlignment::Center);
    _vLayout.appendSpacer(1);

    _vLayout.append(_buttonHLayout);

    _vLayout.appendSpacer(4);
}

void RegisterView::arrangeMainHorizontalLayout() {
    _hLayout.appendSpacer();
    _hLayout.append(_vLayout);
    _hLayout.appendSpacer();
    setLayout(&_hLayout);
}


bool RegisterView::onClick(gui::Button* pBtn)
{
    if (pBtn == &_btnCancel) {
        ComponentUtils::openWindow(getContainingWindow(), new LoginWindow());
        return true;
    } else if (pBtn== &_btnRegister) {
        return handleClickOnRegisterButton();
    }
    return false;
}


bool RegisterView::handleClickOnRegisterButton() {
    td::Variant username, password, confirmPassword;
    _lnUsername.getValue(username);
    _lnPassword.getValue(password);
    _lnConfirmPassword.getValue(confirmPassword);

    if (isValidRegisterInput(username.strVal(), password.strVal(), confirmPassword.strVal())) {
        registerNewUser(username.strVal(), password.strVal());
        User user = UserRepository::getInstance().findUserByUsernameAndPassword(username.strVal(), password.strVal()).value();
        ComponentUtils::openWindow(getContainingWindow(), new MainWindow(user));
        return true;
    }
    return false;
}

void RegisterView::showInfoForValidCredentials(const td::String& username) {
    // TODO: resize this info window
    showInfo(tr("success"), (tr("welcome") + username).strVal());
}

bool RegisterView::isValidRegisterInput(const td::String& username, const td::String& password, const td::String& confirmPassword) {
    if (username.length() <= 4) {
        showWarningForInvalidUsername();
        return false;
    }

    hideWarningForInvalidUsername();

    if (password != confirmPassword) {
        showWarningForInvalidPassword();
        return false;
    }

    hideWarningForInvalidPassword();

    return true;
}

void RegisterView::registerNewUser(const td::String& username, const td::String& password) {
    auto& userRepo = UserRepository::getInstance();
    userRepo.saveUser(User{0, username, password});
}

void RegisterView::showWarningForInvalidUsername() {
    _lblTooShortUsername.hide(false, true);
    cleanInputs();
}

void RegisterView::hideWarningForInvalidUsername() {
    _lblTooShortUsername.hide(true, true);
}


void RegisterView::showWarningForInvalidPassword() {
    _lblInvalidPassword.hide(false, true);
    cleanInputs();
}

void RegisterView::hideWarningForInvalidPassword() {
    _lblInvalidPassword.hide(true, true);
}

void RegisterView::cleanInputs() {
    _lnUsername.clean();
    _lnPassword.clean();
    _lnConfirmPassword.clean();
}

