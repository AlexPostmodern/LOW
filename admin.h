#ifndef ADMIN_H
#define ADMIN_H

#include "mainwindow.h"
#include <QStandardItemModel>
#include <QListWidgetItem>

namespace Ui {
class Admin;
}

class Admin : public MainWindow
{
    Q_OBJECT

public:

    //конструктор
    explicit Admin(QWidget *parent = nullptr);

    //деструктор
    ~Admin()override;

public slots:

    //слот открытия окна
    void slot_OpenAdmin();

    //функция изменения в лист вью с ПОЛЬЗОВАТЕЛЯМИ
    void slot_ChangeListRegUsers(QString signalstr);

private slots:

    //кнопка "ПРИНЯТЬ", выполнение запроса
    void on_pushOK_clicked();

    //кнопка "ОЧИСТИТЬ" историю запросов
    void on_pushClear_clicked();

    //событие нажатия ентер в текст едит
    void returnClick();

    //кнопка "ОБНОВИТЬ" лист вью с ТАБЛИЦАМИ
    void on_pushButtonUpdate_clicked();

    //кнопка "ОБНОВИТЬ" лист вью с ПОЛЬЗОВАТЕЛЯМИ
    void on_pushUpdateRegUsers_clicked();

    //кнопка "ПОДРОБНЕЕ" с ПОЛЬЗОВАТЕЛЯМИ
    void on_pushButtonAlter_clicked();

    //кнопка "ДОБАВИТЬ ПОЛЬЗОВАТЕЛЯ"
    void on_pushButtonAddRegUser_clicked();

    //кнопка "УДАЛИТЬ ПОЛЬЗОВАТЕЛЯ"
    void on_pushDeleteRegUsers_clicked();

    //кнопка "НАЗАД"
    void on_pushButtonBack_clicked();

    //кнопка "ПОДРОБНЕЕ" с ТАБЛИЦАМИ
    void on_pushButtonMore_clicked();

    //кнопка "УДАЛИТЬ ТАБЛИЦУ"
    void on_pushButtonDelete_clicked();

signals:

    //сигналы вызова UpdateAdmin
    void signalInvokeUpdateAdmin(QString);
    void signalNewRegUser();
    void signalInvokeMenuFromAdmin();
    void singalInvokeUpdateTables(QString);

private:
    Ui::Admin *ui;
    DataBase *db;
    QString strquery,text,textReadOnly,idRegUsersUpdating;
    NewSyntax *highlighter;
    QStandardItemModel *model,*modelRegUsers;
    QVector <QStandardItem*> items,itemsRegUsers;
    QStandardItem *item;
    int countOfTables,countOfUsers,rowRegUsersUpdating;
    struct RegUsers
    {
        QString id,login,name,pass;
        int row;
    };
    QVector <RegUsers> regUsers;

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // ADMIN_H
