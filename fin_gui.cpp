#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget window;
  window.setWindowTitle("Financial Tracker");
  window.setMinimumSize(600,400);

  //Title 
  QLabel titleLabel("Financial Tracker");
  titleLabel.setAlignment(Qt::AlignHCenter);
  titleLabel.setStyleSheet("font-size: 48px;");

  //Income 
  QHBoxLayout *incomeLayout = new QHBoxLayout;
  QLabel incomeLabel("Income: ");
  incomeLabel.setStyleSheet("font-size: 32px");
  QLineEdit incomeEdit;
  incomeEdit.setStyleSheet("background-color: white; color: black; font-size: 32px;");
  incomeLayout->addWidget(&incomeLabel);
  incomeLayout->addWidget(&incomeEdit);
  QWidget *incomeWidget = new QWidget;
  incomeWidget->setLayout(incomeLayout);

  //Income function - Save User Enterned Income 
  double savedIncome = 0.0;

  QObject::connect(&incomeEdit, &QLineEdit::returnPressed, [&incomeEdit, &savedIncome, &window]() {
      bool convertOk;
      savedIncome = incomeEdit.text().toDouble(&convertOk);
      if (convertOk) {
        incomeEdit.setText(QString::number(savedIncome));
        QMessageBox::information(&window, "Success", "Income Recorded.");
      } else {
        QMessageBox::warning(&window, "Invalid Input", "Please Enter a Number for Income.");
      }
  });

  incomeEdit.setText(QString::number(savedIncome));
  
  //Expenses List - Title
  QVBoxLayout *expenseLayout = new QVBoxLayout;
  QHBoxLayout *expenseHeaderLayout = new QHBoxLayout;
  QLabel expenseListLabel("List of Expenses:");
  expenseListLabel.setStyleSheet("font-size: 32px;");
  expenseListLabel.setMaximumWidth(350);

  //Expense List - Actual List 
  QListWidget *expenseList = new QListWidget;
  expenseLayout->addWidget(expenseList);

  //Add to Expense List Button 
  QPushButton addExpense("Add Expense");
  addExpense.setStyleSheet("background-color: white; color: black; font-size: 32px;");
  
  //Add Expense Dialouge Box 
  QDialog addExpenseDialog;
  QVBoxLayout *addExpenseLayout = new QVBoxLayout;
  QLabel addExpenseLabel("Enter New Expense:");
  addExpenseLayout->addWidget(&addExpenseLabel);
  QLineEdit addExpenseEdit;
  addExpenseLayout->addWidget(&addExpenseEdit);
  QPushButton addExpenseConfirm("Add");
  addExpenseLayout->addWidget(&addExpenseConfirm);
  addExpenseDialog.setLayout(addExpenseLayout);

  //Button Funcitonality
 QObject::connect(&addExpense, &QPushButton::clicked, [&addExpenseDialog]() {
      addExpenseDialog.exec();
  });
 
 QObject::connect(&addExpenseConfirm, &QPushButton::clicked, [&addExpenseEdit, expenseList, &addExpenseDialog]() {
     QString newExpense = addExpenseEdit.text();
     if (!newExpense.isEmpty()) {
      expenseList->addItem(newExpense);
      addExpenseDialog.close();
      }
  });

 //Expense Layout 
 expenseHeaderLayout->addWidget(&expenseListLabel);
 expenseHeaderLayout->addWidget(&addExpense);
 expenseLayout->addLayout(expenseHeaderLayout);
 QWidget *expenseWidget = new QWidget;
 expenseWidget->setLayout(expenseLayout);
 
 //App Layout 
  QVBoxLayout layout;
  layout.addWidget(&titleLabel);
  layout.addWidget(incomeWidget);
  layout.addWidget(expenseWidget);
  for (int i = 0; i < expenseLayout->count(); ++i) {
    layout.addWidget(expenseLayout->itemAt(i)->widget());
  }

  window.setStyleSheet("background-color: black; color: green; font-size: 32px;");
  window.setLayout(&layout);
  window.show();

  return app.exec();
}
