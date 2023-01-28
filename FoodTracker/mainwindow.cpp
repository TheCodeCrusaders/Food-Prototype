#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDate>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int column = 0; column < ui->tableWidget->columnCount(); column++) {
            calculate_date_exp(row, column);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::calculate_date_exp(int row, int column){
    if(column == 1){
        QString dateString;
        QTableWidgetItem* item = ui->tableWidget->item(row, column);
        if (item != nullptr) {
            dateString = item->text();
        } else {
            // handle empty cell
            return;
        }

        QDate date = QDate::fromString(dateString, "dd-MM-yyyy");
        if (!date.isValid()) {
            // Handle invalid date input
            return;
        }

        QDate today = QDate::currentDate();
        int daysUntil = date.daysTo(today) * -1;
        QString daysUntilS = QString::number(daysUntil);

        QTableWidgetItem* newItem = new QTableWidgetItem(daysUntilS);

        // Insert the new QTableWidgetItem into the new row in the next column
        ui->tableWidget->setItem(row, 2, newItem);

        // we need to save this to some online place for permanant changes.
    }
}


void MainWindow::on_lineEdit_add_item_returnPressed()
{
    // Get the current number of rows in the tableWidget
    int row = ui->tableWidget->rowCount();

    // Insert a new row at the end of the tableWidget
    ui->tableWidget->insertRow(row);

    // Create a new QTableWidgetItem with the text "test"
    QTableWidgetItem* newItem = new QTableWidgetItem(ui->lineEdit_add_item->text());

    // Insert the new QTableWidgetItem into the new row in the first column
    ui->tableWidget->setItem(row, 0, newItem);
    ui->lineEdit_add_item->clear();
}


void MainWindow::on_pushButton_add_item_clicked()
{
    // Get the current number of rows in the tableWidget
    int row = ui->tableWidget->rowCount();

    // Insert a new row at the end of the tableWidget
    ui->tableWidget->insertRow(row);

    // Create a new QTableWidgetItem with the text "test"
    QTableWidgetItem* newItem = new QTableWidgetItem(ui->lineEdit_add_item->text());

    // Insert the new QTableWidgetItem into the new row in the first column
    ui->tableWidget->setItem(row, 0, newItem);
    ui->lineEdit_add_item->clear();
}


void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    calculate_date_exp(row, column);
}



void MainWindow::on_listWidge_recepie_itemClicked(QListWidgetItem *item)
{
    // we need this changed to be web based.
    if(item->text() == "mashed potatoes"){
        ui->textBrowser_recepie->setText("HMMM mashed potatos, this is how you do dis.");
    }
    else if(item->text() == "spicy chicken"){
        ui->textBrowser_recepie->setText("spicy chicken dinner be a rinder.");
    } else {
        ui->textBrowser_recepie->setText(item->text() + " recipe is unknown.");


    }
}

