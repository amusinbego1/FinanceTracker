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
    _categoryRepository(CategoryRepository::getInstance()),
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
    _cbType(tr("type")),
    _cbCategory(tr("category")),
    _neAmount(td::DataType::decimal2, gui::LineEdit::Messages::DoNotSend, true, tr("amount")),

    _btnCancel(tr("cancel")),
    _btnSave(tr("save")),

// DONUT
    _lblExpenseByCategory(tr("expenseByCategory")),
    _donutReplacement("Donut chart replacement"),

// TRANSACTION HISTORY
    _lblTransactionHistory(tr("transactionHistory")),


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

    _hThirdRowLayout(3),
    _vTransactionHistoryLayout(2)
{
    setStyles();
    initComboBoxes();
    arrangeElements();
    initTable();
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
    ComponentUtils::setTitleStyle(_lblTransactionHistory);
    ComponentUtils::setDefaultButtonStyle(_btnSave);
    ComponentUtils::setDefaultButtonStyle(_btnCancel);
}

void MainView::initComboBoxes() {
    _cbType.addItems(std::vector<td::String>{"INCOME", "EXPENSE"});
    _cbType.selectIndex(0);

    _cbCategory.addItems(ComponentUtils::getIncomes());
    _cbCategory.selectIndex(0);
}

void MainView::initTable(bool shouldAddHeaders) {
    _dataSetPtr = _transactionService.findTransactionsIDataSetPtr();

    if (shouldAddHeaders) {
        gui::Columns visCols(_tblTransactionHistory.allocBindColumns(6));
        visCols << gui::ThSep::DoNotShowThSep
        << gui::Header(0, tr("id"), tr("id"), 100)
        << td::Date::Format::ShortY4 << gui::Header(5, tr("date"), tr("date"),150)
        << gui::Header(2, tr("type"), tr("type"), 100, td::HAlignment::Right)
        << gui::Header(1, tr("category"), tr("category"), 170)
        << gui::Header(3, tr("amount"), tr("amount"), 100, td::HAlignment::Right)
        << gui::Header(4, tr("currency"), tr("currency"), 100, td::HAlignment::Left);
        _tblTransactionHistory.init(_dataSetPtr);
    }
    else
        _tblTransactionHistory.reload();
}

void MainView::onChangeCategoryComboBox() {
    _cbCategory.clean();
    _cbCategory.addItems(_cbType.getSelectedIndex() == 0 ? ComponentUtils::getIncomes(): ComponentUtils::getExpenses());
    _cbCategory.selectIndex(0);
}


void MainView::arrangeElements() {
    arrangeOverviewLayout();
    arrangeGraphLayout();
    arrangeNewTransactionLayout();
    arrangeDonutLayout();
    arrangeTransactionHistoryLayout();
    arrangeFirstRowLayout();
    arrangeSecondRowLayout();
    arrangeThirdRowLayout();
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
    _hInputLayout.append(_cbType);
    _hInputLayout.append(_cbCategory);
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

void MainView::arrangeThirdRowLayout() {
    _hThirdRowLayout.appendSpacer();
    _hThirdRowLayout.append(_vTransactionHistoryLayout, td::HAlignment::Center);
    _hThirdRowLayout.appendSpacer();
}


void MainView::arrangeTransactionHistoryLayout() {
    _vTransactionHistoryLayout.append(_lblTransactionHistory);
    _tblTransactionHistory.setSize(gui::Size(500, 50));
    _vTransactionHistoryLayout.append(_tblTransactionHistory);
}


void MainView::arrangeVerticalCentralLayout(){
    _vCentralMainLayout.appendSpacer(2);
    _vCentralMainLayout.appendLayout(_hFirstRowLayout);
    _vCentralMainLayout.appendSpacer(1);
    _vCentralMainLayout.appendLayout(_hSecondRowLayout);
    _vCentralMainLayout.appendSpacer(1);
    _vCentralMainLayout.appendLayout(_hThirdRowLayout);
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
    else if (pBtn == &_btnCancel)
        return handleCancelButton();
    else if (pBtn == &_btnSave)
        return handleSaveButton();

    return true;
}

bool MainView::onChangedSelection(gui::ComboBox* pCmb) {
    if (pCmb == &_cbType)
        onChangeCategoryComboBox();
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

bool MainView::handleCancelButton() {
    td::Date now; now.now();
    _dateEdit.setValue(now);
    _cbType.selectIndex(0);
    _cbCategory.selectIndex(0);
    _neAmount.setValue(td::Decimal2(0.0));
    return true;
}

bool MainView::handleSaveButton() {
    //TODO: make a category service for this stuff
    td::Variant categoryNameVar, categoryTypeVar, amountVar = _neAmount.getValue();
    _cbType.getValue(categoryTypeVar);
    _cbCategory.getValue(categoryNameVar);

    td::Decimal2 amount;
    td::UINT4 categoryName, categoryType;
    td::Date date = _dateEdit.getValue();

    amountVar.getValue(amount);
    categoryNameVar.getValue(categoryName);
    categoryTypeVar.getValue(categoryType);


    Category category = _categoryRepository.findCategoryByNameAndType(
                    ComponentUtils::getCategories()[categoryType][categoryName],
                    from_string(ComponentUtils::getCategoriesTypes()[categoryType].c_str())
                ).value();

    _transactionService.addNewTransaction(Transaction{0, _user, category, amount, "BAM", date, td::String()});

    reloadTable();
    return true;
}


void MainView::reloadTable() {
    // _tblTransactionHistory.clean();
    // _dataSetPtr->removeAll();
    _tblTransactionHistory.reload();
    // _dataSetPtr->release();
    // initTable(false);
    _tblTransactionHistory.selectRow(0);
}




