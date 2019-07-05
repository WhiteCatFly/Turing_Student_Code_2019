#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zjreco.h"

#include <iostream>
#include <string>
#include <QMessageBox>

int c_number = 0;
std::string sub[4];
int ARRAY[7]={0};
std::string subject[7]={"物理","化学","生物","政治","历史","地理","技术"};

bool AllIsNum1(std::string s){
    for(int i = 0; i < s.size(); i++){
        int tmp = (int)s[i];
        if(tmp >= 48 && tmp <= 57) continue;
        else return false;
    }
    return true;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_label_2_linkActivated(const QString &link)
{

}

void Dialog::on_pushButton_clicked()
{
    int score = 0;
    //std::string sub[3];
    std::string province = "浙江";
    if(ui->checkBox->isChecked() == true) {c_number++; ARRAY[0] = 1;}
    if(ui->checkBox_2->isChecked() == true) {c_number++; ARRAY[1] = 1;}
    if(ui->checkBox_3->isChecked() == true) {c_number++; ARRAY[2] = 1;}
    if(ui->checkBox_4->isChecked() == true) {c_number++; ARRAY[3] = 1;}
    if(ui->checkBox_5->isChecked() == true) {c_number++; ARRAY[4] = 1;}
    if(ui->checkBox_6->isChecked() == true) {c_number++; ARRAY[5] = 1;}
    if(ui->checkBox_7->isChecked() == true) {c_number++; ARRAY[6] = 1;}
    /*for(int i = 0;i < 7; i++){
        std::cout << ARRAY[i] << std::endl;
    }*/
    if(c_number != 3){
        QMessageBox::about(NULL,"注意","所选科目应为三科");
        c_number = 0;
    }
    else{
        /*for(int i = 0; i < 5; i++){
            if(ARRAY[i] == 1){
                sub[0] = subject[i];
                for(int j = i + 1; j < 6; j++){
                    if(ARRAY[j] == 1){
                        sub[1] = subject[j];
                        for(int k = j + 1; k < 7; k++){
                            if(ARRAY[k] == 1)
                                 sub[2] = subject[k];*/
        int k=0;
        for(int i=0;i<7;i++)
        {
            if(ARRAY[i]==1)
            {
                sub[k]=subject[i];
                k++;
            }
        }
                                //std::cout << a << b << c << std::endl;
                                 MainWindow *ptr = (MainWindow*)parentWidget();
                                 QString score_ = ui->lineEdit->text();
                                 std::string m_score = score_.toStdString();
                                if(AllIsNum1(m_score) == 1){
                                    score = stoi(m_score);
                                    zjreco a(sub,score);
                                    a.unite();
                                    dialog2 = new Dialog2(this);
                                    dialog2->setModal(false);
                                    dialog2->show();
                                    dialog2->showschool();
                                    c_number = 0;
                                }
                                else QMessageBox::about(NULL,"注意","成绩中不应含有违法字符");
                            //std::cout << province << std::endl;
                            //if(province == "北京") std::cout << "1" << std::endl;
                       c_number = 0;
                       return;
                       /*}
                    }
                 }
             }
        }*/

    }

}
