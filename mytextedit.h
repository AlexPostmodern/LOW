#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QKeyEvent>
#include <QtDebug>

class MyTextEdit:public QTextEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = nullptr);
signals:
    void signalReturnPressed();
protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // MYTEXTEDIT_H
