#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString getDateComboBox();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    Dialog1 *dialog1;
};

#endif // MAINWINDOW_H
