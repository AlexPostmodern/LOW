#include "update.h"
#include "ui_update.h"

Update::Update(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Update)
{
    ui->setupUi(this);
    db=new DataBase(this);
}

Update::~Update()
{
    delete ui;
}

//выход
void Update::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void Update::openUpdateWG(QString *name)
{
    ui->label->setText("Старое название\n"+*name);
    nameWG=*name;
    ui->lineEdit->setText(nameWG);
    ui->lineEditRus->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setText("Новое название");
    Functioins::StartProgram(*this,"Изменение набора слов",450,125);
    sourceSignal="WordGroup";
}

void Update::openUpdateWord(QString *idWord, QString *strWordRus, QString *strWordEng)
{
    ui->label->setText("Старое слово\n"+*strWordRus+" - "+*strWordEng);
    ui->lineEditRus->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setText("На английском");
    ui->lineEditRus->setText(*strWordRus);
    ui->lineEdit->setText(*strWordEng);
    Functioins::StartProgram(*this,"Изменение слова",500,175);
    this->idWord=*idWord;
    this->strWordRus=*strWordRus;
    this->strWordEng=*strWordEng;
    sourceSignal="Word";
}

//выход по кнопке
void Update::on_pushButton_2_clicked()
{
    qDebug()<<"Exit";
    this->hide();
}

void Update::on_pushButton_clicked()
{
    if(sourceSignal=="WordGroup")
    {
        reply = QMessageBox::question(this,"Подтверждение изменения","Вы действительно хотите "
                                      "\nизменить название набора слов \n"
                                      "c \""+nameWG+"\" на \""+ui->lineEdit->text()+"\"?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            db->updateWG(ui->lineEdit->text(),MainWindow::GetID(),nameWG);
            emit InvokeEditorFromUpdate(sourceSignal);
            this->hide();
        }
    }
    if(sourceSignal=="Word")
    {
        reply = QMessageBox::question(this,"Подтверждение изменения","Вы действительно хотите "
                                      "изменить слово\n"
                                      "c \""+strWordRus+" - "+strWordEng+"\"\n"
                                      "на \""+ui->lineEditRus->text()+" - "+ui->lineEdit->text()+"\"?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            db->updateWord(ui->lineEditRus->text(),ui->lineEdit->text(),idWord);
            emit InvokeEditorFromUpdate(sourceSignal);
            this->hide();
        }
    }
}
