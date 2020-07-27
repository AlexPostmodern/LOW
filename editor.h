#ifndef EDITOR_H
#define EDITOR_H

#include "mainwindow.h"

namespace Ui {
class Editor;
}

class Editor : public MainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

signals:
    void InvokeMenuBack(int*, int*);
    void InvokeInstruction();
    void InvokeUpdateWG(QString*);
    void InvokeUpdateWord(QString*,QString*,QString*);

public slots:
void OpeningEditor(int *x, int *y);
void ValuesComboBoxAfterUpdate(QString sourceSignal);

private slots:
void on_buttonOkEditor_clicked();
void pushButtonAddEnabled();
void on_pushButtonAdd_clicked();
void pushButtonadd2Enabled();
void on_pushButtonAdd2_clicked();
void on_pushButtonDelGroup_clicked();
void on_pushButtonSearch_clicked();
void pushButtonAddGroupEnabled();
void on_pushButtonShowAdd_clicked();
void on_pushButtonAddGroup_clicked();
void on_pushButtonBack_clicked();
void on_pushButtonDelWord_clicked();
void on_pushButtonHelp_clicked();
void on_pushUpdateWG_clicked();
void on_pushUpdateWord_clicked();

private:

    Ui::Editor *ui;
    DataBase *db;
    QString queryString1, queryString2, queryString3, text, stringArrRus,stringArrEng;
    QString queryString4,queryString5,queryString6,queryString7,queryString8,queryString9;
    QString str1,*strname;
    QMessageBox::StandardButton reply;
    bool SearchPressed=false;
};

#endif // EDITOR_H
