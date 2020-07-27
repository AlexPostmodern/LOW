#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>
#include "functioins.h"


namespace Ui {
class Instruction;
}

class Instruction : public QDialog
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = nullptr);
    ~Instruction();

public slots:
    void openInstruction();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonBefore_clicked();

private:
    Ui::Instruction *ui;
    int i;
};

#endif // INSTRUCTION_H
