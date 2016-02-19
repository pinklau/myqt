#ifndef CCOMPARESTRINGS_H
#define CCOMPARESTRINGS_H
#include "mytype.h"
#include <QXmlStreamReader>
#include <QXmlAttributes>
#include <QFile>

class CCompareStrings
{
public:
    CCompareStrings();
    void setCompareString(QString* str);
    int command();
    QVector<int>* params();
    QVector<QPoint> params2();
};

class CCommandXml
{
public:
    CCommandXml(QString& filepath);
    ~CCommandXml();
    void analyze();

private:
    void format_head_data(QXmlStreamReader& reader, int ncount);
    void format_param_data(QXmlStreamReader& reader, int ncount);
    void format_range_data(QString& str, CmdParams& param);
    void format_replace_data(QString& str, CmdParams& param);
    void format_text_data(QString& str, CmdParams& param);
    void format_return_data(QString& str, CmdParams& param);
public:
    void clearAll();
private:
    QString contants;
    CmdHeadTrail head;
    QMap<QString, QMap<QString,CommandSet>*> cmdSets;
};

#endif // CCOMPARESTRINGS_H
