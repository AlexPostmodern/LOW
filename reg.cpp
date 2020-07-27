#include "reg.h"
#include "ui_reg.h"

Reg::Reg(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Reg)
{
    ui->setupUi(this);
    ui->setupUi(this);
    //ненажимаемое положение кнопки
    ui->okButtonReg->setEnabled(false);
    QRegExp expLogPassReg("[a-zA-Z0-9]{1,25}");
    //присваиваем полям ввода это ограничение, через валидатор
    ui->lineLoginReg->setValidator(new QRegExpValidator(expLogPassReg,this));
    ui->linePassReg_1->setValidator(new QRegExpValidator(expLogPassReg,this));
    ui->linePassReg_2->setValidator(new QRegExpValidator(expLogPassReg,this));
    //поля ввода передают сигналы изменения текста этому классу в слот с функцией
    connect(ui->lineLoginReg,SIGNAL(textChanged(QString)),this,SLOT(OkEnabledReg()));
    connect(ui->linePassReg_1,SIGNAL(textChanged(QString)),this,SLOT(OkEnabledReg()));
    connect(ui->linePassReg_2,SIGNAL(textChanged(QString)),this,SLOT(OkEnabledReg()));
    QRegExp expName("^[а-яА-Яa-zA-Z0-9][а-яА-Яa-zA-Z0-9\\s]{0,25}[а-яА-Яa-zA-Z0-9]$");
    ui->lineNameReg->setValidator(new QRegExpValidator(expName,this));
    connect(ui->lineNameReg,SIGNAL(textChanged(QString)),this,SLOT(OkEnabledReg()));
    //чтобы кнопка войти нажималась на ентер и чтобы кнопка горела нужно установить default галочку в ui
    connect(ui->lineNameReg, SIGNAL(returnPressed()), this, SLOT(on_okButtonReg_clicked()));
    //cигнал нажатия на кнопку "ок"
    connect(ui->okButtonReg,SIGNAL(clicked()),this,SLOT(on_okButtonReg_clicked()));
    //cигнал нажатия на кнопку "назад"
    connect(ui->BackButtonReg,SIGNAL(clicked()),this,SLOT(on_BackButtonReg_clicked()));
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    connect(ui->lineLoginReg,SIGNAL(textChanged(QString)),this,SLOT(on_lineLoginReg_textChanged()));
    connect(ui->linePassReg_1,SIGNAL(textChanged(QString)),this,SLOT(on_linePassReg_1_textChanged()));
    connect(ui->linePassReg_2,SIGNAL(textChanged(QString)),this,SLOT(on_linePassReg_2_textChanged()));
    connect(ui->lineNameReg,SIGNAL(textChanged(QString)),this,SLOT(on_lineNameReg_textChanged()));
    //дизайн

    //фон окна
    QPalette Pal(palette());
    //QImage background2("qrc:/Instruction/EnterWindow(1).jpg");
    QImage background2(":/background/RegWindow.jpg");
    Pal.setBrush(QPalette::Background, background2);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

Reg::~Reg()
{
    delete ui;
}

//открытие этого окна
void Reg::OpeningReg(int *x, int *y)
{
    qDebug()<<"Signal in Reg is received!";
    Functioins::StartProgram(*this,"Регистрация",760,489);
    db=new DataBase(this);
    this->move(*x,*y);
}


//эта функция принимает сигнал и устанавливает кнопку в положение нажимаемое
//hasAcceptableInput() - возвращает тру, если ограничение которое мы установили выполнено
//тем самым булевое знчение setEnabled возвращает тру, если оба лайна соответствуют ограничению
void Reg::OkEnabledReg()
{
    ui->okButtonReg->setEnabled(ui->lineLoginReg->hasAcceptableInput()&& ui->linePassReg_1->hasAcceptableInput()
                                && ui->lineNameReg->hasAcceptableInput()
                                && ui->linePassReg_2->text()==ui->linePassReg_1->text());
    if (!(ui->linePassReg_1->text()==ui->linePassReg_2->text())&&!(ui->linePassReg_2->text()==""))
    {
        ui->linePassReg_1->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(240,128,128,255), stop:1 rgba(220,68,68,255));"
                                        "selection-background-color: darkgray;");
        ui->linePassReg_2->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(240,128,128,255), stop:1 rgba(220,68,68,255));"
                                        "selection-background-color: darkgray;");
    }
    else if(!(ui->linePassReg_2->text()==""))
    {
        ui->linePassReg_1->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(203,235,203,255), stop:1 rgba(55,176,55,255));"
                                        "selection-background-color: darkgray;");
        ui->linePassReg_2->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(203,235,203,255), stop:1 rgba(55,176,55,255));"
                                        "selection-background-color: darkgray;");
    }
    if (ui->linePassReg_1->text()=="")
    {
        ui->linePassReg_1->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));"
                                        "selection-background-color: darkgray;");
        ui->linePassReg_2->setStyleSheet("border: 1.2px solid gray;"
                                        "border-radius: 7px;"
                                        "padding: 0 8px;"
                                        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                        "stop:0 rgba(240, 240, 240, 240), stop:1 rgba(230, 224, 215, 240));"
                                        "selection-background-color: darkgray;");
    }
}



//нажатие ок в окне регистрация
void Reg::on_okButtonReg_clicked()
{
    qDebug()<<"Button OK was pressed!";
    if (DataBase::clickOkReg(QVariant(ui->lineLoginReg->text()).toString(),
                         QVariant(ui->linePassReg_2->text()).toString(),
                         QVariant(ui->lineNameReg->text()).toString()))
    {

        //создаются базовые наборы слов для каждого нового пользователя
        /*time = QTime(0,0,0);
        timer2 = new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(Timer2()));
        timer2->start(1000);*/
        db->standartWG();
        //timer2->stop();
        //qDebug()<<"TIME ="<<time.toString("HH:mm:ss");
        QMessageBox::information(this, tr("Регистрация"),tr("Вы успешно зарегистрировались!"));
        //окно с регистрацией закроется
        this->hide();
    }
    else
    {
        QMessageBox::warning(this, tr("Регистрация"),tr("Такой логин уже существует!"));
    }
}


/*void Reg::Timer2()
{
    time = time.addSecs(1);
    qDebug()<<"TIME in Timer ="<<time.toString("HH:mm:ss");
}*/

//событие выхода, которое срабатывает при выходе из программы
void Reg::closeEvent(QCloseEvent *event)
{
    if(Functioins::CloseProgram(*this, event,"Подтверждение выхода","Вы действительно хотите прервать регистрацию?"))
        emit SetEnabledReg();
}

//выход по кнопке
void Reg::on_BackButtonReg_clicked()
{
    this->close();
}

void Reg::on_lineLoginReg_textChanged()
{
    ui->label->setVisible(true);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
}

void Reg::on_linePassReg_1_textChanged()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
}

void Reg::on_linePassReg_2_textChanged()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(false);
}

void Reg::on_lineNameReg_textChanged()
{
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(true);
}
