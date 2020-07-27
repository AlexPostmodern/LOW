#include "choosing.h"
#include "ui_choosing.h"

Choosing::Choosing(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Choosing)
{
    ui->setupUi(this);
    db=new DataBase(this);
    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/Choosing.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

Choosing::~Choosing()
{
    delete ui;
    delete db;
}

void Choosing::OpenChoosing(int *x, int *y)
{

    QString querystr="SELECT name FROM WordGroup WHERE userid="+MainWindow::GetID()+";";
    db->showComboBoxReg(ui->comboBoxChoosing,querystr);
    db->createWG((MainWindow::GetID()));
    this->move(*x,*y);
    //delete x; delete y;
    Functioins::StartProgram(*this,"Выберите набор слов",760,489);
}

void Choosing::on_pushButtonCancel_clicked()
{
    int *x=new int;
    int *y=new int;
    this->hide();
    Functioins::GetGeometry(*this,x,y);
    emit InvokeMenuBack1(x,y);
}


//кнопка Начать!
void Choosing::on_pushButtonBegin_clicked()
{
    QString queryStr;
    queryStr="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
    int *wgID=new int;
    int *count=new int;
    //считываем айди группы, который выбран в комбобоксе
    db->valuesFromComboBoxReturn(ui->comboBoxChoosing,queryStr, *wgID);
    //считаем количество слов в наборе
    db->countOfWords(wgID,count);
    //если 0 или не выбран никакой набор выдаем ошибку
    if((*count==0&&!ui->checkBoxChoosing->isChecked())||(!ui->checkBoxChoosing->isChecked()&&ui->comboBoxChoosing->currentIndex()==-1))
    {
        reply = QMessageBox::warning(this,"Ошибка","В этом наборе нет слов");
    }
    else
    {
        int *x=new int;
        int *y=new int;
        Functioins::GetGeometry(*this,x,y);
        if (!(ui->checkBoxChoosing->isChecked()))
        {
            queryStr="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
            db->valuesFromComboBoxReturn(ui->comboBoxChoosing,queryStr, *wgID);
            qDebug()<<"id = "<<*wgID;
            emit InvokeTest(wgID,x,y);
        }
        else
            emit InvokeTestCheck(x,y);
        delete count;
        this->hide();
    }
}

