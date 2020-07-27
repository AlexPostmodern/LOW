#ifndef UPDATEADMIN_H
#define UPDATEADMIN_H

#include "mainwindow.h"

namespace Ui {
class UpdateAdmin;
}

class UpdateAdmin : public MainWindow
{
    Q_OBJECT

public:
    explicit UpdateAdmin(QWidget *parent = nullptr);
    ~UpdateAdmin() override;
public slots:
    void slotOpenUpdateAdmin(QString idRegUser);
    void slotNewRegUser();
signals:
    void signalUpdateHasDone(QString);
private slots:
    void on_pushCancel_clicked();
    void on_pushOk_clicked();

private:
    Ui::UpdateAdmin *ui;
    DataBase *db;
    QString idRegUser,signalStr;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // UPDATEADMIN_H
