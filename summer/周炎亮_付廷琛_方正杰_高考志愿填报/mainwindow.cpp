#include <iostream>
#include <typeinfo>
#include <QHeaderView>
#include <QComboBox>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
     QString province = ui->comboBox_2->currentText();
     std::string province_ = province.toStdString();
     //std::cout << typeid(score_).name() << std::endl;
     if(province == "浙江"){
         dialog = new Dialog(this);
         dialog->setModal(false);
         dialog->setWindowTitle("科类及分数");
         dialog->show();
     }
     else{
         dialog1 = new Dialog1(this);
         dialog1->setModal(false);
         dialog1->setWindowTitle("科类及分数");
         dialog1->show();
     }

}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::exit();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

QString MainWindow::getDateComboBox(){
    QComboBox *combobox = ui->comboBox_2;
    return combobox->currentText();
}
