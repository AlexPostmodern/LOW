#include "updatetables.h"
#include "ui_updatetables.h"

UpdateTables::UpdateTables(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::UpdateTables)
{
    ui->setupUi(this);
}

//деструктор
UpdateTables::~UpdateTables()
{
    delete ui;
}

//функция закрытия окна
void UpdateTables::closeEvent(QCloseEvent *event)
{
    delete db;
    event->accept();
}

//слот открытия окна
void UpdateTables::slotOpenUpdateTables(QString name)
{
    db=new DataBase(this);
    db->db_TableModel(ui->tableView,"PRAGMA table_info("+name+")");
    ui->label->setText("Информация о таблице - "+name);
    Functioins::StartProgram(*this,"Информация о таблице",700,400);
}

//кнопка "ПРИНЯТЬ"
void UpdateTables::on_pushButton_clicked()
{
    this->close();
}
