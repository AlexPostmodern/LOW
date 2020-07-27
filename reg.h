#ifndef REG_H
#define REG_H

#include "mainwindow.h"
#include <QTime>
#include <QTimer>

namespace Ui {
class Reg;
}

class Reg : public MainWindow
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);
    ~Reg();

signals:
    void SetEnabledReg();

public slots:
    void OpeningReg(int*x, int*y);
    void OkEnabledReg();
    void on_okButtonReg_clicked();
    void on_BackButtonReg_clicked();


public:
private:
    Ui::Reg *ui;
    DataBase *db;

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_lineLoginReg_textChanged();
    void on_linePassReg_1_textChanged();
    void on_linePassReg_2_textChanged();
    void on_lineNameReg_textChanged();
};

#endif // REG_H
