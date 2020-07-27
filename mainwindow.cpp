#include "mainwindow.h"
#include "ui_mainwindow.h"
QString MainWindow::strLogin;
QString MainWindow::strName;
QString MainWindow::strPass;
QString MainWindow::strId;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //кнопку "Войти" нельзя нажать
    ui->okButton->setEnabled(false);

    //задание ограничения
    QRegExp expLogPass("[a-zA-Z0-9]{2,25}");
    //присваиваем полям ввода это ограничение, через валидатор
    ui->lineLogin->setValidator(new QRegExpValidator(expLogPass,this));
    ui->linePass->setValidator(new QRegExpValidator(expLogPass,this));
    connect(ui->lineLogin,SIGNAL(textChanged(QString)),this,SLOT(OkEnabled()));
    connect(ui->linePass,SIGNAL(textChanged(QString)),this,SLOT(OkEnabled()));
    //чтобы кнопка войти нажималась на ентер и чтобы кнопка горела нужно установить default галочку в ui
    connect(ui->linePass, SIGNAL(returnPressed()), this, SLOT(on_okButton_clicked()));
    x=new int;
    y=new int;

    //дизайн

    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/MainWindow.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    //стиль кнопок
    this->setStyleSheet("QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 230), stop:1 rgba(160, 141, 110, 150));}"
                        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(160, 141, 110, 200), stop:1 rgba(240, 240, 240, 230));}"
                        "QPushButton:pressed{background-color: rgba(110, 87, 51, 160)}"
                        "QComboBox {border: 1.2px solid gray;"
                                    "border-radius: 3px;"
                                    "padding: 1px 18px 1px 3px;"
                                    "min-width: 6em;}"
                        "QComboBox:editable{background: rgba(110, 87, 51, 150);}"
                        "QComboBox:!editable, QComboBox::drop-down:editable{"
                                    "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 230), stop:1 rgba(110, 87, 51, 150));}"
                        "QComboBox:!editable:on, QComboBox::drop-down:editable:on {"
                                    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,"
                                    "stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);}"
                        "QComboBox:on{padding-top: 3px;"
                                    "padding-left: 4px;}"
                        "QComboBox:hover{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,"
                                    "stop:0 rgba(160, 141, 110, 200), stop:1 rgba(240, 240, 240, 230));}"
                        "QLineEdit {border: 1.2px solid gray;"
                                    "border-radius: 7px;"
                                    "padding: 0 8px;"
                                    "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));"
                                    "selection-background-color: darkgray;}"
                        "QTableView {border-style : Solid;"
                                    "border-color : rgba(110, 87, 51, 180);"
                                    "border-width : 1px;"
                                    "gridline-color: rgba(110, 87, 51, 180);"
                                    "selection-background-color: rgba(110, 87, 51, 150);"
                                    "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));}"
                        "QTableView QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                    "stop:0 rgba(110, 87, 51, 200), stop: 0.5 rgba(110, 87, 51, 160), stop:1 rgba(110, 87, 51, 120));"
                                    "color: white;"
                                    "padding-left: 4px;"
                                    "border: 1px solid rgba(110, 87, 51, 200);}"
                        "QTableView QTableCornerButton::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                    "stop:0 rgba(110, 87, 51, 200), stop: 0.5 rgba(110, 87, 51, 160), stop:1 rgba(110, 87, 51, 120));"
                                    "border: none;}"
                        "QTextEdit {border: 1.2px solid gray;"
                                    "border-radius: 7px;"
                                    "padding: 0 8px;"
                                    "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));"
                                    "selection-background-color: darkgray;}"
                        "QTabWidget::pane {border-top: 10px solid rgba(110, 87, 51, 200);}"
                        "QListView {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));"
                                    "border: 1px solid rgba(160, 141, 110, 200);"
                                    "border-radius: 7px;}"
                        "QListView::item {border: 1px solid rgba(160, 141, 110, 200);"
                                    "border-radius: 7px;}"
                        "QListView::item:selected:!active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop:0 rgba(160, 141, 110, 200), stop: 1 rgba(240, 240, 240, 240));}"
                        "QListView::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 rgba(160, 141, 110, 100), stop: 1 rgba(160, 141, 110, 200));"
                                    "border: 1px solid rgba(160, 141, 110, 200);"
                                    "border-radius: 7px;}"
                        "QListView::item:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 #FAFBFE, stop: 1 #DCDEF1);"
                                    "border: 1px solid rgba(160, 141, 110, 200);}");
}

MainWindow::~MainWindow()
{
    delete ui;
}


//кнопку "Войти" можно нажать
void MainWindow::OkEnabled()
{
    ui->okButton->setEnabled((ui->lineLogin->hasAcceptableInput()&& ui->linePass->hasAcceptableInput()));
    //qDebug()<<(ui->lineLogin->hasAcceptableInput());//проверка условия сообщениями в дебаге
}


//нажатие на кнопку "Войти"
void MainWindow::on_okButton_clicked()
{
    stringLogin = ui->lineLogin->text();
    stringPass = ui->linePass->text();

    if(DataBase::clickOk(stringLogin,stringPass,&strLogin,&strName,&strPass,&strId))
    {
        qDebug()<<"Login = "<<strLogin<<"\tName = "<<strName<<"\tPass = "<<strPass<<"\tID = "<<strId;
        //QMessageBox::StandardButton input;
        QMessageBox::information(this, tr("Авторизация"),tr("Вы успешно авторизовались!"));
        this->hide();
        Functioins::GetGeometry(*this,x,y);
        emit InvokeMenu(x,y);
    }
    else
    {
        qDebug()<<"Wrong Login or Pass!";
        //QMessageBox::StandardButton input;
        QMessageBox::warning(this, tr("Авторизация"),tr("Неверный логин или пароль!"));
    }
}


//Показать/скрыть пароль
void MainWindow::on_checkBoxPass_toggled(bool checked)
{
    if (checked)
    {
        ui->linePass->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->linePass->setEchoMode(QLineEdit::Password);
    }
}


//гетеры для приват полей
QString MainWindow::GetID()
{
    return strId;
}

QString MainWindow::GetName()
{
    return strName;
}

QString MainWindow::GetLogin()
{
    return strLogin;
}

QString MainWindow::GetPass()
{
    return strPass;
}
//Setters for private fields
void MainWindow::SetId(QString value)
{
    strId=value;
}

void MainWindow::SetLogin(QString value)
{
    strLogin=value;
}

void MainWindow::SetName(QString value)
{
    strName=value;
}

void MainWindow::SetPass(QString value)
{
    strPass=value;
}


//нажатие на кнопку регистрация
void MainWindow::on_RegistraionButton_clicked()
{
    ui->RegistraionButton->setEnabled(false);
    Functioins::GetGeometry(*this,x,y);
    emit InvokeReg(x,y);
}


//событие выхода, которое срабатывает при выходе из программы
void MainWindow::closeEvent(QCloseEvent *event)
{
    Functioins::CloseProgram(*this, event,"Подтверждение выхода","Вы действительно хотите выйти?");
}

//выход по кнопке
void MainWindow::on_quitButton_clicked()
{
    this->close();
}



//слот принимает сигнал и ставит кнопку в нажимаемое положение
void MainWindow::RegButtEnabled()
{
    ui->RegistraionButton->setEnabled(true);
}

void MainWindow::changeUser(int *x, int *y)
{
    this->move(*x,*y);
    Functioins::StartProgram(*this,"Вход",760,489);
    ui->linePass->clear();
    ui->lineLogin->clear();
}


