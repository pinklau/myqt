#include "ccomparestrings.h"
#include <QFile>
#include <QDebug>
#include "mytype.h"

const char* maincmd    = "maincmd";
const char* subcmd     = "subcmd";
const char* cmd        = "cmd";
const char* text       = "text";
const char* range      = "range";
const char* cmdreturn  = "return";
const char* head       = "head";
const char* end        = "end";
const char* usersignal = "usersignal";
const char* returnhead = "returnhead";

CCompareStrings::CCompareStrings()
{

}




CCommandXml::CCommandXml(QString& filepath)
    :contants("")
{
    QFile file(filepath);
    if (file.open(QFile::ReadOnly|QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        reader.readNext();
        while(!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                int ncount = reader.attributes().size();
                if (reader.name() == "contants")
                {
                   format_head_data(reader,ncount);
                }
                else if (reader.name() == "param")
                {
                    format_param_data(reader, ncount);
                }
            }
            reader.readNext();
        }
        file.close();
    }
}

CCommandXml::~CCommandXml()
{
    clearAll();
}

void CCommandXml::analyze()
{

}

void CCommandXml::format_head_data(QXmlStreamReader& reader, int ncount)
{
    for (int i = 0; i < ncount; i++)
    {
       if(reader.attributes()[i].name() == "head")
       {
            head.head.append( reader.attributes()[i].value());
       }
       else if (reader.attributes()[i].name() == "end")
       {
            head.end.append(reader.attributes()[i].value());
       }
       else if (reader.attributes()[i].name() == "usersignal")
       {
            head.userSignal.append(reader.attributes()[i].value());
       }
       else if (reader.attributes()[i].name() == "returnhead")
       {
            head.returnHead.append(reader.attributes()[i].value());
       }
    }

    qDebug()<<" contatnts head="<<head.head << "end="<<head.end << "usersignal="<<head.userSignal<<"returnhead="<<head.returnHead;
}

void CCommandXml::format_param_data(QXmlStreamReader &reader, int ncount)
{
    bool bHaveParent = false;
    QString maincmd;
    QString subcmd;
    CmdParams* cmdParam = new CmdParams;
    for (int i = 0; i < ncount; i++)
    {
        if (reader.attributes()[i].name() == "cmd")
        {
            cmdParam->cmd.append(reader.attributes()[i].value());
        }
        else if (reader.attributes()[i].name() == "maincmd")
        {
            cmdParam->maincmd.append(reader.attributes()[i].value());
        }
        else if (reader.attributes()[i].name() == "subcmd")
        {
            cmdParam->subcmd.append(reader.attributes()[i].value());
        }
        else if (reader.attributes()[i].name() == "text")
        {
            QString data = reader.attributes()[i].value().toString();
            format_text_data(data, *cmdParam);
        }
        else if (reader.attributes()[i].name() == "range")
        {
            QString data = reader.attributes()[i].value().toString();
            format_range_data(data, *cmdParam);
        }
        else if (reader.attributes()[i].name() == "return")
        {
            QString data = reader.attributes()[i].value().toString();
            format_return_data(data, *cmdParam);
        }

    }

    delete cmdParam;
}

void CCommandXml::format_range_data(QString &str, CmdParams& param)
{
    if (str.length()>2)
    {
        QVector<QPoint>* ranges = new QVector<QPoint>;

        int nPos = 0;
        QString tmp;
        QPoint p;
        QString colon = ":";
        QString semicolon = ";";

        while(nPos < str.length())
        {
            QChar c = str.at(nPos);
            if (!colon.compare(c,Qt::CaseInsensitive))
            {
                p.setX(tmp.toInt());
                tmp.clear();

            }
            else if (!semicolon.compare(c,Qt::CaseInsensitive) ||
                     nPos >= str.length()-1)
            {
                if (semicolon.compare(c, Qt::CaseInsensitive) &&
                        colon.compare(c,Qt::CaseInsensitive))
                    tmp += c;
                p.setY(tmp.toInt());
                ranges->push_back(p);
                p.setX(0);
                p.setY(0);
                tmp.clear();

            }
            else
            {
                tmp += c;
            }
            nPos ++;

        }

        delete ranges;
    }

}

void CCommandXml::format_replace_data(QString &str, CmdParams& param)
{
    int nCommaCount = 0;
    int nIndex = 0;
    while(true)
    {
        int n = str.indexOf(",", nIndex);
        if (n != -1)
        {
            n + 1 > str.length()? nIndex = n : nIndex = n+1;
            nCommaCount++;
        }
        else
            break;
    }
    if (str.length())
        nCommaCount ++;

}

void CCommandXml::format_text_data(QString &str, CmdParams& param)
{
    int nTextReplaceCount = 0;
    int nPos = 0;

    while (nPos < str.length())
    {
        if(!QString(str.at(nPos)).compare("#"))
        {
            nTextReplaceCount++;
        }
        nPos++;
    }
     param.nTextReplaceCount = nTextReplaceCount;
}

void CCommandXml::format_return_data(QString &str, CmdParams& param)
{
    int nIndex = str.indexOf("@range", Qt::CaseInsensitive);
    if (nIndex != -1)
    {

    }
}

void CCommandXml::clearAll()
{
    if (cmdSets.count())
    {

    }
}
