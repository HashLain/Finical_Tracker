#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget window;
  window.setWindowTitle("Financial Tracker");

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
  
  //Expenses List 
  QVBoxLayout *expenseLayout = new QVBoxLayout;
  QLabel expenseListLabel("List of Expenses:");
  expenseListLabel.setStyleSheet("font-size: 32px;");
  expenseLayout->addWidget(&expenseListLabel);

  //App Layout 
  QVBoxLayout layout;
  layout.addWidget(&titleLabel);
  layout.addWidget(incomeWidget);
  layout.addWidget(&expenseListLabel);

  window.setStyleSheet("background-color: black; color: green;");
  window.setLayout(&layout);
  window.show();

  return app.exec();
}
