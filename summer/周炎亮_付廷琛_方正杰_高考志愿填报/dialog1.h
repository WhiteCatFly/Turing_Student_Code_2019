#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include "dialog2.h"

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_destroyed();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog1 *ui;
    Dialog2 *dialog2;
};

#endif // DIALOG1_H
