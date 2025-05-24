//
// Created by Amer on 23. 5. 2025..
//
#include "gui/loginWindow/LoginView.h"

LoginView::LoginView()
    : _lblUsername(tr("username"))
    , _lblPassword(tr("password"))
    , _btnSignIn(tr("signIn"))
    , _btnRegister(tr("register"))
    , _hLayout(3)
    , _buttonHLayout(2)
    , _vLayout(9)
{
   arrangeElements();
}

void LoginView::arrangeElements() {
    _btnSignIn.setSize(gui::Size(75, 40));
    _btnRegister.setSize(gui::Size(75, 40));
    _btnSignIn.setFont(gui::Font::ID::SystemBold);
    _btnRegister.setFont(gui::Font::ID::SystemBold);

    _buttonHLayout.append(_btnRegister);
    _btnRegister.hide(true, true);
    _buttonHLayout.append(_btnSignIn);

    _vLayout.appendSpacer(4);
    _vLayout.append(_lblUsername, td::HAlignment::Left);
    _vLayout.append(_lnUsername);
    _vLayout.appendSpacer(1);
    _vLayout.append(_lblPassword, td::HAlignment::Left);
    _vLayout.append(_lnPassword);
    _vLayout.appendSpacer(2);
    _vLayout.append(_buttonHLayout);
    _vLayout.appendSpacer(4);

    _hLayout.appendSpacer();
    _hLayout.append(_vLayout);
    _hLayout.appendSpacer();

    setLayout(&_hLayout);
}
