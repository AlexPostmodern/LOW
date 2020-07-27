#ifndef FUNCTIOINS_H
#define FUNCTIOINS_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QEvent>
#include <QCloseEvent>
#include <QtDebug>

class Functioins : public QObject
{
    Q_OBJECT
public:
    explicit Functioins(QObject *parent = nullptr);
    static void StartProgram(QWidget &window, const QString label, const int width, const int hight);
    static void StartProgram(QWidget &window, const QString label);
    static bool CloseProgram(QWidget &window, QCloseEvent *event, const QString headline, const QString label);
    static void wrongWord(QWidget &test, QString rus, QString strlineEdit);
    static void GetGeometry(QWidget &window, int *x, int *y);
    static void MoveWindow(QWidget &window, int *x, int *y);


signals:

public slots:
};

#endif // FUNCTIOINS_H
