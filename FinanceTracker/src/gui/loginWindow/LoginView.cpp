//
// Created by Amer on 23. 5. 2025..
//
#include "gui/loginWindow/LoginView.h"

#include <gui/mainWindow/MainWindow.h>
#include <gui/registerWindow/RegisterWindow.h>

#include "gui/utils/ComponentUtils.h"

LoginView::LoginView()
    : _lblUsername(tr("username"))
    , _lblPassword(tr("password"))
    , _lblInvalidUserWarning(tr("invalidUserWarning"))
    , _btnSignIn(tr("signIn"))
    , _btnRegister(tr("register"))
    , _hLayout(3)
    , _buttonHLayout(2)
    , _vLayout(10)
{
   arrangeElements();
}

void LoginView::setStyles() {
    ComponentUtils::setDefaultButtonStyle(_btnSignIn);
    ComponentUtils::setDefaultButtonStyle(_btnRegister);
    ComponentUtils::setLabelWarningStyle(_lblInvalidUserWarning);

}

void LoginView::arrangeButtonLayout() {
    _buttonHLayout.append(_btnRegister);
    _buttonHLayout.append(_btnSignIn);
}

void LoginView::arrangeVerticalInputLayout() {
    _vLayout.appendSpacer(4);

    _vLayout.append(_lblUsername, td::HAlignment::Left);
    _vLayout.append(_lnUsername);

    _vLayout.appendSpacer(1);

    _vLayout.append(_lblPassword, td::HAlignment::Left);
    _vLayout.append(_lnPassword);

    _vLayout.appendSpacer(1);
    _vLayout.append(_lblInvalidUserWarning, td::HAlignment::Center);
    _vLayout.appendSpacer(1);

    _vLayout.appendLayout(_buttonHLayout);

    _vLayout.appendSpacer(4);
}

void LoginView::arrangeMainHorizontalLayout() {
    _hLayout.appendSpacer();
    _hLayout.append(_vLayout);
    _hLayout.appendSpacer();
    setLayout(&_hLayout);
}

void LoginView::arrangeElements() {
    setStyles();
    arrangeButtonLayout();
    arrangeVerticalInputLayout();
    arrangeMainHorizontalLayout();
}


bool LoginView::handleClickOnSignInButton() {
    td::Variant username, password;
    _lnUsername.getValue(username);
    _lnPassword.getValue(password);

    UserRepository& userRepo = UserRepository::getInstance();
    std::optional<User> user_optional = userRepo.findUserByUsernameAndPassword(username.strVal(), password.strVal());

    if(user_optional.has_value()) {
        ComponentUtils::openWindow(getParentWindow(), new MainWindow(user_optional.value()));
        return true;
    }
    showWarningForInvalidCredentials();
    return false;
}

void LoginView::showInfoForValidCredentials(const User &loggedInUser) {
    // TODO: resize this info window
    showInfo(tr("success"), (tr("welcomeBack") + loggedInUser.username).strVal());
}

void LoginView::showWarningForInvalidCredentials() {
    _lblInvalidUserWarning.hide(false, true);
    _lnUsername.clean();
    _lnPassword.clean();
}

bool LoginView::onClick(gui::Button *pBtn)
{
    if (pBtn == &_btnSignIn)
        return handleClickOnSignInButton();
    else if (pBtn == &_btnRegister) {
        ComponentUtils::openWindow(getParentWindow(), new RegisterWindow());
        return true;
    }
    return false;
}

