//
// Created by Amer on 25. 5. 2025..
//

#include "gui/mainWindow/MainView.h"

#include <gui/utils/ComponentUtils.h>
#include "service/TransactionService.h"
#include <td/Decimal.h>

#include "domain/User.h"

MainView::MainView(User user):
    _user(user),
    _transactionService(TransactionService::getInstance(user)),
// OVERVIEW
    _lblOverview(tr("overview")),
    _btnBalance((tr("balance") + ":   " + formatDecimal2ToString(_transactionService.getSummary().getBalance())).strVal()),
    _btnIncome((tr("income") + ":    " + formatDecimal2ToString(_transactionService.getSummary().getIncome())).strVal()),
    _btnExpense((tr("expense") + ":   " + formatDecimal2ToString(_transactionService.getSummary().getExpense())).strVal()),

// GRAPH
    _lblGraph(tr("balance")),
    _graphReplacement("Line chart replacement"),

// INPUT
    _lblAddNewTransaction(tr("addNewTransaction")),

    _dateEdit(tr("date")),
    _cbCategory(tr("category")),
    _cbType(tr("type")),
    _neAmount(td::DataType::decimal2, gui::LineEdit::Messages::DoNotSend, true, tr("amount")),

    _btnCancel(tr("cancel")),
    _btnSave(tr("save")),

// DONUT
    _lblExpenseByCategory(tr("expenseByCategory")),
    _donutReplacement("Donut chart replacement"),

// LAYOUTS
    _hMainLayout(3),
    _vCentralMainLayout(7),

    _hFirstRowLayout(3),
    _vOverviewLayout(5),
    _vGraphLayout(2),

    _hSecondRowLayout(3),
    _vNewTransactionLayout(3),
    _vDonutLayout(2),
    _hInputLayout(4),
    _hButtonLayout(5),

    _vTransactionHistoryLayout(2)
{
    setStyles();
    arrangeElements();
}

const char* MainView::formatDecimal2ToString(const td::Decimal2& number) {
    double value = number.getAsFloat();
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", value);
    const char* cstr = buffer;
    return cstr;
}

void MainView::setStyles() {
    ComponentUtils::setOverviewButtonStyle(_btnBalance);
    ComponentUtils::setOverviewButtonStyle(_btnIncome);
    ComponentUtils::setOverviewButtonStyle(_btnExpense);
    ComponentUtils::setTitleStyle(_lblOverview);
    ComponentUtils::setTitleStyle(_lblGraph);
    ComponentUtils::setTitleStyle(_graphReplacement);
    ComponentUtils::setTitleStyle(_lblAddNewTransaction);
    ComponentUtils::setTitleStyle(_lblExpenseByCategory);
    ComponentUtils::setTitleStyle(_donutReplacement);
    ComponentUtils::setDefaultButtonStyle(_btnSave);
    ComponentUtils::setDefaultButtonStyle(_btnCancel);
}


void MainView::arrangeElements() {
    arrangeOverviewLayout();
    arrangeGraphLayout();
    arrangeNewTransactionLayout();
    arrangeDonutLayout();
    arrangeFirstRowLayout();
    arrangeSecondRowLayout();
    arrangeVerticalCentralLayout();
    arrangeMainLayout();
}

void MainView::arrangeOverviewLayout() {
    _vOverviewLayout.append(_lblOverview, td::HAlignment::Left);
    // _vOverviewLayout.appendSpacer();
    _vOverviewLayout.append(_btnBalance);
    _vOverviewLayout.append(_btnIncome);
    _vOverviewLayout.append(_btnExpense);
}

void MainView::arrangeGraphLayout() {
    _vGraphLayout.append(_lblGraph, td::HAlignment::Left);
    _vGraphLayout.append(_graphReplacement);
}

void MainView::arrangeNewTransactionLayout() {
    arrangeInputLayout();
    arrangeButtonLayout();
    _vNewTransactionLayout.append(_lblAddNewTransaction, td::HAlignment::Left);
    _vNewTransactionLayout.appendLayout(_hInputLayout);
    _vNewTransactionLayout.appendLayout(_hButtonLayout);
}

void MainView::arrangeInputLayout() {
    _hInputLayout.append(_dateEdit);
    _hInputLayout.append(_cbCategory);
    _hInputLayout.append(_cbType);
    _hInputLayout.append(_neAmount);
}

void MainView::arrangeButtonLayout() {
    _hButtonLayout.appendSpacer();
    _hButtonLayout.append(_btnCancel);
    _hButtonLayout.appendSpacer(3);
    _hButtonLayout.append(_btnSave);
    _hButtonLayout.appendSpacer();
}

void MainView::arrangeDonutLayout() {
    _vDonutLayout.append(_lblExpenseByCategory, td::HAlignment::Left);
    _vDonutLayout.append(_donutReplacement);
}



void MainView::arrangeFirstRowLayout(){
    _hFirstRowLayout.appendLayout(_vOverviewLayout);
    _hFirstRowLayout.appendSpacer();
    _hFirstRowLayout.appendLayout(_vGraphLayout);
}

void MainView::arrangeSecondRowLayout() {
    _hSecondRowLayout.appendLayout(_vNewTransactionLayout);
    _hSecondRowLayout.appendSpacer(5);
    _hSecondRowLayout.appendLayout(_vDonutLayout);

}

void MainView::arrangeVerticalCentralLayout(){
    _vCentralMainLayout.appendSpacer(2);
    _vCentralMainLayout.appendLayout(_hFirstRowLayout);
    _vCentralMainLayout.appendSpacer(1);
    _vCentralMainLayout.appendLayout(_hSecondRowLayout);
    _vCentralMainLayout.appendSpacer(1);
    _vCentralMainLayout.appendLayout(_vTransactionHistoryLayout);
    _vCentralMainLayout.appendSpacer(2);
}

void MainView::arrangeMainLayout(){
    _hMainLayout.appendSpacer();
    _hMainLayout.appendLayout(_vCentralMainLayout);
    _hMainLayout.appendSpacer();
    setLayout(&_hMainLayout);
}

bool MainView::onClick(gui::Button* pBtn){
    if (pBtn == &_btnBalance)
        changeGraphToBalance();
    else if (pBtn == &_btnIncome)
        changeGraphToIncome();
    else if (pBtn == &_btnExpense)
        changeGraphToExpense();

    return true;
}

void MainView::changeGraphToBalance(){
    _lblGraph.setTitle(tr("balance"));
    //TODO: implement graph change to balance
}

void MainView::changeGraphToIncome(){
    _lblGraph.setTitle(tr("income"));
    //TODO: implement graph change to income
}

void MainView::changeGraphToExpense(){
    _lblGraph.setTitle(tr("expense"));
    //TODO: implement graph change to expense
}


