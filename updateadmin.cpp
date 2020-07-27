#include "updateadmin.h"
#include "ui_updateadmin.h"

UpdateAdmin::UpdateAdmin(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::UpdateAdmin)
{
    ui->setupUi(this);
}

//деструктор
UpdateAdmin::~UpdateAdmin()
{
    delete ui;
}

//событие закрытия окна
void UpdateAdmin::closeEvent(QCloseEvent *event)
{
    delete db;
    event->accept();
}

//слот открытия окна по нажатию кнопки "ИЗМЕНИТЬ ПОЛЬЗОВАТЕЛЯ"
void UpdateAdmin::slotOpenUpdateAdmin(QString idRegUser)
{
    db=new DataBase(this);
    //Background
    QPalette Pal(palette());
    QImage bgAdmin(":/background/Editor.jpg");
    Pal.setBrush(QPalette::Background, bgAdmin);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->idRegUser=idRegUser;
    ui->lineEditLogin->setReadOnly(false);
    if(this->idRegUser=="7")
        ui->lineEditLogin->setReadOnly(true);
    ui->labelinfo->setText("Информация о пользователе");
    ui->lineEditID->setVisible(true);
    ui->lineEditID->setReadOnly(true);
    ui->label_4->setVisible(true);
    ui->lineEditID->setText(idRegUser);
    ui->pushOk->setText("Изменить");
    ui->lineEditLogin->setText(db->db_QueryRecordOneNumber("select login from RegUsers "
                                                           "where id='"+idRegUser+"';",0,0));
    ui->lineEditPass->setText(db->db_QueryRecordOneNumber("select password from RegUsers "
                                                           "where id='"+idRegUser+"';",0,0));
    ui->lineEditName->setText(db->db_QueryRecordOneNumber("select name from RegUsers "
                                                           "where id='"+idRegUser+"';",0,0));
    signalStr="Update";
    Functioins::StartProgram(*this,"Информация", 350,200);
}

//кнопка "НАЗАД"
void UpdateAdmin::on_pushCancel_clicked()
{
    this->close();
}

//кнопка "ДОБАВИТЬ/ИЗМЕНИТЬ"
void UpdateAdmin::on_pushOk_clicked()
{
    int countOfUsers;
    if(signalStr=="Update")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Подтверждение изменения",
                                      "Вы действительно хотите изменить данные?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {

            QString strquery("update RegUsers set login='"+ui->lineEditLogin->text()+
                             "',password='"+ui->lineEditPass->text()+
                             "',name='"+ui->lineEditName->text()+"' where id="+idRegUser+";");
            db->db_Query(strquery);
            emit signalUpdateHasDone(signalStr);
            this->close();
        }
    }
    if(signalStr=="New")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Подтверждение добавления",
                                      "Вы действительно хотите добавить нового пользователя?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            countOfUsers=(db->db_QueryRecordOneNumber("select count(*) from RegUsers;",0,0).toUInt());
            for (int i=0;i<countOfUsers;i++)
            {
                if(ui->lineEditLogin->text()==db->db_QueryRecordOneNumber("select login from RegUsers;",0,i))
                {
                    QMessageBox::information(this,"Ошибка","Такой логин уже существует!");
                    return;
                }
            }
            QString strquery("insert into RegUsers (login,password,name)values('"+ui->lineEditLogin->text()+
                             "','"+ui->lineEditPass->text()+
                             "','"+ui->lineEditName->text()+"');");
            db->db_Query(strquery);
            emit signalUpdateHasDone(signalStr);
            this->close();
        }
    }
}

//слот открытия окна по нажатию кнопки "ДОБАВИТЬ ПОЛЬЗОВАТЕЛЯ"
void UpdateAdmin::slotNewRegUser()
{
    db=new DataBase(this);
    //Background
    QPalette Pal(palette());
    QImage bgAdmin(":/background/Editor.jpg");
    Pal.setBrush(QPalette::Background, bgAdmin);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    ui->lineEditLogin->setReadOnly(false);
    ui->labelinfo->setText("Добавить пользователя");
    ui->labelinfo->setText("Новый пользователь");
    ui->lineEditID->setVisible(false);
    ui->label_4->setVisible(false);
    ui->lineEditName->clear();
    ui->lineEditPass->clear();
    ui->lineEditLogin->clear();
    signalStr="New";
    ui->pushOk->setText("Добавить");
    Functioins::StartProgram(*this,"Добавить", 350,200);
}
