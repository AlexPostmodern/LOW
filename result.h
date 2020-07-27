#ifndef RESULT_H
#define RESULT_H

#include <mainwindow.h>
#include <functioins.h>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class Result;
}

class Result : public MainWindow
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();
signals:
    void closeResult(int *, int *);
public slots:
    void openResult1(int *x, int *y);
    void openResultFromMenu(int *x, int *y);
    void on_pushButtonOk_clicked();

private slots:
    void on_pushButtonMore_clicked();

private:
    Ui::Result *ui;
    DataBase *db;
    bool pressBtn=false;
};

#endif // RESULT_H
