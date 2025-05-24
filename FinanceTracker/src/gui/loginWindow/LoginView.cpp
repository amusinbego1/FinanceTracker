//
// Created by Amer on 23. 5. 2025..
//
#include "gui/loginWindow/LoginView.h"
#include "gui/utils/ComponentStyle.h"

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
    ComponentStyle::setDefaultButtonStyle(_btnSignIn);
    ComponentStyle::setDefaultButtonStyle(_btnRegister);
    ComponentStyle::setLabelWarningStyle(_lblInvalidUserWarning);

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
    _vLayout.append(_buttonHLayout);
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


bool LoginView::hangleClickOnSignInButton() {
    td::Variant username, password;
    _lnUsername.getValue(username);
    _lnPassword.getValue(password);

    UserRepository& userRepo = UserRepository::getInstance();
    std::optional<User> user_optional = userRepo.findUserByUsernameAndPassword(username.strVal(), password.strVal());

    if(user_optional.has_value())
        return showInfoForValidCredentials(user_optional.value());
    else
        return showWarningForInvalidCredentials();
}

bool LoginView::showInfoForValidCredentials(const User &loggedInUser) {
    // TODO: resize this info window
    showInfo(tr("success"), (tr("welcome") + loggedInUser.username).strVal());
    return true;
}

bool LoginView::showWarningForInvalidCredentials() {
    _lblInvalidUserWarning.hide(false, true);
    _lnUsername.clean();
    _lnPassword.clean();
    return false;
}
