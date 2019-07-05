#include "dialog1.h"
#include "ui_dialog1.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "score.h"

#include <iostream>
#include <string>
#include <QMessageBox>
bool AllIsNum(std::string s){
    for(int i = 0; i < s.size(); i++){
        int tmp = (int)s[i];
        if(tmp >= 48 && tmp <= 57) continue;
        else return false;
    }
    return true;
}

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_clicked()
{
    int score1 = 0;
    MainWindow *ptr = (MainWindow*)parentWidget();
    QString province_ = ptr->getDateComboBox();
    QString score_ = ui->lineEdit->text();
    QString facluty_ = ui->comboBox->currentText();
    std::string m_score = score_.toStdString();
	std::string facluty = facluty_.toStdString();
    std::string province = province_.toStdString();
    if(AllIsNum(m_score) == 1){
        score user(province, facluty, m_score);
        user.search();
        user.show();
        dialog2 = new Dialog2(this);
        dialog2->setModal(false);
        dialog2->setWindowTitle("查询结果");
        dialog2->show();
        dialog2->showschool();
    }
    else QMessageBox::about(NULL,"注意","成绩中不应含有违法字符");
    //std::cout << province << std::endl;
    //if(province == "北京") std::cout << "1" << std::endl;
    //std::cout << score << std::endl;

}

void Dialog1::on_pushButton_2_clicked()
{
    this->close();
}
