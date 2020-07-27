#include "mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent)
{

}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    if ((e->key()==Qt::Key_Enter)||e->key()==Qt::Key_Return)
    {
        qDebug()<<"ENTER or RETURN PRESSED";
        QString text(MyTextEdit::toPlainText());
        if (text=="")
            QTextEdit::keyPressEvent(e);
        else if(text.back()==";")
            emit signalReturnPressed();
        else
            QTextEdit::keyPressEvent(e);
    }
    else
        QTextEdit::keyPressEvent(e);
}
