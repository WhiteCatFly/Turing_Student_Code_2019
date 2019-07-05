#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dialog2.h"
#include "dialog3.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_Dialog_accepted();

    void on_label_2_linkActivated(const QString &link);

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    Dialog2 *dialog2;
    Dialog3 *dialog3;
};

#endif // DIALOG_H
