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
#include <repository/CategoryRepository.h>
#include "Graph.h"
#include "ExpensePie.h"


class MainView : public gui::View
{
    User _user;
    TransactionService& _transactionService;
    CategoryRepository& _categoryRepository;

    void setStyles();
    void arrangeElements();
    void arrangeOverviewLayout();
    void arrangeGraphLayout();
    void arrangeNewTransactionLayout();
    void arrangeDonutLayout();
    void arrangeInputLayout();
    void arrangeButtonLayout();
    void arrangeExportButtonLayout();
    void arrangeFirstRowLayout();
    void arrangeSecondRowLayout();
    void arrangeThirdRowLayout();
    void arrangeTransactionHistoryLayout();
    void arrangeVerticalCentralLayout();
    void arrangeMainLayout();

    void initComboBoxes();
    void onChangeCategoryComboBox();

    void initTable();
    void reloadTable();

    void changeGraphToBalance();
    void changeGraphToIncome();
    void changeGraphToExpense();
    bool handleCancelButton();
    bool handleSaveButton();
    bool handleDeleteButton();
    bool handleExportButton();

    const char* formatDecimal2ToString(const td::Decimal2& number);
protected:
    //Overview
    gui::Label _lblOverview;
    gui::Button _btnBalance;
    gui::Button _btnIncome;
    gui::Button _btnExpense;

    //Graph
    gui::Label _lblGraph;
    Graph _graph;

    //Input
    gui::Label _lblAddNewTransaction;

    gui::DateEdit _dateEdit;
    gui::ComboBox _cbType;
    gui::ComboBox _cbCategory;
    gui::NumericEdit _neAmount;

    gui::Button _btnCancel;
    gui::Button _btnSave;

    //Donut
    gui::Label _lblExpenseByCategory;
    ExpensePie _pie;

    //Transaction History
    gui::Label _lblTransactionHistory;
    gui::TableEdit _tblTransactionHistory;
    gui::Button _btnExport;
    gui::Button _btnDelete;
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
    gui::HorizontalLayout _hTransactionHistoryLayout;
    gui::VerticalLayout _vExportButtonLayout;



public:
    MainView(User user);

    virtual ~MainView() = default;

    bool onClick(gui::Button* pBtn) override;

    bool onChangedSelection(gui::ComboBox* pCmb);
};

#endif //MAINVIEW_H
