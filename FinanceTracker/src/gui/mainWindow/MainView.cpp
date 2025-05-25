//
// Created by Amer on 25. 5. 2025..
//

#include "gui/mainWindow/MainView.h"
#include "domain/User.h"

MainView::MainView(User user):
    _user(user),
// OVERVIEW
    _lblOverview(tr("overview")),
    _btnBalance(tr("balance")),
    _btnIncome(tr("income")),
    _btnExpense(tr("expense")),

// LAYOUTS
    _hMainLayout(3),
    _vCentralMainLayout(7),

    _hFirstRowLayout(3),
    _vOverviewLayout(4),
    _vGraphLayout(2),

    _hSecondRowLayout(3),
    _vNewTransactionLayout(3),
    _vNewDonutLayout(2),
    _hInputLayout(4),
    _hButtonLayout(3),

    _vTransactionHistoryLayout(2)



{
    arrangeElements();
}


void MainView::arrangeElements() {
    arrangeOverviewLayout();
    arrangeFirstRowLayout();
    arrangeVerticalCentralLayout();
    arrangeMainLayout();
}

void MainView::arrangeOverviewLayout() {
    _vOverviewLayout.append(_lblOverview);
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
}





