#include "database.h"
QSqlDatabase DataBase::db;
int DataBase::countdb;
int DataBase::sizedb;


DataBase::DataBase(QObject *parent) : QObject(parent)
{
    modelQueryBox = new QSqlQueryModel(this);//
    modelQueryTable1 = new QSqlQueryModel(this);
    modelQueryTable2 = new QSqlQueryModel(this);
    modelQueryTable3 = new QSqlQueryModel(this);
    modelQueryTab1CheckBox = new QSqlQueryModel(this);
    modelQueryDel = new QSqlQueryModel(this); 
    universalModel=new QSqlQueryModel(this);
}
DataBase::~DataBase()
{
    delete modelQueryBox;
    delete universalModel;
    delete modelQueryTable1;
    delete modelQueryTable2;
    delete modelQueryTable3;
    delete modelQueryTab1CheckBox;
    delete modelQueryDel;
}
//cоединение с базой данных
bool DataBase::createConnection()
{

    QString path= QDir::currentPath();
    qDebug()<<path;
    //название дафвера
    db=QSqlDatabase::addDatabase("QSQLITE");
    //указываем имя(в моем случае это адрес для библиотеки)
    db.setDatabaseName(path+"/LOW.db");
    //функция подклюения к бд
    db.open();
    //проверка подключения
    if(!db.open())
    {
        qDebug()<<db.lastError().text();
        return false;
    }
    else
    {
        qDebug()<<"Success!";
    }
    return true;
}


//нажатие на кнопку "Войти" в мэйн виндоу
bool DataBase::clickOk(const QString stringLogin, const QString stringPass,
                          QString *strLogin,QString *strName,QString *strPass,QString *strId)
{
    QSqlQuery queryOkButton = QSqlQuery(db);
    if(!queryOkButton.exec("SELECT * FROM RegUsers"))
    {
        qDebug()<<queryOkButton.lastError().databaseText();
        qDebug()<<queryOkButton.lastError().driverText();
    }
    bool coincidence=false; 
    while(queryOkButton.next())
    {
        qDebug()<<queryOkButton.record();
        *strId = queryOkButton.value(0).toString();
        *strLogin = queryOkButton.value(1).toString();
        *strPass = queryOkButton.value(2).toString();
        *strName = queryOkButton.value(3).toString();
        if (strLogin==stringLogin && strPass==stringPass)
        {
            qDebug()<<"Find it!";
            coincidence=true;
            break;
        }
        else
        {
            qDebug()<<"No coincidence!";
        }
    }
    if  (coincidence)
    {
        queryOkButton.exec("update RegUsers set lastEnter=1 where id="+*strId);
        return true;
    }
    else
        return false;
}


//при нажатии на ОК
bool DataBase::clickOkReg(const QString stringLogin, const QString stringPass_2, const QString stringName)
{
    //создается запрос
    QSqlQuery queryOkRegButton = QSqlQuery(db);
    //если запрос не выполнится, то вывести ошибки в дебаг
    if(!queryOkRegButton.exec("SELECT * FROM RegUsers"))
    {
        qDebug()<<queryOkRegButton.lastError().databaseText();
        qDebug()<<queryOkRegButton.lastError().driverText();
        return false;
    }
    //создаем переменные
    QString *strLogin=new QString;
    bool *coincidence= new bool(true);
    //этот цикл означает что наш запрос пройдет по всем строкам таблицы, до тех пор пока не выдаст фолс, т.е. конец таблицы
    while(queryOkRegButton.next())
    {
        qDebug()<<queryOkRegButton.record();
        //присваиваем переменным значения из таблицы, номер в скобочках это порядок столбца
        *strLogin = queryOkRegButton.value(1).toString();
        //если в таблице есть совпадение логинов то переменная будет фолс и выход и цикла
        if (*strLogin==stringLogin)
        {
            qDebug()<<"Find it!";
            *coincidence=false;
            break;
        }
        else
        {
            qDebug()<<"No coincidence!";
        }
    }   //если совпадений нет то в таблицу запишутся данные из лайн едитов
    if  (*coincidence)
    {
        QSqlQuery *queryInsert = new QSqlQuery(db);
        QString strquery("insert into RegUsers (login,password,name,lastEnter) "
                         "values ('"+stringLogin+"','"+stringPass_2+"','"+stringName+"',0);");
        qDebug()<<strquery;
        queryInsert->exec(strquery);
        delete queryInsert; delete strLogin; delete coincidence;
        return true;
    }
    //если все таки совпадение было то вернет фолс
    else
    {
        return false;
    }
}


//создание стандартных наборов слов
//время выполнения 7 сек, 1000 cтрок 2 минуты
void DataBase::standartWG()
{
    db.transaction();//открываем транзакцию
    qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    QString userId,strquery("select id from RegUsers order by id desc;");
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(strquery);
    while(query->next())
    {
        userId=query->value(0).toString();
        break;
    }
    qDebug()<<"userId ="<<userId;
    const int szWG=26;
    QString arrWG_ID[szWG];
    arrWG_ID[0]="63";arrWG_ID[1]="64";arrWG_ID[2]="65";arrWG_ID[3]="67";arrWG_ID[4]="68";
    arrWG_ID[5]="69";arrWG_ID[6]="70";arrWG_ID[7]="71";arrWG_ID[8]="72";arrWG_ID[9]="74";
    arrWG_ID[10]="75";arrWG_ID[11]="76";arrWG_ID[12]="77";arrWG_ID[13]="78";arrWG_ID[14]="79";
    arrWG_ID[15]="80";arrWG_ID[16]="81";arrWG_ID[17]="82";arrWG_ID[18]="83";
    arrWG_ID[19]="84";arrWG_ID[20]="85";arrWG_ID[21]="86";arrWG_ID[22]="87";arrWG_ID[23]="88";
    arrWG_ID[24]="89";arrWG_ID[25]="90";
    QString *arrWordsRus, *arrWordsEng, nameWG,idWG;
    int szW=0,j;
    for (int i=0;i<szWG;i++)
    {
        j=0;
        strquery="select name from WordGroup where id="+arrWG_ID[i]+";";
        query->exec(strquery);
        while(query->next())
            nameWG=query->value(0).toString();
        strquery="select count(*) from Words where wordid="+arrWG_ID[i]+";";
        query->exec(strquery);
        while(query->next())
            szW=query->value(0).toInt();
        arrWordsRus=new QString[szW];
        arrWordsEng=new QString[szW];
        strquery="select * from Words where wordid="+arrWG_ID[i]+";";
        query->exec(strquery);
        while(query->next()&&j<szW)
        {
            arrWordsRus[j]=query->value(1).toString();
            arrWordsEng[j]=query->value(2).toString();
            j++;
        }
        strquery="INSERT INTO WordGroup (name, userid) VALUES ('"+nameWG+"','"+userId+"');";
        query->exec(strquery);
        strquery="select id from WordGroup order by id desc;";
        query->exec(strquery);
        while(query->next())
        {
            idWG=query->value(0).toString();
            break;
        }
        j=0;
        for (int j=0;j<szW;j++)
        {
            strquery="INSERT INTO Words (russian,english,wordid) VALUES ('"
                    +arrWordsRus[j]+"','"+arrWordsEng[j]+"','"+idWG+"');";
            query->exec(strquery);
        }
        delete [] arrWordsEng; delete [] arrWordsRus;
    }
    db.commit();//подтверждаем транзакцию, время выполнения меньше секунды
    qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    delete query;
}

//изменение названия набора слов и слов
void DataBase::updateWG(QString lineEdit, QString userid, QString nameWG)
{
    QSqlQuery *query=new QSqlQuery(db);
    QString strquery("select id from WordGroup where (userid="+userid+" and "
                     "name='"+nameWG+"');"), id;
    qDebug()<<strquery;
    query->exec(strquery);
    while(query->next())
    {
       id=query->value(0).toString();
    }
    strquery="update WordGroup set name='"+lineEdit+"' where id="+id+";";
    query->exec(strquery);
    qDebug()<<strquery;
    delete query;
}


void DataBase::updateWord(QString lineEditRus,QString lineEditEng,QString wordID)
{
   QSqlQuery *query=new QSqlQuery(db);
   QString strquery("update Words set russian='"+lineEditRus+"' where id="+wordID+";");
   query->exec(strquery);
   qDebug()<<strquery;
   strquery="update Words set english='"+lineEditEng+"' where id="+wordID+";";
   query->exec(strquery);
   qDebug()<<strquery;
   delete query;
}


/* тысяча строк примерно 2 минуты
 * 2 массива 7 секунд
void DataBase::standartWG()
{
    QString userId,strquery("select id from RegUsers order by id desc;");
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(strquery);
    while(query->next())
    {
        userId=query->value(0).toString();
        break;
    }
    qDebug()<<"userId ="<<userId;
    const int szWG=26;
    QString arrWG_ID[szWG];
    arrWG_ID[0]="63";arrWG_ID[1]="64";arrWG_ID[2]="65";arrWG_ID[3]="67";arrWG_ID[4]="68";
    arrWG_ID[5]="69";arrWG_ID[6]="70";arrWG_ID[7]="71";arrWG_ID[8]="72";arrWG_ID[9]="74";
    arrWG_ID[10]="75";arrWG_ID[11]="76";arrWG_ID[12]="77";arrWG_ID[13]="78";arrWG_ID[14]="79";
    arrWG_ID[15]="80";arrWG_ID[16]="81";arrWG_ID[17]="82";arrWG_ID[18]="83";
    arrWG_ID[19]="84";arrWG_ID[20]="85";arrWG_ID[21]="86";arrWG_ID[22]="87";arrWG_ID[23]="88";
    arrWG_ID[24]="89";arrWG_ID[25]="90";
    const int szwg=1000;
    QString arrWordsRus1[szwg], arrWordsEng1[szwg], nameWG1="Люди и Семья",idWG;
    strquery="INSERT INTO WordGroup (name, userid) VALUES ('"+nameWG1+"','"+userId+"');";
    query->exec(strquery);
    strquery="select id from WordGroup order by id desc;";
    query->exec(strquery);
    while(query->next())
    {
        idWG=query->value(0).toString();
        break;
    }
    for (int i=0;i<szwg;i++)
    {
       arrWordsRus1[i]="blabla";
       arrWordsEng1[i]="blabla";
    }
    qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    for (int i=0;i<szwg;i++)
    {
            strquery="INSERT INTO Words (russian,english,wordid) VALUES ('"
                    +arrWordsRus1[i]+"','"+arrWordsEng1[i]+"','"+idWG+"');";
            query->exec(strquery);
    }
    qDebug()<<QTime::currentTime().toString("hh:mm:ss");
    delete query;
}*/



//заполнение комбобокса значениями из бд
void DataBase::showComboBoxReg(QComboBox *comboBox1, const QString queryString1)
{
    modelQueryBox->setQuery(queryString1);
    comboBox1->setModel(modelQueryBox);
}


//считывание параметов с комбобокса, получает комбобокс и запрос
void DataBase::valuesFromComboBox(QComboBox *comboBox2,const QString queryString2)
{
    QSqlQuery *queryName1=new QSqlQuery(db);
    queryName1->exec(queryString2);
    while(queryName1->next())
    {
        name = queryName1->value(1).toString();
        if(comboBox2->currentText()==name)
        {
            id = queryName1->value(0).toString();
            qDebug()<<"Find concidience!\tname = "<<name<<"\tid = "<<id;
            break;
        }
    }
}

//вывод значений
void DataBase::valuesFromComboBoxReturn(QComboBox *comboBox2, const QString queryString2, int &wgID)
{
    QSqlQuery *queryName1=new QSqlQuery(db);
    queryName1->exec(queryString2);
    while(queryName1->next())
    {
        name = queryName1->value(1).toString();
        if(comboBox2->currentText()==name)
        {
            id = queryName1->value(0).toString();
            qDebug()<<"Find concidience!\tname = "<<name<<"\tid = "<<id;
            break;
        }
    }
    wgID=id.toInt();
}




//для первой вкладки
void DataBase::valuesFromComboBoxTab1(QComboBox *comboBox3,const QString queryString3)
{
    QSqlQuery *queryName2=new QSqlQuery(db);
    queryName2->exec(queryString3);
    while(queryName2->next())
    {
        name3 = queryName2->value(1).toString();
        if(comboBox3->currentText()==name3)
        {
            id3 = queryName2->value(0).toString();
            qDebug()<<"Find concidience!\tname = "<<name3<<"\tid = "<<id3;
            break;
        }
    }
}

//для вкладки удаления
void DataBase::valuesFromComboBoxDel(QComboBox *comboBox4,const QString queryString4)
{
    QSqlQuery *queryName3=new QSqlQuery(db);
    queryName3->exec(queryString4);
    while(queryName3->next())
    {
        name2 = queryName3->value(1).toString();
        if(comboBox4->currentText()==name2)
        {
            id2 = queryName3->value(0).toString();
            qDebug()<<"Find concidience!\tname = "<<name2<<"\tid = "<<id2;
            break;
        }
    }

}

//перегрузка функции
void DataBase::valuesFromComboBox(QComboBox *comboBox5,const QString queryString5, QString *str)
{
    QSqlQuery *queryName4=new QSqlQuery(db);
    queryName4->exec(queryString5);
    while(queryName4->next())
    {
        name1 = queryName4->value(1).toString();
        if(comboBox5->currentText()==name1)
        {
            id1 = queryName4->value(0).toString();
            qDebug()<<"Find concidience!\tname = "<<name1<<"\tid = "<<id1;
            break;
        }
    }
    *str=name1;
}

//отображение таблицы слов на таб1, полчает tableView, если чекбокс отключен
void DataBase::showWordsTab1(QTableView *tableView1, const QString stringSearchTab1)
{
    QSqlQuery *queryTable1 = new QSqlQuery(db);
    if (stringSearchTab1.isEmpty())
    {
        stringQueryTable1="SELECT russian AS 'Слова на русском', english AS 'Слова на английском' "
                         "FROM Words WHERE wordid="+id3;
    }
    else
    {
        stringQueryTable1="SELECT russian AS 'Слова на русском', english AS 'Слова на английском' "
                         "FROM Words WHERE (wordid="+id3+" AND (russian LIKE '"+stringSearchTab1+
                         "%' OR english LIKE '"+stringSearchTab1+"%'));";
    }
    queryTable1->exec(stringQueryTable1);
    modelQueryTable1->setQuery(*queryTable1);
    tableView1->setModel(modelQueryTable1);
}


//отображение таблицы слов на таб1, полчает tableView, если чекбокс включен
void DataBase::showWordsTab1ifCheckBoxIsCheck(const QString strid, QTableView *tableView4,
                                              const QString stringSearchTab1Box)
{
    QSqlQuery *queryTableCheckBox = new QSqlQuery(db);
    if (stringSearchTab1Box.isEmpty())
    {
       strTab1Box="select wg.name as 'Название набора', w.russian as 'Слова на русском', "
                  "w.english as 'Слова на анлийском' from RegUsers as rg "
                  "left outer join WordGroup as wg on rg.id=wg.userid "
                  "join Words as w on wg.id=w.wordid "
                  "where rg.id="+strid+" order by wg.name;";
    }
    else
    {
       strTab1Box="select wg.name as 'Название набора', w.russian as 'Слова на русском', "
                  "w.english as 'Слова на анлийском' from RegUsers as rg "
                  "left outer join WordGroup as wg on rg.id=wg.userid "
                  "join Words as w on wg.id=w.wordid "
                  "where (rg.id="+strid+" and (russian LIKE '"+stringSearchTab1Box+"%' "
                  "OR english LIKE '"+stringSearchTab1Box+"%')) order by wg.name;";
    }
    queryTableCheckBox->exec(strTab1Box);
    modelQueryTab1CheckBox->setQuery(*queryTableCheckBox);
    tableView4->setModel(modelQueryTab1CheckBox);
}



//отображение во вкадке удаление NEN
void DataBase::showWordsTabDel(QTableView *tableView2, const QString stringSearchDel)
{
    QSqlQuery *queryTable3 = new QSqlQuery(db);
    if (stringSearchDel.isEmpty())
    {
        stringQueryTable2="SELECT id, russian AS 'Слова на русском', english AS 'Слова на английском' "
                         "FROM Words WHERE wordid="+id2;
    }
    else
    {
        stringQueryTable2="SELECT id, russian AS 'Слова на русском', english AS 'Слова на английском' "
                         "FROM Words WHERE (wordid="+id2+" AND (russian LIKE '"+stringSearchDel+
                         "%' OR english LIKE '"+stringSearchDel+"%'));";
    }
    queryTable3->exec(stringQueryTable2);
    modelQueryTable3->setQuery(*queryTable3);
    tableView2->setModel(modelQueryTable3);
    delete queryTable3;
}


//запись слов в бд, получает два лайн едита и создает запрос
void DataBase::insertWordsToDB(const QLineEdit *lineEditRus, const QLineEdit *lineEditEng)
{
    QSqlQuery *queryWord=new QSqlQuery(db);
    stringWordRusEng="INSERT INTO Words (russian,english,wordid) VALUES ('"
                     +lineEditRus->text()+"','"+lineEditEng->text()+"','"+id+"');";
    qDebug()<<"rus = "<<lineEditRus->text()<<"\teng = "<<lineEditEng->text();
    qDebug()<<stringWordRusEng;
    queryWord->exec(stringWordRusEng);
}


//запись нескольких слов сразу, получает два массива чаров, которые были созданы и создает запрос
/* Example : машина car
             телефон phone
             дом home
слово на русском потом пробел потом ентер и так далее*/
void DataBase::textEditAdd(const QString stringArrRus, const QString stringArrEng)
{
    QSqlQuery *queryTextEdit=new QSqlQuery(db);
    str1="INSERT INTO Words (russian,english,wordid) VALUES ('"
            +stringArrRus+"','"+stringArrEng+"','"+id+"');";
    qDebug()<<str1;
    queryTextEdit->exec(str1);
}


//удаление набора слов
void DataBase::deleteGroup(QTableView *tableView)
{
    QSqlQuery *queryDel=new QSqlQuery(db);
    str2="DELETE FROM Words WHERE wordid="+id1+";";
    str3="DELETE FROM WordGroup WHERE id="+id1+";";
    qDebug()<<str2<<"\n"<<str3;
    queryDel->exec(str2);
    queryDel->exec(str3);
    str3="select from WordGroup where id"+id1+";";
    queryDel->exec(str3);
    modelQueryDel->setQuery(*queryDel);
    tableView->setModel(modelQueryDel);
}

//отобажение всех наборов в tableView на вкладке добавление набора
void DataBase::showAllGroup(QTableView *tableView3, const QString queryString7)
{
    QSqlQuery *queryTableViewGroup=new QSqlQuery(db);
    qDebug()<<queryString7;
    queryTableViewGroup->exec(queryString7);
    modelQueryTable2->setQuery(*queryTableViewGroup);
    tableView3->setModel(modelQueryTable2);
    delete queryTableViewGroup;
}


// добавление наборов
 bool DataBase::addWordGroup(QString strAddWG, const QString strid)
 {
     QString strquery("select count(*) from WordGroup where (userid="+strid+
                      " and name='"+strAddWG+"');");
     int count=0;
     qDebug()<<strquery;
     QSqlQuery *query = new QSqlQuery (db);
     query->exec(strquery);
     while(query->next())
         count=query->value(0).toInt();
     if (count>0)
     {
         delete query;
         return false;
     }
     if (count==0)
     {
        strquery="INSERT INTO WordGroup (name, userid) VALUES ('"+strAddWG+"','"+strid+"');";
        query->exec(strquery);
        delete query;
     }
     return true;
 }

 //поиск в табе удаление слов
 void DataBase::ifCBIsCheckDel(const QString stridDel, QTableView *tableViewDel,
                                               const QString stringSearchTabBoxDel)
 {
     QSqlQuery *queryTableCheckBox = new QSqlQuery(db);
     QString strTabBoxDel;
     if (stringSearchTabBoxDel.isEmpty())
     {
        strTabBoxDel="select w.id, wg.name as 'Название набора', w.russian as 'Слова на русском', "
                   "w.english as 'Слова на анлийском' from RegUsers as rg "
                   "left outer join WordGroup as wg on rg.id=wg.userid "
                   "join Words as w on wg.id=w.wordid "
                   "where rg.id="+stridDel+" order by wg.name;";
     }
     else
     {
        strTabBoxDel="select w.id, wg.name as 'Название набора', w.russian as 'Слова на русском', "
                   "w.english as 'Слова на анлийском' from RegUsers as rg "
                   "left outer join WordGroup as wg on rg.id=wg.userid "
                   "join Words as w on wg.id=w.wordid "
                   "where (rg.id="+stridDel+" and (russian LIKE '"+stringSearchTabBoxDel+"%' "
                   "OR english LIKE '"+stringSearchTabBoxDel+"%')) order by wg.name;";
     }
     queryTableCheckBox->exec(strTabBoxDel);
     modelQueryDel->setQuery(*queryTableCheckBox);
     tableViewDel->setModel(modelQueryDel);
 }


void DataBase::delWord(const QString idDelWord)
{
    QSqlQuery *queryDelWord = new QSqlQuery(db);
    QString strQueryDelWord="DELETE FROM Words WHERE id="+idDelWord+";";
    queryDelWord->exec(strQueryDelWord);
}


// КНОПКА ТЕСТИРОВАНИЕ


void DataBase::testReceiveSize(int *wgID, int *size)
{
    //получаем количество элементов в таблице
    qDebug()<<" testFillArr wgID = "<<*wgID;
    QString querystr="select count(*) from Words where wordid="+QString::number(*wgID)+";";
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(querystr);
    query->first();
    //присваеваем количество строк в size
    *size=query->value(0).toInt();
}



//передача размера массива и заполнение
void DataBase::fillArrs(QString *labelstr, const int size, const int *wgID, int firstWordID)
{
    QString querystr1="select * from Words where wordid="+QString::number(*wgID)+";";
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(querystr1);
    int j=0;
    int *arrID=new int[size];
    while(query->next())
    {
        if (j==size)
                break;
        arrID[j]=query->value(0).toInt();
        j++;
    }   
    qDebug()<<arrID[0]<<arrID[1]<<arrID[2]<<arrID[3]<<arrID[4]<<arrID[size-1];
    firstWordID=arrID[firstWordID];
    qDebug()<<"Word ID = "<< firstWordID;
    QString querystr2="select russian from Words where id="+QString::number(firstWordID);
    query->exec(querystr2);
    query->first();
    *labelstr=query->value(0).toString();
    delete [] arrID;
}



//заполнение вспомогательных массивов
void DataBase::fillArrID(int * arrId, int * arr0or1, const int size, const int wordGroupID, int * arrResult)
{
    wgID=wordGroupID;
    QString querystr1="select * from Words where wordid="+QString::number(wordGroupID)+";";
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(querystr1);
    int j=0;
    while(query->next())
    {
        if (j==size)
                break;
        arrId[j]=query->value(0).toInt();
        arr0or1[j]=0;
        arrResult[j]=1;
        j++;

    }
}



//тестирование
void DataBase::testDB(QWidget *test, QLabel *label, QLineEdit *lineEditTest, const int *arrRandomId, int *check, int *arrAnswerBool, const int size,
                      QLabel *labelProgress, QProgressBar *progressBar)
{
    qDebug()<<"\nclick Answer into testDB";
    QString querystr="select * from Words where id="+QString::number(arrRandomId[*check])+";";
    qDebug()<<querystr;
    QSqlQuery *query = new QSqlQuery (db);
    QString rus,eng;
    query->exec(querystr);
    while(query->next())
    {
        rus=query->value(1).toString();
        eng=query->value(2).toString();
    }
    if (lineEditTest->text()==eng)
    {

        arrAnswerBool[*check]=1;
        counterProgress++;
        labelProgress->setText(QString::number(counterProgress)+" из "+QString::number(size));
        progressBar->setValue(counterProgress);
        qDebug()<<"arrAnswerBool ="<<arrAnswerBool[*check];
        qDebug()<<"Right! You answer ="<<lineEditTest->text()<<"russian ="<<rus<<"english ="<<eng;
        *check=*check+1;
        if(*check==size)
            return;
        querystr="select * from Words where id="+QString::number(arrRandomId[*check])+";";
        query->exec(querystr);
        while(query->next())
        {
            label->setText(query->value(1).toString());
            rus=query->value(1).toString();
            eng=query->value(2).toString();
        }
        qDebug()<<"Next word russian ="<<rus<<"english ="<<eng;
        lineEditTest->clear();
        return;
    }
    else
    {
        qDebug()<<"Wrong! You answer ="<<lineEditTest->text()<<"russian ="<<rus<<"english ="<<eng;
        Functioins::wrongWord(*test, rus,lineEditTest->text());
        lineEditTest->clear();
        return;
    }
}

void DataBase::answerLater(QLabel *label, int *check, const int *arrRandomId)
{
    QString *strquery=new QString;
    QSqlQuery *query = new QSqlQuery (db);
    *strquery="select * from Words where id="+QString::number(arrRandomId[*check])+";";
    query->exec(*strquery);
    while(query->next())
        label->setText(query->value(1).toString());
    delete strquery; delete query;
}

void DataBase::searchLaterWorld(const int *arrRandomId, int *arrAnswerBool, QLabel *label, const int size, int *check, bool *end)
{
    qDebug()<<"searchLaterWorld";
    for(int i=0;i<size;i++)
    {
        answerArr=arrAnswerBool[i];
        if (answerArr==0)
        {
            *check=i;
            QString *strquery=new QString;
            QSqlQuery *query = new QSqlQuery (db);
            *strquery="select * from Words where id="+QString::number(arrRandomId[*check])+";";
            query->exec(*strquery);
            while(query->next())
                label->setText(query->value(1).toString());
            //lineEditTest->clear();
            delete strquery; delete query;
            return;
        }
    }
    *end=true;
}


void DataBase::testDBExecute(QWidget *test, const int *arrRandomId, int *arrAnswerBool, QLineEdit *lineEditTest, int *check, const int size,
                             QLabel *labelProgress, QProgressBar *progressBar)
{
    qDebug()<<"\nclick Answer into testDBExecute";
    QString *strquery=new QString;
    QSqlQuery *query = new QSqlQuery (db);
    QString querystr="select * from Words where id="+QString::number(arrRandomId[*check])+";";
    QString rus,eng;
    query->exec(querystr);
    while(query->next())
    {
        rus=query->value(1).toString();
        eng=query->value(2).toString();
    }
    if (lineEditTest->text()==eng)
    {
        arrAnswerBool[*check]=1;
        counterProgress++;
        labelProgress->setText(QString::number(counterProgress)+" из "+QString::number(size));
        progressBar->setValue(counterProgress);
        qDebug()<<"Right! You answer ="<<lineEditTest->text()<<"russian ="<<rus<<"english ="<<eng;
        qDebug()<<"Next word russian ="<<rus<<"english ="<<eng;
        lineEditTest->clear();
    }
    else
    {
        qDebug()<<"Wrong! You answer ="<<lineEditTest->text()<<"russian ="<<rus<<"english ="<<eng;
        Functioins::wrongWord(*test, rus,lineEditTest->text());
        lineEditTest->clear();
    }
    delete strquery; delete query;
}




//нажимание кнопки не знаю, активируется сетчик вхождений
/*void DataBase::dontKnow(QString *strDontKnow, const int check, const int *arrRandomId)
{
    QSqlQuery *query = new QSqlQuery (db);
    QString *strquery=new QString("select * from Words where id="+QString::number(arrRandomId[check])+";");
    QString *rus = new QString;
    QString *eng = new QString;
    QString *id = new QString;
    int *count = new int;
    query->exec(*strquery);
    while(query->next())
    {
        *rus=query->value(1).toString();
        *eng=query->value(2).toString();
    }
    *strDontKnow=*rus+" - "+*eng;

    *strquery="select id from WordGroup where name='Words to repeat'";
    query->exec(*strquery);
    while (query->next())
        *id=query->value(0).toString();
    *strquery="select count(*) from Words where (wordid="+*id+" and english='"+*eng+"');";
    query->exec(*strquery);
    while (query->next())
        *count=query->value(0).toInt();
    if(*count==0)
    {
        *strquery="INSERT INTO Words (russian,english,wordid) VALUES ('"+*rus+"','"+*eng+"',"+*id+");";
        query->exec(*strquery);
        qDebug()<<"id ="<<*id<<"\nstrquery ="<<*strquery;
    }
    delete rus; delete id; delete eng; delete query; delete strquery; delete count;
}*/

void DataBase::dontKnow(QString *strDontKnow, const int check, const int *arrRandomId, QString userId)
{
    QSqlQuery *query = new QSqlQuery (db);
    QString *strquery=new QString("select * from Words where id="+QString::number(arrRandomId[check])+";");
    QString *rus = new QString;
    QString *eng = new QString;
    QString *idGroup = new QString;
    QString *Word = new QString;
    int *count = new int;
    this->db_Transaction("open");
    query->exec(*strquery);
    while(query->next())
    {
        *rus=query->value(1).toString();
        *eng=query->value(2).toString();
    }
    *strDontKnow=*rus+" - "+*eng;
     bool concidience=false;
    *strquery="select id from WordGroup where (name='Words to repeat' AND userid="+userId+");";
    query->exec(*strquery);
    while (query->next())
        *idGroup=query->value(0).toString();
    *strquery="select english from Words where (wordid="+*idGroup+" AND english ='"+*eng+"');";
    query->exec(*strquery);
    while (query->next())
    {
        *Word=query->value(0).toString();
        if(*Word==*eng)
        {
            concidience=true;
            break;
        }
    }
    if (!concidience)
    {
        *strquery="INSERT INTO Words (russian,english,wordid) VALUES ('"+*rus+"','"+*eng+"',"+*idGroup+");";
        query->exec(*strquery);
        qDebug()<<"id ="<<*idGroup<<"\nstrquery ="<<*strquery;
    }
    else
    {
        qDebug()<<"Такое слово уже есть!";
    }
    this->db_Transaction("commit");
    delete rus; delete Word; delete eng; delete query; delete strquery; delete count; delete idGroup;
}




//проверка есть ли поле со словами для повторения в таблице набор слов, если нету, то создаем
void DataBase::createWG(QString strId)
{
   QSqlQuery *query = new QSqlQuery (db);
   QString *strquery=new QString;
   *strquery="select count(*) FROM WordGroup where (userid="+strId+" and name='Words to repeat');";
   query->exec(*strquery);
   int *count=new int;
   while (query->next())
       *count=query->value(0).toInt();
   qDebug()<<"count = "<<*count;
   if (*count==0)
   {
       *strquery="INSERT INTO WordGroup (name, userid) VALUES ('Words to repeat','"+strId+"');";
       query->exec(*strquery);
       qDebug()<<"WG is added";
   }
   delete strquery; delete count; delete query;
}

//запись в таблицы с результатами
void DataBase::insertResult(int *arrRandomId, int *arrResult, int count, int size, int userid, QTime time, bool OnePuck)
{
    //строка с запросами
    QString *strquery=new QString("SELECT name FROM WordGroup where id="+QString::number(wgID)+";");
    //универсальная рабочая строка
    QString *strwork=new QString;
    QString *strwork1=new QString;
    userID=userid;
    /*sizedb=new int;
    countdb=new int;*/
    /*timedb=new QTime(0,0,0);
    *timedb=time;*/
    sizedb=size;
    countdb=count;
    //запрос
    QSqlQuery *query = new QSqlQuery (db);
    //узнаем название набора слов
    if (OnePuck)
    {
        query->exec(*strquery);
        while (query->next())
            *strwork=query->value(0).toString();
    }
    else
        *strwork="Все наборы";
    //заполняем таблицу результат
    *strquery="INSERT INTO Result (groupname,date,right,wrong,time,percent, userid) "
              "VALUES ('"+*strwork+"','"+QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")+"',"
            +QString::number(size-count)+","+QString::number(count)+",'"+time.toString("HH:mm:ss")+"','"
            +QString::number((100*(size-count))/(size))+"%',"+QString::number(userid)+");";
    qDebug()<<*strquery;
    query->exec(*strquery);
    //узнаем последний айди в таблице результат
    *strquery="SELECT max(id) FROM Result where userid="+QString::number(userid)+";";
    query->exec(*strquery);
    while (query->next())
    {
        *strwork=query->value(0).toString();
    }
    QString *rus=new QString;
    QString *eng=new QString;
    //заполняем таблицу ResultMore
    this->db_Transaction("open");
    for (int i=0;i<size;)
    {
        *strquery="select russian, english from Words where id="+QString::number(arrRandomId[i])+";";
        query->exec(*strquery);
        while(query->next())
        {
            *rus=query->value(0).toString();
            *eng=query->value(1).toString();
        }
        if (arrResult[i]==1)
            *strwork1="Верно";
        else
            *strwork1="Не верно";
        *strquery="INSERT INTO ResultMore (rus,eng,answer,resultid) VALUES "
              "('"+*rus+"','"+*eng+"','"+*strwork1+"',"+*strwork+");";
        query->exec(*strquery);
        i++;
    }
    this->db_Transaction("commit");
    delete strquery; delete query; delete rus; delete eng; delete strwork; delete strwork1;
}


void DataBase::showResult1(QTableView *tableResult, const QString userid, QLabel *labelResult)
{
    QString *strquery=new QString("SELECT max(id) FROM Result where userid="+userid+";");
    QString *resultID=new QString;
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(*strquery);
    while(query->next())
        *resultID=query->value(0).toString();
    *strquery="SELECT rus as 'Слова на русском',eng as 'Слова на английском',answer as 'Ваш ответ' "
              "FROM ResultMore where resultid="+*resultID+";";
    query->exec(*strquery);
    MyTableModel *modelResult = new MyTableModel;
    modelResult  ->setQuery(*query);
    tableResult->setModel(modelResult);
    *strquery="select right, wrong, time from Result where userid ="+userid+";";
    int *right=new int;
    int *wrong=new int;
    QString *time=new QString;
    query->exec(*strquery);
    while(query->next())
    {
        *right=query->value(0).toInt();
        *wrong=query->value(1).toInt();
        *time=query->value(2).toString();
    }
    labelResult->setText("Верно - "+QString::number(*right)+" Неверно - "+QString::number(*wrong)+
                         "\n"+QString::number(*right*100/(*right+*wrong))+"%\nВремени потрачено - "+*time);
    delete strquery; delete right; delete wrong; delete time; delete query; delete resultID;
}

//посмотреть результат каждого тестирования по словам, кнопка Подробно
void DataBase::resultMoreButton(QString idResult, QTableView *tableResult)
{
    QString *strquery=new QString("SELECT rus as 'Слова на русском',eng as 'Слова на английском',answer as 'Ваш ответ' "
                                  "FROM ResultMore where resultid="+idResult+";");
    QSqlQuery *query = new QSqlQuery (db);
    query->exec(*strquery);
    modelRes=new MyTableModel(this);
    modelRes  ->setQuery(*query);
    tableResult->setModel(modelRes);
    delete strquery; delete query;
}



void DataBase::showResultButton(const QString id, QTableView *tableResult, int *countResult)
{
    modelRes=new MyTableModel(this);
    QSqlQuery *query = new QSqlQuery (db);
    QString *strquery=new QString("select count(*) from Result where userid="+id+";");
    query->exec(*strquery);
    while(query->next())
        *countResult=query->value(0).toInt();
    *strquery="select groupname as 'Название набора', date as 'Дата', right as 'Верно',"
              "wrong as 'Не верно', time as 'Время', percent as 'Прогресс' , id from Result where userid="+id+" order by id desc;";
    query->exec(*strquery);
    modelRes->setQuery(*query);
    tableResult->setModel(modelRes);
    delete strquery; delete query;
}

void DataBase::testReceiveSizeCheck(int *size, const QString userid)
{
    QString *strquery=new QString;
    QSqlQuery *query=new QSqlQuery(db);
    //количество наборов
    countCheck = new int;
    //узнаю количество наборов слов у пользователя
    *strquery="select count(*) from WordGroup where userid="+userid;
    query->exec(*strquery);
    while (query->next())
        *countCheck=query->value(0).toInt();
    /*создаю массив с айди наборов слов пользователя
    этот массив остается в классе бд, потом из функции заполнения к нему обращусь*/
    arrWGId=new int[*countCheck];
    //заполняю этот массив
    *strquery="select * from WordGroup where userid="+userid;
    query->exec(*strquery);
    int *i=new int;
    *i=0;
    QString *strarrWGId = new QString;
    while (query->next()&&*i<*countCheck)
    {
        arrWGId[*i]=query->value(0).toInt();
        *strarrWGId=*strarrWGId+QString::number(arrWGId[*i])+" ";
        *i=*i+1;
    }
    qDebug()<<"arrWGId = "<<*strarrWGId;
    delete i; delete strarrWGId;
    //узнаю количество слов во всех наборах пользователя и присваиваю в size
    for (int i=0; i<*countCheck;)
    {
        *strquery="select count(*) from Words where wordid="+QString::number(arrWGId[i]);
        query->exec(*strquery);
        while (query->next())
            *size=*size+query->value(0).toInt();
        i++;
    }
    delete strquery; delete query;
}

//заполняем вспомогательные массивы
void DataBase::fillArrIDCheck(int *arrId, int *arr0or1, const int size, int *arrResult)
{
    QString *strquery = new QString;
    QSqlQuery *query = new QSqlQuery (db);
    int j=0;
    for (int i=0;i<*countCheck;)
    {
        *strquery="select * from Words where wordid="+QString::number(arrWGId[i]);
        query->exec(*strquery);
        while (query->next())
        {
            arrId[j]=query->value(0).toInt();
            j++;
        }
        i++;
    }
    for (int i=0;i<size;i++)
    {
        arr0or1[i]=0;
        arrResult[i]=1;
    }
    delete strquery; delete query; delete countCheck;
}

//заполнение лейбла для первого слова
void DataBase::firstWordToLabel(const int firstWordID, QLabel *labelCheck)
{
    QString *strquery = new QString;
    QSqlQuery *query = new QSqlQuery (db);
    *strquery="select * from Words where id="+QString::number(firstWordID);
    query->exec(*strquery);
    while (query->next())
        labelCheck->setText(query->value(1).toString());
    delete strquery; delete query;
}

void DataBase::countOfWords(int *wgID, int *count)
{
    QString *strquery = new QString;
    QSqlQuery *query = new QSqlQuery (db);
    *strquery="select count(*) from Words where wordid="+QString::number(*wgID);
    query->exec(*strquery);
    while (query->next())
        *count=query->value(0).toInt();
    qDebug()<<"countOfWords: wgID ="<<*wgID<<"count ="<<*count;
    delete strquery; delete query;
}

//admin


void DataBase::db_Query(QString strquery)
{
    QSqlQuery query(db);
    query.exec(strquery);
}

QString DataBase::db_QueryRecordOneNumber(QString strquery, int i, int conditionalWhile)
{
    QSqlQuery query(db);
    QString data;
    query.exec(strquery);
    int j=0;
    while (query.next())
    {
         data=query.value(i).toString();
         if(j==conditionalWhile)
             break;
         j++;
    }
    return data;
}

void DataBase::db_TableModel(QTableView *table, QString strquery)
{
    QSqlQuery query(db);
    query.exec(strquery);
    universalModel->setQuery(query);
    table->setModel(universalModel);
}

void DataBase::db_Transaction(QString transaction)
{
    if (transaction=="open")
        db.transaction();
    if(transaction=="commit")
        db.commit();
    if(transaction=="rollback")
        db.rollback();
}
