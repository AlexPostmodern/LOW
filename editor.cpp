#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    //db=new DataBase(this);
    //ненажимаемое положение кнопок
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonAdd2->setEnabled(false);
    //регулярки для лайн едитов
    //первый символ буквы а-яА-Я, потом а-яА-Я, пробел или запятая от 0шт до 98шт, и потом опять буква
    QRegExp expRus("^[а-яА-Я][а-яА-Я\\s,]{0,98}[а-яА-Я]$");
    //QRegExp expRus("^[!\\s][?!.*\\s$][?![?:.*\\s]{2}]");
    QRegExp expEng("^[a-zA-Z][a-zA-Z\\s]{0,98}[a-zA-Z]$");
    //присваиваем полям ввода это ограничение, через валидатор
    ui->lineEditRus->setValidator(new QRegExpValidator(expRus,this));
    ui->lineEditEng->setValidator(new QRegExpValidator(expEng,this));
    //поля ввода передают сигналы изменения текста этому классу в слот с функцией
    connect(ui->lineEditRus,SIGNAL(textChanged(QString)),this,SLOT(pushButtonAddEnabled()));
    connect(ui->lineEditEng,SIGNAL(textChanged(QString)),this,SLOT(pushButtonAddEnabled()));
    connect(ui->lineEditEng, SIGNAL(returnPressed()), this, SLOT(on_pushButtonAdd_clicked())); 
    connect(ui->textEditRusEng,SIGNAL(textChanged()),this,SLOT(pushButtonadd2Enabled()));
    connect(ui->lineEditSearch, SIGNAL(returnPressed()), this, SLOT(on_buttonOkEditor_clicked()));
    ui->pushButtonAddGroup->setEnabled(false);
    QRegExp expEngRus("^[а-яА-Яa-zA-Z1-9][а-яА-Яa-zA-Z1-9\\s,]{0,98}[а-яА-Яa-zA-Z1-9]$");
    ui->lineEditAddGroup->setValidator(new QRegExpValidator(expEngRus,this));
    connect(ui->lineEditAddGroup,SIGNAL(textChanged(QString)),this,SLOT(pushButtonAddGroupEnabled()));
    //нажатие добавить группу по ентер
    connect(ui->lineEditAddGroup, SIGNAL(returnPressed()), this, SLOT(on_pushButtonAddGroup_clicked()));

    //фон окна
    QPalette Pal(palette());
    QImage bgEnterWindow(":/background/Editor.jpg");
    Pal.setBrush(QPalette::Background, bgEnterWindow);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    //цвет текста лейблов
    /*QString strColor="color: rgb(110, 87, 51)";
    ui->label->setStyleSheet(strColor);
    ui->label_2->setStyleSheet(strColor);
    ui->label_3->setStyleSheet(strColor);
    ui->label_4->setStyleSheet(strColor);
    ui->label_5->setStyleSheet(strColor);
    ui->label_6->setStyleSheet(strColor);
    ui->label_7->setStyleSheet(strColor);
    ui->label_8->setStyleSheet(strColor);
    ui->label_9->setStyleSheet(strColor);
    ui->label_10->setStyleSheet(strColor);
    ui->label_11->setStyleSheet(strColor);
    ui->label_12->setStyleSheet(strColor);
    ui->labelHeaderWord->setStyleSheet(strColor);
    ui->labelHeaderGroup->setStyleSheet(strColor);
    //цвет текста чекбоксов
    //ui->checkBox->setStyleSheet("QCheckBox { color: rgb(110, 87, 51) }");
    //ui->checkBoxDel->setStyleSheet("QCheckBox { color: rgb(110, 87, 51) }");*/
    //стиль кнопок
    this->setStyleSheet("QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 230), stop:1 rgba(160, 141, 110, 150));}"
                        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(160, 141, 110, 200), stop:1 rgba(240, 240, 240, 230));}"
                        "QPushButton:pressed{background-color: rgba(110, 87, 51, 160);}"
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
                        "QTabWidget::pane {border-top: 1px solid rgba(110, 87, 51, 200);"
                                    "border-left: 1.4px solid rgba(110, 87, 51, 200);"
                                    "border-right: 1.4px solid rgba(110, 87, 51, 200);"
                                    "border-bottom: 1.4px solid rgba(110, 87, 51, 200);}"
                        "QTabBar::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 rgba(240, 240, 240, 240),stop: 0.5 rgba(230, 224, 215, 240), stop: 1.0 rgba(110, 87, 51, 150));"
                                    "border: 1px solid rgba(110, 87, 51, 200);"
                                    "border-bottom-color: rgba(110, 87, 51, 200);"
                                    "border-top-left-radius: 4px;"
                                    "border-top-right-radius: 4px;"
                                    "min-width: 8ex;"
                                    "padding: 2px;}"
                        "QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 rgba(240, 240, 240, 240), stop: 0.5 rgba(230, 224, 215, 240), stop: 1.0 rgba(230, 224, 215, 255));"
                                    "border-bottom-color:rgba(230, 224, 215, 255);"
                                    "margin-top: 2px;}"
                        "QTabBar::tab:!selected {margin-top: 5px;}");
}

Editor::~Editor()
{
    delete ui;
}

//задание параметров виджетов при откытии окна
void Editor::OpeningEditor(int *x, int *y)
{
    //функция открытия окна
    db=new DataBase(this);
    //создаем строку с запросом
    queryString1="SELECT name FROM WordGroup WHERE userid="+MainWindow::GetID();
    //передаем комбобоксы и строки с запросами, чтобы отобразить значения в комбобоксах
    db->showComboBoxReg(ui->comboBox,queryString1);
    db->showComboBoxReg(ui->comboBoxTab2,queryString1);
    db->showComboBoxReg(ui->comboBoxDel,queryString1);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBoxTab2->setCurrentIndex(0);
    ui->comboBoxDel->setCurrentIndex(0);
    //надпись с именем
    ui->labelHeaderGroup->setText(MainWindow::GetName()+", выберите набор слов");
    this->move(*x,*y);
    //delete x; delete y;
    Functioins::StartProgram(*this,"Редактор слов");
}


//делает выборку на первом табе слов из наборов и поиск слов
void Editor::on_buttonOkEditor_clicked()
{
    if (!(ui->checkBox->isChecked()))
    {
        //создаем строку с запросом
        queryString2="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
        //передаем комбобокс и строку с запросом
        db->valuesFromComboBoxTab1(ui->comboBox,queryString2);
        //показывает слова в таблице
        db->showWordsTab1(ui->tableWords, ui->lineEditSearch->text());
        ui->tableWords->setColumnHidden(0,false);
        //делаем по центру колонки в таблице
        ui->tableWords->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableWords->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableWords->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    else
    {
        str1=MainWindow::GetID();
        db->showWordsTab1ifCheckBoxIsCheck(str1, ui->tableWords, ui->lineEditSearch->text());
        ui->tableWords->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->tableWords->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableWords->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->tableWords->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}


//добавление слов по нажатию кнопки добавить по одному слову
void Editor::on_pushButtonAdd_clicked()
{
    //тоже самое что и сверху, передаем параметры фукции, и функция с ними работает
    queryString3="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
    db->valuesFromComboBox(ui->comboBoxTab2,queryString3);
    db->insertWordsToDB(ui->lineEditRus,ui->lineEditEng);
    reply = QMessageBox::information(this,"Добавлене слов","Слова успешно добавлены!\n"+
                                     ui->lineEditRus->text()+" - "+ui->lineEditEng->text());
    //после добавления очищаются лайны
    ui->lineEditRus->clear();
    ui->lineEditEng->clear();
    //задается фокус первому лайну
    ui->lineEditRus->setFocus();
}


//нажимаемое положение кнопки в "добавить набор"
void Editor::pushButtonAddEnabled()
{
    ui->pushButtonAdd->setEnabled(ui->lineEditRus->hasAcceptableInput() && ui->lineEditEng->hasAcceptableInput());
}

void Editor::pushButtonadd2Enabled()
{
    if (!ui->textEditRusEng->toPlainText().isEmpty())
    {
        ui->pushButtonAdd2->setEnabled(true);
    }
    else
    {
        ui->pushButtonAdd2->setEnabled(false);
    }
}

void Editor::pushButtonAddGroupEnabled()
{
    ui->pushButtonAddGroup->setEnabled(ui->lineEditAddGroup->hasAcceptableInput());
}




//добавление нескольких слов по кнопке как в инструкции

void Editor::on_pushButtonAdd2_clicked()
{
    text=ui->textEditRusEng->toPlainText();
    bool space=true;
    int count=0;
    //цикл обрабатывает строку как массив чаров и записывает в две стринговые переменные
    //и передает в функцию в класс database и так по кругу
    //вобщем, если я забуду как это работает, то просто нужно вникнуть, тут все легко, не хочется расписывать
    qDebug()<<"text.size() ="<<text.size();
    db->db_Transaction("open");
    for (int i=0;i<=text.size();)
    {
        if (i==0&&text[i]==" ")
        {
            i++;
            count++;
            continue;
        }
        if (text[i]==" "&&text[i+1]==" ")
        {
            i++;
            count++;
            continue;
        }
        if (text[i]==" "&&text[i-1]=="\n")
        {
            i++;
            count++;
            continue;
        }
        if (text[i]==" "&&text[i-1]=="/")
        {
            i++;
            count++;
            continue;
        }
        if (text[i]==" "&&text[i+1]=="/")
        {
            i++;
            count++;
            continue;
        }
        if (text[i]==" "&&text[i+1]=="\n")
        {
            i++;
            count++;
            continue;
        }
        if (i==(text.size()-1)&&text[i]==" ")
        {
            i++;
            count=i;
            continue;
        }
        if (text[i]=="\n"||text.size()==i)//если элемент массива \n-конец строки
        {
            queryString4="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
            db->valuesFromComboBox(ui->comboBoxTab2,queryString4);
            db->textEditAdd(stringArrRus,stringArrEng);
            qDebug()<<stringArrRus<<stringArrEng;
            stringArrRus=stringArrEng="";
            i++;
            count=i;
            space=true;
            continue;
        }
        if (space&&!(text[i]=="/"))//если элемент массива не /
        {
            stringArrRus[i-count]=text[i];
            i++;
            continue;
        }
        if (text[i]=="/")//если элемент массива /
        {
            space=false;
            i++;
            count=i;
            continue;
        }
        if (!space)
        {
            stringArrEng[i-count]=text[i];
            i++;
            continue;
        }
    }
    db->db_Transaction("commit");
    reply = QMessageBox::information(this,"Добавлене слов","Слова успешно добавлены!");
    ui->textEditRusEng->clear();
}



//ЭКСПЕРИMЕНТ

/*добавление нескольких слов по кнопке
man [мэн] - мужчина
woman [уУмэн] – женщина
child [чайлд] - ребенок
boy [бой] - мальчик
girl [гё:рл] - девочка
guy [гай] - парень
friend [фрэнд] - друг
acquaintance [экуЭйнтэнс] - знакомый; знакомство
neighbor [нЭйбэр] - сосед
guest [гэст] - гость
chief [чи:ф] - начальник; шеф; главный; вождь
boss [бос] - босс
competitor [кэмпЭтитэр] - конкурент, соперник
client [клАйэнт] - клиент
colleague [кОли:г] - коллега

void Editor::on_pushButtonAdd2_clicked()
{
    text=ui->textEditRusEng->toPlainText();
    bool space=true,again=false,con=false;
    int count=0;
    const int engAl=26;
    QString arrEng[engAl],str;
    arrEng[0]="a";arrEng[1]="b";arrEng[2]="c";arrEng[3]="d";arrEng[4]="e";arrEng[5]="f";arrEng[6]="g";arrEng[7]="h";
    arrEng[8]="i";arrEng[9]="j";arrEng[10]="k";arrEng[11]="l";arrEng[12]="m";arrEng[13]="n";arrEng[14]="o";arrEng[15]="p";
    arrEng[16]="q";arrEng[17]="r";arrEng[18]="s";arrEng[19]="t";arrEng[20]="u";arrEng[21]="v";arrEng[22]="w";arrEng[23]="x";
    arrEng[24]="y";arrEng[25]="z";
    qDebug()<<"text.size() ="<<text.size();
    for (int i=0;i<=text.size();)
    {
        if (text[i]==" "&&text[i+1]=="[")
        {
            i++;
            count++;
            space=false;
            continue;
        }
        if (!space&&!again)
        {

            if (text[i]=="-"||text[i]=="–")
            {
                i=i+2;
                count=i;
                again=true;
                continue;
            }
            i++;
            continue;
        }
        if (i==text.size())
        {
            queryString4="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
            db->valuesFromComboBox(ui->comboBoxTab2,queryString4);
            db->textEditAdd(stringArrRus,stringArrEng);
            qDebug()<<stringArrRus<<stringArrEng;
            stringArrRus=stringArrEng="";
            i++;
            count=i;
            space=true;
            again=false;
            continue;
        }
        if ((text[i]==" "&&again))
        {
            con=false;
            for (int j=0;j<engAl;j++)
            {
                str=arrEng[j];
                if (text[i+1]==str)
                {
                    con=true;
                    break;
                }
            }
            if (con)
            {
                queryString4="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
                db->valuesFromComboBox(ui->comboBoxTab2,queryString4);
                db->textEditAdd(stringArrRus,stringArrEng);
                qDebug()<<stringArrRus<<stringArrEng;
                stringArrRus=stringArrEng="";
                i++;
                count=i;
                space=true;
                again=false;
                continue;
            }
            else
            {
                stringArrRus[i-count]=text[i];
                i++;
                continue;
            }
        }
        if ((space&&!(text[i]=="["))||(space&&!((text[i]=="-"||text[i]=="–"))&&!(text[i+1]==" ")))
        {
            stringArrEng[i-count]=text[i];
            i++;
            continue;
        }
        if (again || (!(text[i+1]==" ")&&(text[i]=="-"||text[i]=="–")))
        {
            stringArrRus[i-count]=text[i];
            i++;
            continue;
        }
    }
    reply = QMessageBox::information(this,"Добавлене слов","Слова успешно добавлены!");
    ui->textEditRusEng->clear();
}
*/

//удалить набор слов
void Editor::on_pushButtonDelGroup_clicked()
{
    queryString5="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID()+";";
    db->valuesFromComboBox(ui->comboBoxDel,queryString5, &queryString8);
    reply = QMessageBox::question(this,"Подтверждение удаления","Вы действительно хотите "
                                  "удалить набор - "+queryString8+"?",QMessageBox::Yes | QMessageBox::No);
    if (reply ==QMessageBox::Yes)
        {
            //QString idDel=MainWindow::GetID();
            db->deleteGroup(ui->tableViewDel);
            //создаем строку с запросом
            queryString9="SELECT name FROM WordGroup WHERE userid="+MainWindow::GetID();
            //передаем комбобоксы и строки с запросами, чтобы отобразить значения в комбобоксах
            db->showComboBoxReg(ui->comboBox,queryString9);
            db->showComboBoxReg(ui->comboBoxTab2,queryString9);
            db->showComboBoxReg(ui->comboBoxDel,queryString9);
            //this->on_pushButtonSearch_clicked();
            //this->on_pushButtonShowAdd_clicked();
            //ui->tableViewDel->
        }
}

//поиск слов для удаления
void Editor::on_pushButtonSearch_clicked()
{
    SearchPressed=true;
    if (!(ui->checkBoxDel->isChecked()))
    {
        queryString6="SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID();
        db->valuesFromComboBoxDel(ui->comboBoxDel,queryString6);
        db->showWordsTabDel(ui->tableViewDel,ui->lineEditDelWord->text());
        //делаем по центру текст в таблице
        ui->tableViewDel->setColumnHidden(0, true);
        ui->tableViewDel->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableViewDel->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->tableViewDel->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    else
    {
        QString strid=MainWindow::GetID();
        db->ifCBIsCheckDel(strid, ui->tableViewDel, ui->lineEditDelWord->text());
        ui->tableViewDel->setColumnHidden(0, true);
        ui->tableViewDel->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->tableViewDel->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->tableViewDel->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        ui->tableViewDel->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}


//покакзать наборы
void Editor::on_pushButtonShowAdd_clicked()
{
    queryString7="SELECT name AS 'Название набора' FROM WordGroup WHERE userid="+MainWindow::GetID();
    db->showAllGroup(ui->tableViewGroup, queryString7);
    //делаем колонки по центру в таблице
    ui->tableViewGroup->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

//нажатие на кнопку назад
void Editor::on_pushButtonBack_clicked()
{
    int *x=new int;
    int *y=new int;
    this->hide();
    Functioins::GetGeometry(*this,x,y);
    emit InvokeMenuBack(x,y);  
    delete db;
    SearchPressed=false;
}

//нажатие на кнопку добавить набор
void Editor::on_pushButtonAddGroup_clicked()
{
    if (ui->lineEditAddGroup->text()=="Words to repeat")
    {
        reply = QMessageBox::warning(this, "Ошибка","Вы не можете добавить набор слов с таким именем"
                                                    "\nПожалуйста придумайте другое название");
        ui->lineEditAddGroup->clear();
    }
    else
    {
        reply = QMessageBox::question(this,"Подтверждение добавления","Вы действительно хотите "
                                      "добавить набор - "+ui->lineEditAddGroup->text()+"?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
            {
                QString strid=MainWindow::GetID();
                if(db->addWordGroup(ui->lineEditAddGroup->text(),strid))
                {
                    ui->lineEditAddGroup->clear();
                    //создаем строку с запросом
                    queryString9="SELECT name FROM WordGroup WHERE userid="+MainWindow::GetID();
                    //передаем комбобоксы и строки с запросами, чтобы отобразить значения в комбобоксах
                    db->showComboBoxReg(ui->comboBox,queryString9);
                    db->showComboBoxReg(ui->comboBoxTab2,queryString9);
                    db->showComboBoxReg(ui->comboBoxDel,queryString9);
                }
                else
                {
                    ui->lineEditAddGroup->clear();
                    reply = QMessageBox::warning(this, "Ошибка","Набор с таким именем уже существует"
                                                                "\nПожалуйста придумайте другое название");
                }
            }
    }
}


//нажатие на кнопку удалить cлово
void Editor::on_pushButtonDelWord_clicked()
{
    QString strDelWord,idDelWord;
    //выделение полной строки
    ui->tableViewDel->setSelectionBehavior(QAbstractItemView::SelectRows);
    if (!SearchPressed)
    {
        QMessageBox::information(this,"Ошибка", "Пожалуйста, нажмите \"Посик\" и выберите слово",QMessageBox::Ok);
        return;
    }
    QModelIndex currentDiscount = ui->tableViewDel->currentIndex();
    idDelWord=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),0),0).toString();
    if (idDelWord=="")
    {
        QMessageBox::information(this,"Ошибка", "Пожалуйста, выберите слово",QMessageBox::Ok);
        return;
    }
    if (!ui->checkBoxDel->isChecked())
    {
        strDelWord=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),1),0).toString()
                +" - "+ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),2),0).toString();
        qDebug() <<idDelWord <<strDelWord;
    }
    if(ui->checkBoxDel->isChecked())
    {
        strDelWord=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),2),0).toString()
                +" - "+ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),3),0).toString();
        qDebug() <<idDelWord <<strDelWord;
    }
    reply = QMessageBox::question(this,"Подтверждение удаления","Вы действительно хотите "
                                  "удалить слова: "+strDelWord+"?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        db->delWord(idDelWord);
        this->on_pushButtonSearch_clicked();
    }
    if (reply == QMessageBox::Yes)
        return;
}

void Editor::on_pushButtonHelp_clicked()
{
    emit InvokeInstruction();
}

//изменить слово и набор
void Editor::on_pushUpdateWG_clicked()
{
    QString strquery("SELECT * FROM WordGroup WHERE userid="+MainWindow::GetID()+";");
    strname=new QString;
    db->valuesFromComboBox(ui->comboBoxDel, strquery, strname);
    emit InvokeUpdateWG(strname);
}

void Editor::ValuesComboBoxAfterUpdate(QString sourceSignal)
{
    if(sourceSignal=="WordGroup")
    {
        QString strquery("SELECT name FROM WordGroup WHERE userid="+MainWindow::GetID()+";");
        db->showComboBoxReg(ui->comboBox,strquery);
        db->showComboBoxReg(ui->comboBoxTab2,strquery);
        db->showComboBoxReg(ui->comboBoxDel,strquery);
        delete strname;
    }
    if(sourceSignal=="Word")
    {
        this->on_pushButtonSearch_clicked();
    }
}

void Editor::on_pushUpdateWord_clicked()
{
    QString strUpdateRus,strUpdateEng,idUpdateWord;
    if (!SearchPressed)
    {
        QMessageBox::information(this,"Ошибка", "Пожалуйста, нажмите \"Посик\" и выберите слово",QMessageBox::Ok);
        return;
    }
    QModelIndex currentDiscount = ui->tableViewDel->currentIndex();
    idUpdateWord=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),0),0).toString();
    if (idUpdateWord=="")
    {
        QMessageBox::information(this,"Ошибка", "Пожалуйста, выберите слово",QMessageBox::Ok);
        return;
    }
    if (!ui->checkBoxDel->isChecked())
    {
        strUpdateRus=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),1),0).toString();
        strUpdateEng=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),2),0).toString();

        qDebug() <<idUpdateWord <<strUpdateRus<<strUpdateEng;
    }
    if(ui->checkBoxDel->isChecked())
    {
        strUpdateRus=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),2),0).toString();
        strUpdateEng=ui->tableViewDel->model()->data(ui->tableViewDel->model()->index(currentDiscount.row(),3),0).toString();
        qDebug() <<idUpdateWord <<strUpdateRus<<strUpdateEng;
    }
    emit InvokeUpdateWord(&idUpdateWord,&strUpdateRus,&strUpdateEng);
}
