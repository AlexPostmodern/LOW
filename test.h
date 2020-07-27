#ifndef TEST_H
#define TEST_H

#include "mainwindow.h"
#include "QTimer"
#include "QTime"
#include <QMessageBox>

namespace Ui {
class Test;
}

class Test : public MainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

public slots:
    void fillArr(int *wgID, int*x, int*y);
    void fillArrCheck(int *x, int *y);


private slots:
    void Timer();
    void OpenTest(int *x, int *y);
    void on_pushButtonAnswer_clicked();
    void answerEnabled();
    void on_pushDontKnow_clicked();
    void endOfTest();
    void on_pushCancel_clicked();
    //void answerLater();
    void on_pushAnswerLater_clicked();

signals:
    void showResult1(int *, int *);
    void InvokeChoosing(int *, int *);
    void InvokeChoosing1(int *, int *);

private:
    Ui::Test *ui;
    QTimer *timer;
    QTime time;
    DataBase *db;
    int size,firstWordID, wordGroupID, check=0, *arrRandomId, count=0, *arrResult,*x,*y;
    int intWork,*arrAnswerBool,counterProgress=0;
    bool create=false, execute=false, OnePack=false, pressAnswerLater=false,end=false;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TEST_H
