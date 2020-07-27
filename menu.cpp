#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    db=new DataBase(this);
    //кнопка админ
    ui->pushAdmin->setVisible(false);
    //координаты
    x=new int;
    y=new int;
    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/MainMenu.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    //цвет лейбла и шрифт
    id = QFontDatabase::addApplicationFont(":/fonts/MISTRAL.TTF"); //путь к шрифту
    family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
    mistral.setFamily(family);
    mistral.setBold(true);
    mistral.setPointSize(28);
    ui->labelName->setStyleSheet("color: rgb(110, 87, 51)");
    ui->labelName->setFont(mistral);

    //цвет фона у месадж боксов
    qApp->setStyleSheet("QMessageBox { background-color: rgb(215, 210, 203) }");
}

Menu::~Menu()
{
    delete ui;
    delete db;
}

//открытие окна Меню
void Menu::OpeningMenu(int *x, int *y)
{
    qDebug()<<"Signal in Menu is received!";    
    qDebug()<<"Name = "<<MainWindow::GetName();
    ui->labelName->setText("Добро пожаловать, "+MainWindow::GetName()+"!");
    //qDebug()<<"OpeningMenu x ="<<*x<<"y ="<<*y;
    this->move(*x,*y);
    if (MainWindow::GetLogin()=="admin"&&MainWindow::GetID()=="7")
    {
        ui->pushAdmin->setVisible(true);
    }
    Functioins::StartProgram(*this,"Главное меню",760,489);
}
void Menu::OpeningMenu()
{
    qDebug()<<"Signal in Menu is received!";
    qDebug()<<"Name = "<<MainWindow::GetName();
    ui->labelName->setText("Добро пожаловать, "+(MainWindow::GetName())+"!");
    //qDebug()<<"OpeningMenu x ="<<*x<<"y ="<<*y;;
    if (MainWindow::GetLogin()=="admin"&&MainWindow::GetID()=="7")
    {
        ui->pushAdmin->setVisible(true);
    }
    Functioins::StartProgram(*this,"Главное меню",760,489);
}
//открытие окна Эдитор
void Menu::on_editorButton_clicked()
{
    this->hide();
    Functioins::GetGeometry(*this,x,y);
    emit InvokeEditor(x,y);
}

void Menu::BackEditor(int *x, int *y)
{
    this->move(*x,*y);
    delete x; delete y;
    this->show();
}

void Menu::on_pushButton_clicked()
{
    this->hide();
    Functioins::GetGeometry(*this,x,y);
    emit InvokeChoosing(x,y);
}

void Menu::on_pushButton_5_clicked()
{
    this->hide();
    Functioins::GetGeometry(*this,x,y);
    emit InvokeResult(x,y);
}

void Menu::on_pushButtonExit_clicked()
{
    this->close();
}

void Menu::on_pushAdmin_clicked()
{
    this->hide();
    emit signal_InvokeAdmin();
}

void Menu::on_pushChangeUser_clicked()
{
    this->hide();
    db->db_Query("update RegUsers set lastEnter=0;");
    ui->pushAdmin->setVisible(false);
    Functioins::GetGeometry(*this,x,y);
    emit signalInvokeMainWindow(x,y);
}
