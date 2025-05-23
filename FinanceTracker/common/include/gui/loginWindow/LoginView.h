//
//  Created by Izudin Dzafic on 1 Dec 2022.
//  Copyright © 2022 IDz. All rights reserved.
//
#pragma once
#include <gui/View.h>
#include <gui/Label.h>
#include <gui/LineEdit.h>
#include <gui/NumericEdit.h>
#include <gui/TextEdit.h>
#include <gui/Button.h>
#include <gui/HorizontalLayout.h>
#include <gui/VerticalLayout.h>
#include <gui/PasswordEdit.h>
#include <td/Color.h>
#include <cnt/StringBuilder.h>

class LoginView : public gui::View
{
    void arrangeElements();
protected:
    gui::Label _lblUsername;
    gui::LineEdit _lnUsername;
    gui::Label _lblPassword;
    gui::PasswordEdit _lnPassword;
    gui::Button _btnSignIn;
    gui::HorizontalLayout _hLayout;
    gui::VerticalLayout _vLayout;
public:
    LoginView();

    bool onFinishEdit(gui::LineEdit* pCtrl) override
    {
        // if ( (pCtrl == &_neQuantity) || (pCtrl == &_nePrice) )
        // {
        //     td::Variant quant = _neQuantity.getValue();
        //     td::Variant price = _nePrice.getValue();
        //     auto value = quant * price;
        //     td::Decimal2 decVal(value.r8Val());
        //     _neValue.setValue(decVal);
        //     return true;
        // }
        return false;
    }


    bool onClick(gui::Button* pBtn) override
    {
        // if (pBtn == &_btnSignIn)
        // {
        //     cnt::StringBuilderSmall sb;
        //     sb.appendString(_lnUsername.getText());
        //     sb.appendCString(", Quantity=");
        //     sb.appendString(_neQuantity.getText());
        //     sb.appendCString(", Value=");
        //     sb.appendString(_neValue.getText());
        //     sb.appendCString(" ");
        //     td::String str = sb.toString();
        //     _textEdit.appendString(str);
        //     return true;
        // }
        // else if (pBtn == &_btnDelete)
        // {
        //     _textEdit.clean();
        //     return true;
        // }
        return false;
    }


};
