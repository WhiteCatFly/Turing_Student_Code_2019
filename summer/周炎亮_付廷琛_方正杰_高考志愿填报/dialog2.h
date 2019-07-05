#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    void showschool();
    ~Dialog2();

private:
    Ui::Dialog2 *ui;
};

#endif // DIALOG2_H
