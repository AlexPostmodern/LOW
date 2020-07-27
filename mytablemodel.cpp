#include "mytablemodel.h"
#include <QColor>
#include <QLinearGradient>

MyTableModel::MyTableModel(QObject *parent):QSqlQueryModel(parent)
{

}
QVariant MyTableModel::data(const QModelIndex &idx, int role) const
{
    QColor color,secondColor;
    if (role==Qt::BackgroundColorRole)
    {
        //задание цвета столбцам с "верно"/"не верно"
        if ((idx.column() == 2)&&(!(QSqlQueryModel::data(this->index(idx.row(),2)).toString()=="Не верно")))
        {
            color.setRgb(203,235,203,255);
            secondColor.setRgb(55,176,55,255);
            QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
            linearGrad.setColorAt(0, color);
            linearGrad.setColorAt(1, secondColor);
            return QBrush(linearGrad);
            //color.setRgb(144,238,144,255);
            //return color;
        }
        if (idx.column() == 3)
        {
            color.setRgb(240,128,128,255);
            secondColor.setRgb(220,68,68,255);
            QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
            linearGrad.setColorAt(0, color);
            linearGrad.setColorAt(1, secondColor);
            return QBrush(linearGrad);
            //color.setRgb(240,128,128,255);
            //return color;
        }
        //задание цвета строкам, с условием "верно"/"не верно"
        if (QSqlQueryModel::data(this->index(idx.row(),2)).toString()=="Не верно")
        {
            color.setRgb(240,128,128,255);
            secondColor.setRgb(220,68,68,255);
            QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
            linearGrad.setColorAt(0, color);
            linearGrad.setColorAt(1, secondColor);
            return QBrush(linearGrad);
            //color.setRgb(240,128,128,255);
            //return color;
        }
        if (QSqlQueryModel::data(this->index(idx.row(),2)).toString()=="Верно")
        {
            color.setRgb(203,235,203,255);
            secondColor.setRgb(55,176,55,255);
            QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
            linearGrad.setColorAt(0, color);
            linearGrad.setColorAt(1, secondColor);
            return QBrush(linearGrad);
            //color.setRgb(144,238,144,255);
            //return color;
        }
        //задание цвета ячейке прогресс
        if (idx.column() == 5)
        {
            int right=QSqlQueryModel::data(this->index(idx.row(),2)).toInt();
            int wrong=QSqlQueryModel::data(this->index(idx.row(),3)).toInt();
            //зеленый
            if((right*100/(right+wrong))>=75)
            {
                color.setRgb(203,235,203,255);
                secondColor.setRgb(55,176,55,255);
                QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
                linearGrad.setColorAt(0, color);
                linearGrad.setColorAt(1, secondColor);
                return QBrush(linearGrad);
                //color.setRgb(144,238,144,255);
                //return color;
            }
            //желтый
            if((right*100/(right+wrong))<75&&(right*100/(right+wrong))>=50)
            {
                color.setRgb(242,224,140,255);
                secondColor.setRgb(255,211,0,255);
                QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
                linearGrad.setColorAt(0, color);
                linearGrad.setColorAt(1, secondColor);
                return QBrush(linearGrad);
                //color.setRgb(255,211,0,255);
                //return color;
            }
            //красный
            if((right*100/(right+wrong))<50)
            {
                color.setRgb(240,128,128,255);
                secondColor.setRgb(220,68,68,255);
                QLinearGradient linearGrad(QPointF(20, 10), QPointF(100, 100));
                linearGrad.setColorAt(0, color);
                linearGrad.setColorAt(1, secondColor);
                return QBrush(linearGrad);
                //color.setRgb(240,128,128,255);
                //return color;
            }
        }
    }
    else if (role==Qt::DisplayRole)
    {
        return QSqlQueryModel::data(idx);
    }
    //выравнивание текста в ячейках по центру
    if (role == Qt::TextAlignmentRole )
    {
        return Qt::AlignCenter;
    }
    return QVariant();
}

