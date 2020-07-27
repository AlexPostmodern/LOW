#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QObject>
#include <QSqlQueryModel>

class MyTableModel:public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MYTABLEMODEL_H
