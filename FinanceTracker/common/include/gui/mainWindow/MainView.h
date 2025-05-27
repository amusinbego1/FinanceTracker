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
#include <gui/NumericEdit.h>
#include <gui/ComboBox.h>
#include <gui/DateEdit.h>
#include <gui/TableEdit.h>
#include <gui/View.h>

class MainView : public gui::View
{
User _user;
TransactionService& _transactionService;;

    void setStyles();
    void arrangeElements();
    void arrangeOverviewLayout();
    void arrangeGraphLayout();
    void arrangeNewTransactionLayout();
    void arrangeDonutLayout();
    void arrangeInputLayout();
    void arrangeButtonLayout();
    void arrangeFirstRowLayout();
    void arrangeSecondRowLayout();
    void arrangeThirdRowLayout();
    void arrangeTransactionHistoryLayout();
    void arrangeVerticalCentralLayout();
    void arrangeMainLayout();

    void initComboBoxes();
    void onChangeCategoryComboBox();

    void initTable();

    void changeGraphToBalance();
    void changeGraphToIncome();
    void changeGraphToExpense();
    void handleCancelButton();
    void handleSaveButton();

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

    //Input
    gui::Label _lblAddNewTransaction;

    gui::DateEdit _dateEdit;
    gui::ComboBox _cbCategory;
    gui::ComboBox _cbType;
    gui::NumericEdit _neAmount;

    gui::Button _btnCancel;
    gui::Button _btnSave;

    //Donut
    gui::Label _lblExpenseByCategory;
    gui::Label _donutReplacement;

    //Transaction History
    gui::Label _lblTransactionHistory;
    gui::TableEdit _tblTransactionHistory;
    dp::IDataSetPtr _dataSetPtr;

    //LAYOUTS
    gui::HorizontalLayout _hMainLayout;
    gui::VerticalLayout _vCentralMainLayout;

    gui::HorizontalLayout _hFirstRowLayout;
    gui::VerticalLayout _vOverviewLayout;
    gui::VerticalLayout _vGraphLayout;

    gui::HorizontalLayout _hSecondRowLayout;
    gui::VerticalLayout _vNewTransactionLayout;
    gui::VerticalLayout _vDonutLayout;
    gui::HorizontalLayout _hInputLayout;
    gui::HorizontalLayout _hButtonLayout;


    gui::HorizontalLayout _hThirdRowLayout;
    gui::VerticalLayout _vTransactionHistoryLayout;



public:
    MainView(User user);

    virtual ~MainView() = default;

    bool onClick(gui::Button* pBtn) override;

    bool onChangedSelection(gui::ComboBox* pCmb);
};

#endif //MAINVIEW_H
