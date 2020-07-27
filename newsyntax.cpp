#include "newsyntax.h"

NewSyntax::NewSyntax(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    db=new DataBase(this);
    const QString keywordPatterns[] =
    {
            QStringLiteral("\\bselect\\b"), QStringLiteral("\\bfrom\\b"), QStringLiteral("\\bdelete\\b"),
            QStringLiteral("\\bupdate\\b"), QStringLiteral("\\binsert\\b"), QStringLiteral("\\binto\\b"),
            QStringLiteral("\\bwhere\\b"), QStringLiteral("\\band\\b"), QStringLiteral("\\bor\\b"),
            QStringLiteral("\\bcreate\\b"), QStringLiteral("\\btext\\b"), QStringLiteral("\\btable\\b"),
            QStringLiteral("\\bvarchar\\b"), QStringLiteral("\\bnull\\b"), QStringLiteral("\\binteger\\b"),
            QStringLiteral("\\bprimary\\bkey\\b"), QStringLiteral("\\bforeign\\bkey\\b"), QStringLiteral("\\bdrop\\b"),
            QStringLiteral("\\bjoin\\b"), QStringLiteral("\\bleft\\bjoin\\b"), QStringLiteral("\\bvalues\\b"),
            QStringLiteral("\\border\\bby\\b"), QStringLiteral("\\bdesc\\b"), QStringLiteral("\\bset\\b"),
            QStringLiteral("\\bas\\b"), QStringLiteral("\\blike\\b"), QStringLiteral("\\bouter\\bjoin\\b"),
            QStringLiteral("\\balter\\b"),QStringLiteral("\\badd\\bcolumn\\b"),QStringLiteral("\\bint\\b")
    };//27
    for (const QString &pattern : keywordPatterns)
    {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
    }
    this->updateTableNames();
}
NewSyntax::~NewSyntax()
{
    delete db;
}
void NewSyntax::updateTableNames()
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkRed);
    keywordFormat.setFontWeight(QFont::Normal);
    keywordFormat.setFontUnderline(true);
    int countOftables=(db->db_QueryRecordOneNumber("select count(*) from sqlite_master where "
                                                   "(type = 'table' and name not like 'sqlite_%')",0,0)).toUInt();
    for (int i=0;i<countOftables;i++)
    {
        namesOfTables.append("\\b"+db->db_QueryRecordOneNumber("select name from sqlite_master where "
                                                         "(type = 'table' and name not like 'sqlite_%')",0,i)+"\\b");
        rule.pattern=QRegularExpression(namesOfTables.at(i));
        rule.format=keywordFormat;
        highlightingRules.append(rule);
    }
    qDebug()<<highlightingRules.at(27).pattern;
}
void NewSyntax::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
