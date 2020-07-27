#ifndef UPDATETABLES_H
#define UPDATETABLES_H

#include "mainwindow.h"

namespace Ui {
class UpdateTables;
}

class UpdateTables : public MainWindow
{
    Q_OBJECT

public:
    explicit UpdateTables(QWidget *parent = nullptr);
    ~UpdateTables()override;
public slots:
    void slotOpenUpdateTables(QString name);
private:
    Ui::UpdateTables *ui;
    DataBase *db;
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_pushButton_clicked();
};

#endif // UPDATETABLES_H
