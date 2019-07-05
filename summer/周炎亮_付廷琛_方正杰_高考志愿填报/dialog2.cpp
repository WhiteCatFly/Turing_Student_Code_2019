#include "dialog2.h"
#include "ui_dialog2.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include <QByteArray>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::showschool(){
    QString dataFromFile;
    QFile file("C:\\Users\\Administrator\\Documents\\build-untitled-Desktop_Qt_5_6_1_MinGW_32bit-Debug\\ans.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "can not open";
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str1 = stream.readLine();
    ui->textBrowser->setText(str1);
    QString str2 = stream.readLine();
    ui->textBrowser_2->setText(str2);
    QString str3 = stream.readLine();
    ui->textBrowser_3->setText(str3);
    QString str4 = stream.readLine();
    ui->textBrowser_4->setText(str4);
    QString str5 = stream.readLine();
    ui->textBrowser_5->setText(str5);
    QString str6 = stream.readLine();
    ui->textBrowser_6->setText(str6);
    QString str7 = stream.readLine();
    ui->textBrowser_7->setText(str7);
    QString str8 = stream.readLine();
    ui->textBrowser_8->setText(str8);
    QString str9 = stream.readLine();
    ui->textBrowser_9->setText(str9);
    QString str10 = stream.readLine();
    ui->textBrowser_10->setText(str10);
}
