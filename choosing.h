#ifndef CHOOSING_H
#define CHOOSING_H

#include "mainwindow.h"

namespace Ui {
class Choosing;
}

class Choosing : public MainWindow
{
    Q_OBJECT

public:
    explicit Choosing(QWidget *parent = nullptr);
    ~Choosing();
public slots:
    void OpenChoosing(int *x, int *y);

signals:
    void InvokeTest(int*, int*, int*);
    void InvokeTestCheck(int*, int*);
    void InvokeMenuBack1(int*, int*);

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonBegin_clicked();

private:
    Ui::Choosing *ui;
    DataBase *db;
    QMessageBox::StandardButton reply;
};

#endif // CHOOSING_H
