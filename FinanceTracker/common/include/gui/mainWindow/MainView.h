//
// Created by Amer on 25. 5. 2025..
//

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <gui/Button.h>

#include <service/TransactionService.h>

#include "domain/User.h"
#include <gui/VerticalLayout.h>
#include <gui/HorizontalLayout.h>
#include <gui/Label.h>
#include <gui/View.h>

class MainView : public gui::View
{
User _user;
TransactionService& _transactionService;;

    void setStyles();
    void arrangeElements();
    void arrangeOverviewLayout();
    void arrangeGraphLayout();
    void arrangeFirstRowLayout();
    void arrangeVerticalCentralLayout();
    void arrangeMainLayout();

    void changeGraphToBalance();
    void changeGraphToIncome();
    void changeGraphToExpense();
    const char* formatDecimal2ToString(const td::Decimal2& number);
protected:
    //Overview
    gui::Label _lblOverview;
    gui::Button _btnBalance;
    gui::Button _btnIncome;
    gui::Button _btnExpense;

    //Graph
    gui::Label _lblGraph;
    gui::Label _graphReplacement;

    //LAYOUTS
    gui::HorizontalLayout _hMainLayout;
    gui::VerticalLayout _vCentralMainLayout;

    gui::HorizontalLayout _hFirstRowLayout;
    gui::VerticalLayout _vOverviewLayout;
    gui::VerticalLayout _vGraphLayout;

    gui::HorizontalLayout _hSecondRowLayout;
    gui::VerticalLayout _vNewTransactionLayout;
    gui::VerticalLayout _vNewDonutLayout;
    gui::HorizontalLayout _hInputLayout;
    gui::HorizontalLayout _hButtonLayout;

    gui::VerticalLayout _vTransactionHistoryLayout;



public:
    MainView(User user);

    virtual ~MainView() = default;

    bool onClick(gui::Button* pBtn) override;
};

#endif //MAINVIEW_H
