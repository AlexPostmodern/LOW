#include "functioins.h"

Functioins::Functioins(QObject *parent) : QObject(parent)
{

}

//запуск
void Functioins::StartProgram(QWidget &window, const QString label, const int width, const int hight)
{
    window.setWindowTitle(label);
    window.setMinimumSize(width, hight);
    window.setMaximumSize(width, hight);
    window.show();
}


void Functioins::StartProgram(QWidget &window, const QString label)
{
    window.setWindowTitle(label);
    window.show();
}


//выход
bool Functioins::CloseProgram(QWidget &window, QCloseEvent *event, const QString headline, const QString label)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(&window, headline,label,QMessageBox::Yes | QMessageBox::No);
    if (reply ==QMessageBox::Yes)
        {
            event->accept();
            return true;
        }
    else
        {
            event->ignore();
            return false;
        }
}

void Functioins::wrongWord(QWidget &test, QString rus, QString strlineEdit)
{
    QMessageBox::warning(&test,"Ошибка","У вас ошибка - "+strlineEdit+"\nПопробуйте снова - "+rus);
}


void Functioins::GetGeometry(QWidget &window, int *x, int *y)
{
    //*x= window.geometry().x();
    //*y= window.geometry().y();
    *x= window.pos().x();
    *y= window.pos().y();
    qDebug()<<"x ="<<*x<<"y ="<<*y;
}

void Functioins::MoveWindow(QWidget &window, int *x, int *y)
{
    window.move(*x,*y);
}
