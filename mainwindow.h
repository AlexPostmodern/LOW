#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "functioins.h"
#include "mytablemodel.h"
#include "newsyntax.h"
#include "mytextedit.h"
#include <QMainWindow>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>
#include <QCheckBox>
#include <QDebug>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QFontDatabase>
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString GetID();
    static QString GetLogin();
    static QString GetName();
    static QString GetPass();
    static void SetId(QString value);
    static void SetLogin(QString value);
    static void SetName(QString value);
    static void SetPass(QString value);


public slots:
    void RegButtEnabled();
    void changeUser(int*,int*);

signals:
    void InvokeMenu(int*, int*);
    void InvokeReg(int*, int*);

private:
    Ui::MainWindow *ui;
    QString stringLogin,stringPass;
    static QString strLogin,strName,strPass,strId;
    int *x,*y;

private slots:
    void on_okButton_clicked();
    void OkEnabled();
    void on_checkBoxPass_toggled(bool checked);
    void on_RegistraionButton_clicked();
    void on_quitButton_clicked();

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
