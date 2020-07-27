#include "instruction.h"
#include "ui_instruction.h"

Instruction::Instruction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);
    this->setStyleSheet("QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(240, 240, 240, 230), stop:1 rgba(160, 141, 110, 150));}"
                        "QPushButton:hover{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 rgba(160, 141, 110, 200), stop:1 rgba(240, 240, 240, 230));}"
                        "QPushButton:pressed{background-color: rgba(110, 87, 51, 160);}");
}

Instruction::~Instruction()
{
    delete ui;
}

void Instruction::openInstruction()
{

    QImage image(":/instruction/InstructionAllWords.jpg");
    ui->label->setPixmap(QPixmap::fromImage(image));
    i=1;
    Functioins::StartProgram(*this,"Помощь");
}

void Instruction::on_pushButtonClose_clicked()
{
    this->close();
}

void Instruction::on_pushButtonNext_clicked()
{
    i++;
    QImage image;
    switch (i)
    {
        case 2:
            image.load(":/instruction/InstructionAdd.jpg");
            break;
        case 3:
            image.load(":/instruction/InstructionAddGroup.jpg");
            break;
        case 4:
            image.load(":/instruction/InstructionDelete.jpg");
            break;
        case 5:
            i--;
            return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void Instruction::on_pushButtonBefore_clicked()
{
    i--;
    QImage image;
    switch (i)
    {
        case 0:
            i++;
            return;
        case 1:
            image.load(":/instruction/InstructionAllWords.jpg");
            break;
        case 2:
            image.load(":/instruction/InstructionAdd.jpg");
            break;
        case 3:
            image.load(":/instruction/InstructionAddGroup.jpg");
            break;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
