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
// LAYOUTS
    _hMainLayout(3),
    _vCentralMainLayout(7),

    _hFirstRowLayout(3),
    _vOverviewLayout(5),
    _vGraphLayout(2),

    _hSecondRowLayout(3),
    _vNewTransactionLayout(3),
    _vNewDonutLayout(2),
    _hInputLayout(4),
    _hButtonLayout(3),

    _vTransactionHistoryLayout(2)
{
    //TODO: check if cache works properly when user is changed, or is it smth else
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
}


void MainView::arrangeElements() {
    arrangeOverviewLayout();
    arrangeFirstRowLayout();
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

void MainView::arrangeFirstRowLayout(){
    _hFirstRowLayout.appendLayout(_vOverviewLayout);
    _hFirstRowLayout.appendSpacer();
    _hFirstRowLayout.appendLayout(_vGraphLayout);
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





