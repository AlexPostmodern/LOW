#ifndef UPDATE_H
#define UPDATE_H

#include "mainwindow.h"

namespace Ui {
class Update;
}

class Update : public MainWindow
{
    Q_OBJECT

public:
    explicit Update(QWidget *parent = nullptr);
    ~Update();
public slots:
    void openUpdateWG(QString *name);
    void openUpdateWord(QString *idWord,QString *strWordRus,QString *strWordEng);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
signals:
    void InvokeEditorFromUpdate(QString);
private:
    Ui::Update *ui;
    DataBase *db;
    QMessageBox::StandardButton reply;
    QString nameWG, idWord, strWordRus,strWordEng,sourceSignal;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // UPDATE_H
