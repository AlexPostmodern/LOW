#ifndef MENU_H
#define MENU_H

#include "mainwindow.h"
#include <QWidget>
#include <QtWidgets/QWidget>


namespace Ui {
class Menu;
}

class Menu : public MainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

signals:
    void InvokeEditor(int*, int*);
    void InvokeChoosing(int*, int*);
    void InvokeResult(int*, int*);
    void signal_InvokeAdmin();
    void signalInvokeMainWindow(int*, int*);

public slots:
    void OpeningMenu(int *x, int *y);
    void BackEditor(int *x, int *y);
    void OpeningMenu();

private slots:
    void on_editorButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButtonExit_clicked();

    void on_pushAdmin_clicked();

    void on_pushChangeUser_clicked();

private:
    Ui::Menu *ui;
    int *x,*y,id;
    QString family;
    QFont mistral;
    DataBase *db;
};

#endif // MENU_H
