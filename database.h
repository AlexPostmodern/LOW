#ifndef DATABASE_H
#define DATABASE_H

#include <functioins.h>
#include <mytablemodel.h>
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QTableView>
#include <QLineEdit>
#include <QTime>
#include <QLineEdit>
#include <QLabel>
#include <QProgressBar>
#include <QDir>


class DataBase : public QObject
{
    Q_OBJECT
public:
    ~DataBase();
    explicit DataBase(QObject *parent = nullptr);
    static bool createConnection();
    static bool clickOk(const QString stringLogin, const QString stringPass, QString *strLogin,
                    QString *strName, QString *strPass, QString *strId);
    static bool clickOkReg(const QString stringLogin, const QString stringPass_2, const QString stringName);
    void showComboBoxReg(QComboBox *comboBox, const QString queryString);
    void valuesFromComboBox(QComboBox *comboBox, const QString queryString);
    void valuesFromComboBox(QComboBox *comboBox, const QString queryString, QString *str);
    void showWordsTab1(QTableView *tableView, const QString stringSearch);
    void insertWordsToDB(const QLineEdit *lineEditRus, const QLineEdit *lineEditEng);
    void textEditAdd(const QString stringArrRus, const QString stringArrEng);
    void deleteGroup(QTableView *tableView);
    void showAllGroup(QTableView *tableView, const QString queryString);
    void showWordsTabDel(QTableView *tableView, const QString stringSearch);
    void valuesFromComboBoxDel(QComboBox *comboBox,const QString queryString);
    void valuesFromComboBoxTab1(QComboBox *comboBox,const QString queryString);
    void showWordsTab1ifCheckBoxIsCheck(const QString strid, QTableView *tableView4, const QString stringSearchTab1Box);
    bool addWordGroup(QString strAddWG, const QString strid);
    void ifCBIsCheckDel(const QString stridDel, QTableView *tableViewDel,
                                                  const QString stringSearchTabBoxDel);
    void delWord(const QString idDelWord);
    void testReceiveSize(int *wgID, int *size);
    void valuesFromComboBoxReturn(QComboBox *comboBox2,const QString queryString2, int &size);
    void fillArrs(QString* labelstr, const int size, const int *wgID, int firstWordID);
    void fillArrID(int * arrId, int *arr0or1, const int size, const int wordGroupID, int *arrResult);
    void testDB(QWidget *test, QLabel *label, QLineEdit *lineEditTest, const int *arrRandomId, int *check, int *arrAnswerBool, const int size,
                QLabel *labelProgress, QProgressBar *progressBar);
    void dontKnow(QString *strDontKnow, const int check, const int *arrRandomId, QString userId);
    void createWG(QString strId);
    void insertResult(int *arrRandomId, int *arrResult, int count, int size, int userid, QTime time, bool OnePuck);
    static void showResult1(QTableView *tableResult, const QString userid, QLabel *labelResult);
    void showResultButton(const QString id, QTableView *tableResult, int *countResult);
    void testReceiveSizeCheck(int *size, const QString userid);
    void fillArrIDCheck(int * arrId, int *arr0or1, const int size, int *arrResult);
    void firstWordToLabel(const int firstWordID, QLabel *labelCheck);
    void countOfWords(int* wgID, int*count);
    void answerLater(QLabel *label, int *check, const int *arrRandomId);
    void searchLaterWorld(const int *arrRandomId, int *arrAnswerBool, QLabel *label, const int size, int *check, bool *end);
    void testDBExecute(QWidget *test, const int *arrRandomId, int *arrAnswerBool, QLineEdit *lineEditTest, int *check, const int size,
                       QLabel *labelProgress, QProgressBar *progressBar);
    void resultMoreButton(QString idResult, QTableView *tableResult);
    void standartWG();
    void updateWG(QString lineEdit,QString userid,QString nameWG);
    void updateWord(QString lineEditRus,QString lineEditEng,QString wordID);
    //общие функции
    void db_Query(QString strquery);
    QString db_QueryRecordOneNumber(QString strquery, int i, int conditionalWhile);
    void db_TableModel(QTableView *table, QString strquery);
    void db_Transaction(QString transaction);
public slots:

private slots:

private:
static QSqlDatabase db;
static int sizedb,countdb;
MyTableModel *modelRes;
QSqlQueryModel*modelQueryBox, *universalModel;
QSqlQueryModel *modelQueryTable1,*modelQueryTable2,*modelQueryTable3, *modelQueryTab1CheckBox, *modelQueryDel;
QString name,name1,name2,name3,id,id1,id2,id3,stringQueryTable1,stringQueryTable2, stringWordRusEng;
QString str1,str2,str3,str4,str5, addWordGroupString, strTab1Box;
//QTime *timedb;
int wgID, userID, *arrWGId, *countCheck,answerArr, counterProgress=0;

};
#endif // DATABASE_H
