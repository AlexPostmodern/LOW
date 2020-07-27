#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    db=new DataBase(this);
    //connect(this, SIGNAL(returnPressed()), this, SLOT(on_pushButtonOk_clicked()));
    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/Result.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    //colot and font of label
    int id = QFontDatabase::addApplicationFont(":/fonts/MISTRAL.TTF"); //путь к шрифту
    QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
    QFont mistral(family);
    mistral.setBold(true);
    mistral.setPointSize(18);
    ui->labelResult->setStyleSheet("color: rgb(110, 87, 51)");
    ui->labelResult->setFont(mistral);
}

Result::~Result()
{
    delete ui;
}

void Result::openResult1(int *x, int *y)
{

    this->move(*x,*y);
    DataBase::showResult1(ui->tableResult, MainWindow::GetID(), ui->labelResult);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pushButtonMore->setVisible(false);
    Functioins::StartProgram(*this,"Результат",760,489);
}

void Result::openResultFromMenu(int *x, int *y)
{

    this->move(*x,*y);
    int countResult;
    ui->labelResult->setText("Результаты");
    db->showResultButton(MainWindow::GetID(), ui->tableResult, &countResult);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableResult->horizontalHeader()->setDefaultSectionSize(90);
    ui->tableResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableResult->setColumnHidden(6,true);
    ui->pushButtonMore->setVisible(true);
    Functioins::StartProgram(*this,"Результат",760,489);
}

void Result::on_pushButtonOk_clicked()
{
    int *x=new int;
    int *y=new int;
    Functioins::GetGeometry(*this,x,y);
    this->hide();
    if (!pressBtn)
        emit closeResult(x,y);
    if (pressBtn)
    {
        pressBtn=false;
        this->openResultFromMenu(x,y);
    }
}

void Result::on_pushButtonMore_clicked()
{
    QString idResult;
    QModelIndex currentDiscount = ui->tableResult->currentIndex();
    idResult=ui->tableResult->model()->data(ui->tableResult->model()->index(currentDiscount.row(),6),0).toString();
    qDebug()<<"idResult ="<<idResult;
    if (idResult=="")
    {
        QMessageBox::information(this,"Ошибка", "Пожалуйста, выберите интересующий вас результат",QMessageBox::Ok);
        return;
    }
    pressBtn=true;
    db->resultMoreButton(idResult, ui->tableResult);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableResult->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->pushButtonMore->setVisible(false);
}
