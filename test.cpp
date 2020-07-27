#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    //db=new DataBase(this);
    /*QTime time = QTime::currentTime();
    qsrand(time.msec());*/
    check=0;
    QRegExp expAnswer("^[a-zA-Z][a-zA-Z\\-\\s]{0,98}[a-zA-Z]$");
    ui->pushButtonAnswer->setEnabled(false);
    //присваиваем полям ввода это ограничение, через валидатор
    ui->lineEditTest->setValidator(new QRegExpValidator(expAnswer,this));
    connect(ui->lineEditTest, SIGNAL(returnPressed()), this, SLOT(on_pushButtonAnswer_clicked()));
    connect(ui->lineEditTest,SIGNAL(textChanged(QString)),this,SLOT(answerEnabled()));
    x=new int;
    y=new int;

    //дизайн

    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/Test.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    //progressbar
    ui->progressBar->setStyleSheet("QProgressBar"
                                   "{"
                                       "border: 1px solid transparent;text-align: center;"
                                       "color:rgba(0,0,0,255);"
                                       "border-radius: 5px;"
                                       "border-width: 3px;"
                                       "border-image: 9,2,5,2; "
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                       "stop:0 rgba(240, 240, 240, 255), stop:1 rgba(110, 87, 51, 120));"
                                   "}"
                                       "QProgressBar::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                                       "stop: 0 rgba(110, 87, 51,200), stop: 1 rgba(255,255,255,200));}");
    //labels
    ui->labelTimer->setStyleSheet("QLabel { color: rgb(110, 87, 51) }");
    ui->labelProgress->setStyleSheet("QLabel { color: rgb(110, 87, 51) }");
}

Test::~Test()
{
    delete ui;
}


void Test::closeEvent(QCloseEvent *event)
{
    Functioins::CloseProgram(*this, event,"Подтверждение выхода","Результаты теста не сохранятся!\n"
                                                                 "Вы действительно хотите выйти?");
}


void Test::answerEnabled()
{
    ui->pushButtonAnswer->setEnabled(ui->lineEditTest->hasAcceptableInput());
}


//функция открытия и таймер
void Test::OpenTest(int*x, int*y)
{
    db=new DataBase(this);  
    time = QTime(0,0,0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timer()));
    timer->start(1000);
    this->move(*x,*y);
    ui->pushAnswerLater->setEnabled(true);
    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);
    Functioins::StartProgram(*this,"Тестирование",760,489);
}

//обновление таймера каждую секунду в лейбле
void Test::Timer()
{
    time = time.addSecs(1);
    ui->labelTimer->setText("Времени прошло "+time.toString("hh:mm:ss"));
    if (time.toString("hh:mm:ss")=="00:30:00")
    {
        timer->stop();
        qDebug()<<"time ="<<time.toString("hh:mm:ss");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,"Перерыв", "Пора сделать перерыв!\n"
                                         "Чтобы продолжить нажмите ОК",QMessageBox::Ok);
        if (reply ==QMessageBox::Ok)
        {
            timer->start();
        }
    }
}

//открытие программы, если выбран какой то набор
void Test::fillArr(int *wgID, int*x, int*y)
{
    Test::OpenTest(x,y);
    delete x; delete y;
    OnePack=true;
    QString regID=MainWindow::GetID();
    //проверка того, что получили по сигналу
    qDebug()<<"fillArr wgID = "<<*wgID;
    //строка для выведения слов на экран
    QString labelstr;
    //узнаю размер массива
    db->testReceiveSize(wgID, &size);
    qDebug()<<"size = "<<size;
    ui->progressBar->setMaximum(size);
    /*генерирую случайный индекс в интервале от 0 до размера массива,
    этот случайный индекс, позже буде
    хранить в себе айди первого случайного слова*/
    firstWordID=rand()%size;
    qDebug()<<"Random index = "<<firstWordID;
    //заполняется строка для лейбла
    db->fillArrs(&labelstr,size,wgID,firstWordID);
    qDebug()<<"labelstr = "<<labelstr;
    ui->label->setText(labelstr);
    wordGroupID=*wgID;
    delete wgID;
    qDebug()<<"wordGroupID="<<wordGroupID<<"size ="<<size<<"firstWordID ="<<firstWordID;
    qDebug()<<"check ="<<check;
    arrRandomId=new int[size];
    arrResult=new int[size];
    arrAnswerBool=new int[size];
    int *arrId=new int[size];
    int *arr0or1=new int[size];
    int *arrRandomIndex=new int[size];
    db->fillArrID(arrId,arr0or1,size,wordGroupID,arrResult);
    qDebug()<<"arr0or1 ="<<arr0or1[0]<<arr0or1[1]<<arr0or1[2]<<arr0or1[3];
    qDebug()<<"arrId ="<<arrId[0]<<arrId[1]<<arrId[2]<<arrId[3];
    int *a=new int;
    int *b=new int;
    for (int i=0; i<size;)
    {
        *a=rand()%size;
        if(arr0or1[*a]==0)
        {
            arr0or1[*a]=1;
            arrRandomIndex[i]=*a;
            i++;
        }
    }
    qDebug()<<"arrRandomIndex ="<<arrRandomIndex[0]<<arrRandomIndex[1]<<arrRandomIndex[2]<<arrRandomIndex[3];
    for (int i=0; i<size;i++)
    {
        *b=arrRandomIndex[i];
        if(*b==firstWordID)
        {
            arrRandomIndex[i]=arrRandomIndex[0];
            arrRandomIndex[0]=firstWordID;
            break;
        }
    }
    qDebug()<<"arrRandomIndex after change ="<<arrRandomIndex[0]<<arrRandomIndex[1]<<arrRandomIndex[2]<<arrRandomIndex[3];
    for (int i=0; i<size;i++)
    {
        arrRandomId[i]=arrId[arrRandomIndex[i]];
        arrAnswerBool[i]=0;
    }
    qDebug()<<"arrRandomId ="<<arrRandomId[0]<<arrRandomId[1]<<arrRandomId[2]<<arrRandomId[3];
    delete a; delete b; delete [] arrRandomIndex; delete [] arrId; delete [] arr0or1;
}

//открытие программы если выбраны все наборы
void Test::fillArrCheck( int*x, int*y)
{
    OnePack=false;
    Test::OpenTest(x,y);
    delete x; delete y;
    //размер массива со словами из всех наборов
    size=0;
    //узнаю размер массивов
    db->testReceiveSizeCheck(&size, MainWindow::GetID());
    qDebug()<<"size = "<<size;
    ui->progressBar->setMaximum(size);
    //строка для выведения слов на экран
    QString labelstr;
    /*генерирую случайный индекс в интервале от 0 до размера массива,
    этот случайный индекс, позже будет хранить в себе айди первого случайного слова*/
    int firstWordIndex;
    firstWordIndex=rand()%size;
    qDebug()<<"Random index = "<<firstWordIndex;
    //создаю массив для айди всех слов в случайном порядке
    arrRandomId=new int[size];
    arrResult=new int[size];
    arrAnswerBool=new int[size];
    //создаю массив с айди всех слов в обычном порядке
    int *arrId=new int[size];
    /*создаю массив с нулями, для заполнения массива индексов в случайном порядке
    когда берется индекс из массива с айди, вместо 0 пишется 1*/
    int *arr0or1=new int[size];
    //массив с случайными индексами
    int *arrRandomIndex=new int[size];
    //заполняю массив с айди, с нулями и массив для результатов единицами
    db->fillArrIDCheck(arrId,arr0or1,size,arrResult);
    int a;
    //заполняю массив случайными индексами
    for (int i=0; i<size;)
    {
        a=rand()%size;
        if(arr0or1[a]==0)
        {
            arr0or1[a]=1;
            arrRandomIndex[i]=a;
            i++;
        }
    }
    //вывод массива с индексами
    QString *strarrRandomIndex = new QString;
    *strarrRandomIndex="";
    for(int i=0;i<size;i++)
    {
        *strarrRandomIndex=*strarrRandomIndex+QString::number(arrRandomIndex[i])+" ";
    }
    qDebug()<<"arrRandomIndex = "<<*strarrRandomIndex;
    //замена индекса первого слова с индексом другого
    int b;
    for (int i=0; i<size;i++)
    {
        b=arrRandomIndex[i];
        if(b==firstWordIndex)
        {
            arrRandomIndex[i]=arrRandomIndex[0];
            arrRandomIndex[0]=firstWordIndex;
            break;
        }
    }
    //заполнение массива случайными айди       //создание массива, который отслеживает отвечено ли или нет
    for (int i=0; i<size;i++)
    {
        arrRandomId[i]=arrId[arrRandomIndex[i]];
        arrAnswerBool[i]=0;         //изначально массив состоит из фолс, потому что ни одного ответа не дано
    }
    //вывод полученных массивов
    QString *strarrId=new QString;
    QString *strarr0or1=new QString;
    QString *strarrResult=new QString;
    QString *strarrRandomId = new QString;
    *strarrId=*strarr0or1=*strarrResult=*strarrRandomIndex=*strarrRandomId="";
    for(int i=0;i<size;i++)
    {
        *strarrId=*strarrId+QString::number(arrId[i])+" ";
        *strarr0or1=*strarr0or1+QString::number(arr0or1[i])+" ";
        *strarrResult=*strarrResult+QString::number(arrResult[i])+" ";
        *strarrRandomIndex=*strarrRandomIndex+QString::number(arrRandomIndex[i])+" ";
        *strarrRandomId=*strarrRandomId+QString::number(arrRandomId[i])+" ";
    }
    //присваеваем айди первого слова
    firstWordID=arrRandomId[0];
    qDebug()<<"arrId = "<<*strarrId<<"\narr0or1 = "<<*strarr0or1<<"\narrResult = "<<*strarrResult
           <<"\narrRandomIndex after change = "<<*strarrRandomIndex<<"\narrRandomId = "<<*strarrRandomId
          <<"\nfirstWordID = "<<firstWordID;
    db->firstWordToLabel(firstWordID, ui->label);
    delete strarrId; delete strarr0or1; delete strarrResult; delete strarrRandomIndex; delete strarrRandomId;
}

/*void Test::on_pushButtonAnswer_clicked()
{
    if (check==size-1)
    {
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check);
        if (check==size-1)
            return;
        if(countAnswerLater==0)
        {
            this->endOfTest();
        }
        if(countAnswerLater>0)
        {
            for (int i=0;i<size;i++)
            {
                intWork=arrAnswerLater[i];
                if(!(intWork==0))
                {
                    arrAnswerLater0[count_i]=intWork;
                    count_i++;
                }
            }
            delete[] arrAnswerLater;
            qDebug()<<arrAnswerLater0[0]<<arrAnswerLater0[1];
            count_i=0;
            check=arrAnswerLater0[count_i];
            count_i++;
            db->testDB(this, ui->label, ui->lineEditTest, arrAnswerLater0, &check);
        }
    }

    else
    {
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check);
        qDebug()<<"check ="<<check;
    }
}*/



/*void Test::on_pushButtonAnswer_clicked()
{
    if (execute)
    {
       db->testDB(this, ui->label, ui->lineEditTest, arrAnswerLater0, &check);
    }
    if (check==size-1 && (!execute))
    {
        execute=true;
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check);
        if (check==size-1)
            return;
        if(countAnswerLater==0)
        {
            this->endOfTest();
        }
        if(countAnswerLater>0)
        {
            arrAnswerLater0=new int[countAnswerLater];
            for (int i=0;i<countAnswerLater;i++)
            {
                intWork=arrAnswerLater[i];
                arrAnswerLater0[i]=intWork;
            }
            delete[] arrAnswerLater;
            qDebug()<<arrAnswerLater0[0]<<arrAnswerLater0[1];
            check=0;
            db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check);
        }
    }
    if (check==countAnswerLater-1)
    {
        qDebug()<<"ENDDDD";
    }
    else
    {
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check);
        qDebug()<<"check ="<<check;
    }
}*/


void Test::on_pushButtonAnswer_clicked()
{
//когда закончился основной набор и начинаются пропущенные слова
    if(execute)
    {
        db->testDBExecute(this,arrRandomId,arrAnswerBool,ui->lineEditTest,&check,size,
                          ui->labelProgress,ui->progressBar);
        if(arrAnswerBool[check]==0)
            return;
        db->searchLaterWorld(arrRandomId,arrAnswerBool,ui->label,size,&check,&end);
        if (end)
        {
            this->endOfTest();
            return;
        }
        return;
    }
//любое слово кроме последнего слова
    if(!execute&&check<size-1)
    {
        qDebug()<<"check < size-1 ="<<check;
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check, arrAnswerBool,size,
                   ui->labelProgress,ui->progressBar);
        return;
    }
//когда последнее слово в наборе и нет пропущенных слов
    if (check>=size-1&&!pressAnswerLater&&!execute)
    {
        qDebug()<<"check = size-1 ="<<check;
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check, arrAnswerBool,size,
                   ui->labelProgress,ui->progressBar);
        if (check==size-1)
            return;
        this->endOfTest();
        return;
    }
//когда последнее слово в наборе и есть пропущенные слова
    if (check>=size-1&&pressAnswerLater&&!execute)
    {
        db->testDB(this, ui->label, ui->lineEditTest, arrRandomId, &check, arrAnswerBool,size,
                   ui->labelProgress,ui->progressBar);
        if(check==size-1)
            return;
        qDebug()<<"execute=true in Answer clicked";
        execute=true;
        db->searchLaterWorld(arrRandomId,arrAnswerBool,ui->label,size,&check,&end);
        ui->lineEditTest->clear();
        ui->pushAnswerLater->setEnabled(false);
        return;
    }
}

void Test::on_pushAnswerLater_clicked()
{
    pressAnswerLater=true;
    ui->lineEditTest->setFocus();
    //когда пропускается любое слово, кроме последнего
    if (!(check==size-1)&&!execute)
    {
        check++;
        db->answerLater(ui->label,&check,arrRandomId);
        return;
    }
    //когда пропускается последнее слово в наборе
    else
    {
        qDebug()<<"execute=true in AnswerLater clicked";
        execute=true;
        db->searchLaterWorld(arrRandomId,arrAnswerBool,ui->label,size,&check,&end);
        ui->lineEditTest->clear();
        ui->pushAnswerLater->setEnabled(false);
        return;
    }
}

void Test::endOfTest()
{
    qDebug()<<"The END\nПропущенных слов нет\nRight -"<<size-count<<"\nWrong -"<<count;
    qDebug()<<"arrRandomId ="<<arrRandomId[0]<<arrRandomId[1]<<arrRandomId[2]<<arrRandomId[3];
    qDebug()<<"arrResult"<<arrResult[0]<<arrResult[1]<<arrResult[2]<<arrResult[3];
    qDebug()<<"arrAnswerBool ="<<arrAnswerBool[0]<<arrAnswerBool[1]<<arrAnswerBool[2]<<arrAnswerBool[3];
    db->insertResult(arrRandomId,arrResult,count,size,MainWindow::GetID().toInt(),time,OnePack);
    Functioins::GetGeometry(*this,x,y);
    emit showResult1(x,y);
    this->hide();
    delete [] arrResult; delete [] arrRandomId; delete [] arrAnswerBool;
    //приведение переменных к первоначальному виду
    check=0;
    count=0;
    counterProgress=0;
    ui->labelProgress->setText("");
    timer->stop();
    time=QTime(0,0,0);
    ui->lineEditTest->clear();
    execute=false;
    pressAnswerLater=false;
    end=false;
    delete db;
}

void Test::on_pushDontKnow_clicked()
{
    if (!(arrResult[check]==0))
    {
        arrResult[check]=0;
        count++;
    }
    QString *strDontKnow=new QString;
    db->dontKnow(strDontKnow, check, arrRandomId, MainWindow::GetID());
    QMessageBox::information(this,"Подсказка","Возможно, вы захотите повторить : "+*strDontKnow);
    ui->lineEditTest->clear();
    ui->lineEditTest->setFocus();
    delete strDontKnow;
}


void Test::on_pushCancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Подтверждение выхода", "Результаты теста не сохранятся!\n"
                                                          "Вы действительно хотите выйти?",QMessageBox::Yes | QMessageBox::No);
    if (reply ==QMessageBox::Yes)
        {
        this->hide();
        //приведение переменных к первоначальному виду
        delete [] arrResult; delete [] arrRandomId; delete [] arrAnswerBool;
        check=0;
        count=0;
        counterProgress=0;
        ui->labelProgress->setText("");
        timer->stop();
        time=QTime(0,0,0);
        ui->lineEditTest->clear();
        execute=false;
        pressAnswerLater=false;
        end=false;
        delete db;
        Functioins::GetGeometry(*this,x,y);
        emit InvokeChoosing1(x,y);
    }
}


/*void Test::on_pushAnswerLater_clicked()
{
    if (countAnswerLater==0)
    {
        arrAnswerLater=new int[size];
        for (int i=0;i<size;i++)
        {
            arrAnswerLater[i]=0;
        }
        this->answerLater();
    }
    else
    {
        this->answerLater();
    }
}

void Test::answerLater()
{
    countAnswerLater++;
    arrAnswerLater[i_later]=arrRandomId[check];
    i_later++;
    if(!(check==size-1))
    {
        check++;
        qDebug()<<"check answerLater ="<<check;
        db->answerLater(ui->label,&check,arrRandomId);
    }
}*/
