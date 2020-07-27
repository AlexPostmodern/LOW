#include "mainwindow.h"
#include "functioins.h"
#include "menu.h"
#include "reg.h"
#include "editor.h"
#include "test.h"
#include "choosing.h"
#include "result.h"
#include "instruction.h"
#include "update.h"
#include "admin.h"
#include "newsyntax.h"
#include "updateadmin.h"
#include "updatetables.h"
#include <QApplication>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //подключение к бд
    DataBase::createConnection();
    //создание объектов кассов
    MainWindow window;
    Menu menu;
    Reg reg;
    Editor editor;
    Test test;
    Choosing choosing;
    DataBase db;
    Result result;
    Instruction instruction;
    Update update;
    Admin admin;
    UpdateAdmin updateadmin;
    UpdateTables updatetables;
    //старт приложения, првоерка на последнего пользователя и заход в него сразу
    int lastEnter,countOfUsers=(db.db_QueryRecordOneNumber("select count(*) from RegUsers;",0,0)).toUInt();
    bool c=false;
    for (int i=0;i<countOfUsers;i++)
    {
        lastEnter=(db.db_QueryRecordOneNumber("select lastEnter from RegUsers;",0,i)).toUInt();
        if(lastEnter==1)
        {
            c=true;
            window.SetId(db.db_QueryRecordOneNumber("select id from RegUsers;",0,i));
            window.SetLogin(db.db_QueryRecordOneNumber("select login from RegUsers;",0,i));
            window.SetName(db.db_QueryRecordOneNumber("select name from RegUsers;",0,i));
            window.SetPass(db.db_QueryRecordOneNumber("select password from RegUsers;",0,i));
            break;
        }
    }
    if (c)
        menu.OpeningMenu();
    else
        Functioins::StartProgram(window,"Вход",760,489);

       //сигналы вызыващие окна и взаимодействия между классами
    QObject::connect(&window,SIGNAL(InvokeMenu(int*,int*)),&menu,SLOT(OpeningMenu(int*,int*)));
    QObject::connect(&window,SIGNAL(InvokeReg(int*,int*)),&reg,SLOT(OpeningReg(int*,int*)));
    QObject::connect(&reg,SIGNAL(SetEnabledReg()),&window,SLOT(RegButtEnabled()));
    QObject::connect(&menu,SIGNAL(InvokeEditor(int*, int*)),&editor,SLOT(OpeningEditor(int*,int*)));
    QObject::connect(&editor,SIGNAL(InvokeMenuBack(int*, int*)),&menu,SLOT(BackEditor(int*, int*)));
    QObject::connect(&menu, SIGNAL(InvokeChoosing(int*, int*)), &choosing, SLOT(OpenChoosing(int*,int*)));
    QObject::connect(&choosing,SIGNAL(InvokeMenuBack1(int*, int*)),&menu,SLOT(BackEditor(int*, int*)));
    QObject::connect(&choosing, SIGNAL(InvokeTest(int*, int*, int*)), &test, SLOT(fillArr(int*, int*, int*)));
    QObject::connect(&choosing, SIGNAL(InvokeTestCheck(int*, int*)), &test, SLOT(fillArrCheck(int*, int*)));
    QObject::connect(&test, SIGNAL(showResult1(int*, int*)), &result, SLOT(openResult1(int*, int*)));
    QObject::connect(&result,SIGNAL(closeResult(int*, int*)),&menu,SLOT(OpeningMenu(int*, int*)));
    QObject::connect(&menu,SIGNAL(InvokeResult(int*, int*)),&result,SLOT(openResultFromMenu(int*,int*)));
    QObject::connect(&test,SIGNAL(InvokeChoosing1(int*, int*)),&choosing,SLOT(OpenChoosing(int*, int*)));
    QObject::connect(&editor, SIGNAL(InvokeInstruction()),&instruction, SLOT(openInstruction()));
    QObject::connect(&editor,SIGNAL(InvokeUpdateWG(QString*)),&update,SLOT(openUpdateWG(QString*)));
    QObject::connect(&update,SIGNAL(InvokeEditorFromUpdate(QString)),&editor,SLOT(ValuesComboBoxAfterUpdate(QString)));
    QObject::connect(&editor,SIGNAL(InvokeUpdateWord(QString*,QString*,QString*)),&update,SLOT(openUpdateWord(QString*,QString*,QString*)));
    QObject::connect(&menu,SIGNAL(signal_InvokeAdmin()),&admin,SLOT(slot_OpenAdmin()));
    QObject::connect(&admin,SIGNAL(signalInvokeUpdateAdmin(QString)),&updateadmin,SLOT(slotOpenUpdateAdmin(QString)));
    QObject::connect(&updateadmin,SIGNAL(signalUpdateHasDone(QString)),&admin,SLOT(slot_ChangeListRegUsers(QString)));
    QObject::connect(&admin,SIGNAL(signalNewRegUser()),&updateadmin,SLOT(slotNewRegUser()));
    QObject::connect(&admin,SIGNAL(signalInvokeMenuFromAdmin()),&menu,SLOT(OpeningMenu()));
    QObject::connect(&admin,SIGNAL(singalInvokeUpdateTables(QString)),&updatetables,SLOT(slotOpenUpdateTables(QString)));
     QObject::connect(&menu,SIGNAL(signalInvokeMainWindow(int*, int*)),&window,SLOT(changeUser(int*, int*)));
    return a.exec();
}
