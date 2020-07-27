#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

//деструктор
Admin::~Admin()
{
    delete ui;
}

//событие закрытия окна
void Admin::closeEvent(QCloseEvent *event)
{
    if(Functioins::CloseProgram(*this, event,"Подтверждение выхода","Вы действительно хотите выйти?"))
    {
        ui->textEditReadOnly->clear();
        delete highlighter;
        delete db;
        //правильное удаление вектора из указателей
        for (QVector<QStandardItem*>::iterator it=items.begin();it!=items.end();it++)
        {
            delete *it;
        }
        items.clear();
        delete model;
        for (QVector<QStandardItem*>::iterator it=itemsRegUsers.begin();it!=itemsRegUsers.end();it++)
        {
            delete *it;
        }
        itemsRegUsers.clear();
        delete modelRegUsers;
        event->accept();
    }
}

//слот открытия окна
void Admin::slot_OpenAdmin()
{
    highlighter = new NewSyntax(ui->textEdit->document());
    db=new DataBase(this);
    ui->textEditReadOnly->setReadOnly(true);
    ui->textEditReadOnly->setStyleSheet("color: gray");
    ui->textReadOnlyQuery->setReadOnly(true);
    ui->textReadOnlyQuery->setStyleSheet("color: gray");
    ui->textReadOnlyQuery->setText("ЗАПРОСЫ:"
                                   "\n\n1. SELECT * FROM *tableName*;"
                                   "\n\n2. INSERT INTO *tableName* (*name*,*name*,*name*) VALUES (*data*,*data*,*data*;)"
                                   "\n\n3. SELECT *name* from *tableName* WHERE (*name*=*data* AND/OR *name_2*=*data_2*);"
                                   "\n\n4. UPDATE *tableName* SET *name*=*data*;"
                                   "\n\n5. DELETE FROM *tableName* WHERE *name*=*data*;"
                                   "\n\n6. CОРТИРОВКА: SELECT * FROM *tableName* order by *name*; desc - от большего к меньшему"
                                   "\n\n7. CREATE TABLE *tableName*(*name* *type of data*, *name_2* *type of data_2*);"
                                   "\n\n8. DROP TABLE *tableName*;"
                                   "\n\n9. ALTER TABLE *tableName* ADD COLUMN *columnName* *type of data*;"
                                   "\n\n10. СУММА/MAX: SELECT count(*)/max(*name*) FROM *tableName*;");
    countOfTables=(db->db_QueryRecordOneNumber("select count(*) from sqlite_master where "
                                                   "(type = 'table' and name not like 'sqlite_%')",0,0)).toInt();
    qDebug()<<"count of tables ="<<countOfTables;
    model = new QStandardItemModel;//новая модель списка
    db->db_Transaction("open");
    for (int i=0;i<countOfTables;i++)
    {
        item=new QStandardItem;
        item->setText(db->db_QueryRecordOneNumber("select name from sqlite_master where "
                                                     "(type = 'table' and name not like 'sqlite_%')",0,i));
        items.append(item);
        model->appendRow(items.at(i));
        ui->listView->setModel(model);
    }
    countOfUsers=(db->db_QueryRecordOneNumber("select count(*) from RegUsers;",0,0)).toInt();
    qDebug()<<"count of users ="<<countOfUsers;
    modelRegUsers=new QStandardItemModel;
    RegUsers reg;
    for (int i=0;i<countOfUsers;i++)
    {
        reg.id=(db->db_QueryRecordOneNumber("select id from RegUsers",0,i));
        reg.login=(db->db_QueryRecordOneNumber("select login from RegUsers",0,i));
        reg.name=(db->db_QueryRecordOneNumber("select name from RegUsers",0,i));
        reg.pass=(db->db_QueryRecordOneNumber("select pass from RegUsers",0,i));
        reg.row=i;
        item=new QStandardItem;
        item->setText(reg.login);
        regUsers.append(reg);
        itemsRegUsers.append(item);
        modelRegUsers->appendRow(itemsRegUsers.at(i));
        ui->listViewRegUsers->setModel(modelRegUsers);
    }
    db->db_Transaction("commit");
    //Background
    QPalette Pal(palette());
    QImage bgAdmin(":/background/AdminWindow.jpg");
    Pal.setBrush(QPalette::Background, bgAdmin);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->textEdit, SIGNAL(signalReturnPressed()), this, SLOT(returnClick()));
    Functioins::StartProgram(*this,"ADMIN",1220,800);
}

//функция изменения в лист вью с ПОЛЬЗОВАТЕЛЯМИ
void Admin::slot_ChangeListRegUsers(QString signalstr)
{
    RegUsers reg;
    if(signalstr=="Update")
    {
        QString id=regUsers.at(rowRegUsersUpdating).id;
        reg.id=id;
        reg.login=(db->db_QueryRecordOneNumber("select login from RegUsers",0,rowRegUsersUpdating));
        reg.name=(db->db_QueryRecordOneNumber("select name from RegUsers",0,rowRegUsersUpdating));
        reg.pass=(db->db_QueryRecordOneNumber("select pass from RegUsers",0,rowRegUsersUpdating));
        reg.row=rowRegUsersUpdating;
        regUsers[rowRegUsersUpdating]=reg;
        itemsRegUsers.at(rowRegUsersUpdating)->setText(regUsers.at(rowRegUsersUpdating).login);
    }
    if(signalstr=="New")
    {
        reg.id=(db->db_QueryRecordOneNumber("select max(id) from RegUsers",0,0));
        reg.login=(db->db_QueryRecordOneNumber("select login from RegUsers where id="+reg.id,0,0));
        reg.name=(db->db_QueryRecordOneNumber("select name from RegUsers where id="+reg.id,0,0));
        reg.pass=(db->db_QueryRecordOneNumber("select pass from RegUsers where id="+reg.id,0,0));
        reg.row=regUsers.size();
        item=new QStandardItem;
        item->setText(reg.login);
        itemsRegUsers.append(item);
        regUsers.append(reg);
        modelRegUsers->appendRow((item));
        ui->listViewRegUsers->setModel(modelRegUsers);
    }
}

//кнопка "ПРИНЯТЬ", выполнение запроса
void Admin::on_pushOK_clicked()
{
    strquery.clear();
    text=ui->textEdit->toPlainText();
    qDebug()<<text.size();
    for(int i=0;i<text.size();)
    {
        if(text.at(i)==";"||i==text.size()-1)
        {
            strquery.append(text.at(i));
            qDebug()<<"strquery ="<<strquery;
            if (textReadOnly.isEmpty())
                textReadOnly.append(strquery);
            else
                textReadOnly.append("\n"+strquery);
            ui->textEditReadOnly->setText(textReadOnly);
            db->db_TableModel(ui->tableView,strquery);
            ui->textEdit->clear();
            break;
        }
        strquery.append(text.at(i));
        i++;
    }
    delete highlighter;
    highlighter = new NewSyntax(ui->textEdit->document());
    this->on_pushButtonUpdate_clicked();
    this->on_pushUpdateRegUsers_clicked();
}

//кнопка "ОЧИСТИТЬ" историю запросов
void Admin::on_pushClear_clicked()
{
    textReadOnly.clear();
    ui->textEditReadOnly->clear();
}

//событие нажатия ентер в текст едит
void Admin::returnClick()
{
    this->on_pushOK_clicked();
}

//кнопка "ОБНОВИТЬ" лист вью с ТАБЛИЦАМИ
void Admin::on_pushButtonUpdate_clicked()
{
    countOfTables=(db->db_QueryRecordOneNumber("select count(*) from sqlite_master where "
                                                   "(type = 'table' and name not like 'sqlite_%')",0,0)).toInt();
    for (QVector<QStandardItem*>::iterator it=items.begin();it!=items.end();it++)
    {
        delete *it;
    }
    items.clear();
    model->clear();
    db->db_Transaction("open");
    for (int i=0;i<countOfTables;i++)
    {
        item=new QStandardItem;
        item->setText(db->db_QueryRecordOneNumber("select name from sqlite_master where "
                                                     "(type = 'table' and name not like 'sqlite_%')",0,i));
        items.append(item);
        model->appendRow(items.at(i));
        ui->listView->setModel(model);
    }
    db->db_Transaction("commit");
}

//кнопка "ОБНОВИТЬ" лист вью с ПОЛЬЗОВАТЕЛЯМИ
void Admin::on_pushUpdateRegUsers_clicked()
{
    countOfUsers=(db->db_QueryRecordOneNumber("select count(*) from RegUsers;",0,0)).toInt();
    for (QVector<QStandardItem*>::iterator it=itemsRegUsers.begin();it!=itemsRegUsers.end();it++)
    {
        delete *it;
    }
    itemsRegUsers.clear();
    modelRegUsers->clear();
    regUsers.clear();
    RegUsers reg;
    db->db_Transaction("open");
    for (int i=0;i<countOfUsers;i++)
    {
        reg.id=(db->db_QueryRecordOneNumber("select id from RegUsers",0,i));
        reg.login=(db->db_QueryRecordOneNumber("select login from RegUsers",0,i));
        reg.name=(db->db_QueryRecordOneNumber("select name from RegUsers",0,i));
        reg.pass=(db->db_QueryRecordOneNumber("select pass from RegUsers",0,i));
        reg.row=i;
        item=new QStandardItem;
        item->setText(reg.login);
        regUsers.append(reg);
        itemsRegUsers.append(item);
        modelRegUsers->appendRow(itemsRegUsers.at(i));
        ui->listViewRegUsers->setModel(modelRegUsers);
    }
    db->db_Transaction("commit");
}

//кнопка "ПОДРОБНЕЕ" с ПОЛЬЗОВАТЕЛЯМИ
void Admin::on_pushButtonAlter_clicked()
{
    if (ui->listViewRegUsers->currentIndex().row()==-1)
    {
        QMessageBox::information(this,"Ошибка","Пожалуйста, выберите пользователя!");
        return;
    }
    idRegUsersUpdating=regUsers.at(ui->listViewRegUsers->currentIndex().row()).id;
    rowRegUsersUpdating=regUsers.at(ui->listViewRegUsers->currentIndex().row()).row;
    qDebug()<<idRegUsersUpdating;
    emit signalInvokeUpdateAdmin(idRegUsersUpdating);
    //this->setEnabled(false);
}

//кнопка "ДОБАВИТЬ ПОЛЬЗОВАТЕЛЯ"
void Admin::on_pushButtonAddRegUser_clicked()
{
    emit  signalNewRegUser();
    //this->setEnabled(false);
}

//кнопка "УДАЛИТЬ ПОЛЬЗОВАТЕЛЯ"
void Admin::on_pushDeleteRegUsers_clicked()
{
    QMessageBox::StandardButton reply;
    if (ui->listViewRegUsers->currentIndex().row()==-1)
    {
        QMessageBox::information(this,"Ошибка","Пожалуйста, выберите пользователя!");
        return;
    }
    if (itemsRegUsers.at(ui->listViewRegUsers->currentIndex().row())->text()=="admin")
    {
        QMessageBox::information(this,"Ошибка","Вы не можете удалить этого пользователя!");
        return;
    }
    reply = QMessageBox::question(this,"Подтверждение удаления",
                                  "Вы действительно хотите удалить этого пользователя?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        db->db_Transaction("open");
        idRegUsersUpdating=regUsers.at(ui->listViewRegUsers->currentIndex().row()).id;
        int countOfWG=((db->db_QueryRecordOneNumber("select count(*) from WordGroup where userid="+idRegUsersUpdating,0,0)).toInt());
        int countOfResult=((db->db_QueryRecordOneNumber("select count(*) from Result where userid="+idRegUsersUpdating,0,0)).toInt());
        QString idWG,idResult;
        for (int i=0;i<countOfWG;i++)
        {
            idWG=db->db_QueryRecordOneNumber("select id from WordGroup where userid="+idRegUsersUpdating,0,i);
            db->db_Query("delete from Words where wordid="+idWG);
            db->db_Query("delete from WordGroup where id="+idWG);
        }
        for (int i=0;i<countOfResult;i++)
        {
            idResult=db->db_QueryRecordOneNumber("select id from Result where userid="+idRegUsersUpdating,0,i);
            db->db_Query("delete from ResultMore where resultid="+idResult);
            db->db_Query("delete from Result where id="+idResult);
        }
        db->db_Query("delete from RegUsers where id="+idRegUsersUpdating);
        db->db_Transaction("commit");
        this->on_pushUpdateRegUsers_clicked();
    }
}

//кнопка "НАЗАД"
void Admin::on_pushButtonBack_clicked()
{
    emit signalInvokeMenuFromAdmin();
    this->close();
}

//кнопка "ПОДРОБНЕЕ" с ТАБЛИЦАМИ
void Admin::on_pushButtonMore_clicked()
{
    if (ui->listView->currentIndex().row()==-1)
    {
        QMessageBox::information(this,"Ошибка","Пожалуйста, выберите таблицу!");
        return;
    }
    else
    {
        emit singalInvokeUpdateTables(items.at(ui->listView->currentIndex().row())->text());
    }
}

//кнопка "УДАЛИТЬ ТАБЛИЦУ"
void Admin::on_pushButtonDelete_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Подтверждение удаления",
                                  "Вы действительно хотите удалить эту таблицу?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        db->db_Query("drop table "+items.at(ui->listView->currentIndex().row())->text());
        this->on_pushButtonUpdate_clicked();
    }
}
