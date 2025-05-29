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
    _graph(user),

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
    _pie(user),

// TRANSACTION HISTORY
    _lblTransactionHistory(tr("transactionHistory")),
    _btnExport(tr("export")),
    _btnDelete(tr("delete")),

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
    _vTransactionHistoryLayout(2),
    _hTransactionHistoryLayout(2),
    _vExportButtonLayout(2)
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
    ComponentUtils::setTitleStyle(_lblAddNewTransaction);
    ComponentUtils::setTitleStyle(_lblExpenseByCategory);
    ComponentUtils::setTitleStyle(_lblTransactionHistory);
    ComponentUtils::setDefaultButtonStyle(_btnSave);
    _btnSave.setAsDefault();
    ComponentUtils::setDefaultButtonStyle(_btnCancel);
    ComponentUtils::setDefaultButtonStyle(_btnDelete);
    ComponentUtils::setDefaultButtonStyle(_btnExport);
    _btnExport.setAsDefault();
}

void MainView::initComboBoxes() {
    _cbType.addItems(std::vector<td::String>{"INCOME", "EXPENSE"});
    _cbType.selectIndex(0);

    _cbCategory.addItems(ComponentUtils::getIncomes());
    _cbCategory.selectIndex(0);
}

void MainView::initTable() {
    _dataSetPtr = _transactionService.findTransactionsIDataSetPtr();

        gui::Columns visCols(_tblTransactionHistory.allocBindColumns(6));
        visCols
        << gui::Header(0, tr("id"), tr("id"), 100)
        << td::Date::Format::ShortY4 << gui::Header(5, tr("date"), tr("date"),150)
        << gui::Header(2, tr("type"), tr("type"), 100, td::HAlignment::Right)
        << gui::Header(1, tr("category"), tr("category"), 170)
        << gui::Header(3, tr("amount"), tr("amount"), 100, td::HAlignment::Right)
        << gui::Header(4, tr("currency"), tr("currency"), 100, td::HAlignment::Left);
        _tblTransactionHistory.init(_dataSetPtr);
        _tblTransactionHistory.selectRow(0);
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
    _vGraphLayout.append(_graph);
}

void MainView::arrangeNewTransactionLayout() {
    _hInputLayout.setSize(gui::Size(300, 100));
    arrangeInputLayout();
    arrangeButtonLayout();
    _vNewTransactionLayout.append(_lblAddNewTransaction, td::HAlignment::Left);
    _vNewTransactionLayout.appendLayout(_hInputLayout);
    _vNewTransactionLayout.appendLayout(_hButtonLayout);
}

void MainView::arrangeInputLayout() {
    _dateEdit.setSize(gui::Size(30, 20));
    _cbType.setSize(gui::Size(70, 20));
    _cbCategory.setSize(gui::Size(70, 20));
    _neAmount.setSize(gui::Size(30, 20));
    _hInputLayout.append(_dateEdit);
    _hInputLayout.append(_cbType);
    _hInputLayout.append(_cbCategory);
    _hInputLayout.append(_neAmount);
}

void MainView::arrangeButtonLayout() {
    _hButtonLayout.appendSpacer();
    _hButtonLayout.append(_btnCancel);
    _hButtonLayout.appendSpacer(2);
    _hButtonLayout.append(_btnSave);
    _hButtonLayout.appendSpacer();
}

void MainView::arrangeDonutLayout() {
    _vDonutLayout.append(_lblExpenseByCategory, td::HAlignment::Left);
    _vDonutLayout.append(_pie);
}



void MainView::arrangeFirstRowLayout(){
    _hFirstRowLayout.appendLayout(_vOverviewLayout);
    _hFirstRowLayout.appendSpacer();
    _hFirstRowLayout.appendLayout(_vGraphLayout);
}

void MainView::arrangeSecondRowLayout() {
    _hSecondRowLayout.appendLayout(_vNewTransactionLayout);
    _hSecondRowLayout.appendSpacer(2);
    _hSecondRowLayout.appendLayout(_vDonutLayout);

}

void MainView::arrangeThirdRowLayout() {
    _hThirdRowLayout.appendSpacer();
    _hThirdRowLayout.append(_vTransactionHistoryLayout, td::HAlignment::Center);
    _hThirdRowLayout.appendSpacer();
}




void MainView::arrangeTransactionHistoryLayout() {
    _tblTransactionHistory.setSize(gui::Size(500, 50));
    _hTransactionHistoryLayout.append(_tblTransactionHistory);
    arrangeExportButtonLayout();
    _hTransactionHistoryLayout.appendLayout(_vExportButtonLayout);

    _vTransactionHistoryLayout.append(_lblTransactionHistory);
    _vTransactionHistoryLayout.appendLayout(_hTransactionHistoryLayout);
}

void MainView::arrangeExportButtonLayout() {
    _vExportButtonLayout.append(_btnExport, td::HAlignment::Left, td::VAlignment::Top);
    _vExportButtonLayout.append(_btnDelete, td::HAlignment::Left, td::VAlignment::Bottom);
}



void MainView::arrangeVerticalCentralLayout(){
    _vCentralMainLayout.appendSpacer(1);
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
    else if (pBtn == &_btnExport)
        return handleExportButton();
    else if (pBtn == &_btnDelete)
        return handleDeleteButton();

    return true;
}

bool MainView::onChangedSelection(gui::ComboBox* pCmb) {
    if (pCmb == &_cbType)
        onChangeCategoryComboBox();
    return true;
}

void MainView::changeGraphToBalance(){
    _lblGraph.setTitle(tr("balance"));
    _graph.changeDataType("Balance");
}

void MainView::changeGraphToIncome(){
    _lblGraph.setTitle(tr("income"));
    _graph.changeDataType("Income");
}

void MainView::changeGraphToExpense(){
    _lblGraph.setTitle(tr("expense"));
    _graph.changeDataType("Expense");
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
    // td::Variant categoryNameVar, categoryTypeVar, amountVar = _neAmount.getValue();
    // _cbType.getValue(categoryTypeVar);
    // _cbCategory.getValue(categoryNameVar);
    //
    // td::Decimal2 amount;
    // td::INT4 categoryName, categoryType;
    // td::Date date = _dateEdit.getValue();
    //
    // amountVar.getValue(amount);
    // categoryNameVar.getValue(categoryName);
    // categoryTypeVar.getValue(categoryType);
    //
    //
    // Category category = _categoryRepository.findCategoryByNameAndType(
    //                 ComponentUtils::getCategories()[categoryType][categoryName],
    //                 from_string(ComponentUtils::getCategoriesTypes()[categoryType].c_str())
    //             ).value();
    //
    // _transactionService.addNewTransaction(Transaction{0, _user, category, amount, "BAM", date, td::String()});

    reloadTable();
    return true;
}


void MainView::reloadTable() {
    _dataSetPtr = _transactionService.findTransactionsIDataSetPtr();
    _tblTransactionHistory.reload();
}

bool MainView::handleDeleteButton() {
    //TODO: implement delete functionality
    std::cout << "Delete Butoon Pressed" << td::endl;
    return true;
}

bool MainView::handleExportButton() {
    _transactionService.writeTransactionsToXml();
    showInfo(tr("success"), tr("successfulExport"));
    return true;
}





