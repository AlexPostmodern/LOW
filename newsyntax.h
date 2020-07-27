#ifndef NEWSYNTAX_H
#define NEWSYNTAX_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QtDebug>
#include "database.h"

class NewSyntax:public QSyntaxHighlighter
{
    Q_OBJECT
public:
    NewSyntax(QTextDocument *parent = nullptr);
    ~NewSyntax()override;
    void updateTableNames();
protected:
    void highlightBlock(const QString &text) override;
private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat keywordFormat;
    DataBase *db;
    QVector<QString>namesOfTables;
};

#endif // NEWSYNTAX_H
