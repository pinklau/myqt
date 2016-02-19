#include "paramsettings.h"
#include "ui_paramsettings.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

paramsettings::paramsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paramsettings)
{
    ui->setupUi(this);
    this->resize(560,450);
    bshow = false;
}

paramsettings::~paramsettings()
{
    delete ui;
    clear_words();
}

void paramsettings::on_pushButton_ok_destroyed()
{

}

void paramsettings::on_pushButton_cancel_destroyed()
{

}

void paramsettings::on_pushButton_reset_clicked()
{
    ui->textEdit_pc->clear();
    ui->textEdit_arm->clear();
}

void paramsettings::on_pushButton_ok_clicked()
{
    listPc.clear();
    listArm.clear();

    QString textPc = ui->textEdit_pc->toPlainText();
    QString textArm = ui->textEdit_arm->toPlainText();

    QString t,t2;
    QChar changelinesignal = '\n';
    for (int i = 0; i < textPc.length(); i++)
    {
        if (textPc.at(i) == changelinesignal)
         {
            t2.append(t.toLocal8Bit());
            listPc.push_back(t2);
            t.clear();
            t2.clear();
        }
        else
        {
            t.push_back(textPc[i]);
        }
    }
    QByteArray ba = t.toLocal8Bit();
    t2.append(t.toLocal8Bit());
    listPc.push_back(t);
    t.clear();

    for (int i = 0; i < textArm.length();i++)
    {
        if (textArm.at(i) == changelinesignal)
            listArm.push_back(t),t.clear();
        else
            t.push_back(textArm.at(i));
    }
    listArm.push_back(t);
    qDebug()<< "arm:" <<listArm;
    qDebug()<< "pc:" << listPc;
}

QStringList paramsettings::PcParams() const
{
    return listPc;
}

QStringList paramsettings::ArmParams() const
{
    return listArm;
}

void paramsettings::on_pushButton_clicked()
{
    read_data(ui->textEdit_pc);
}

void paramsettings::read_data(QTextEdit *&textCtrl)
{
    QFileDialog fname;
    fname.setFilter(QDir::Readable);
    fname.setNameFilter(QString("*.txt"));
    if(fname.exec())
    {
       QStringList files = fname.selectedFiles();
       QString file = files[0];

       FILE* fp = fopen(file.toLocal8Bit(), "r");
       if (fp)
       {

           textCtrl->clear();
           QTextStream readFile(fp, QIODevice::ReadOnly);
           QString data = readFile.readAll();
           fclose(fp);
           textCtrl->insertPlainText(data);
       }

    }
}

void paramsettings::on_pushButton_2_clicked()
{
    read_data(ui->textEdit_arm);
}

void paramsettings::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
       // ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
    }
    else
    {
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
       // ui->lineEdit_5->setEnabled(false);
        ui->lineEdit_6->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
    }
}

void paramsettings::on_pushButton_3_clicked(bool checked)
{

}

void paramsettings::on_pushButton_3_clicked()
{
    bshow = !bshow;
    if (bshow)
    {
        this->resize(940,450);
    }
    else
    {
        this->resize(560,450);
    }
}

void paramsettings::clear_words()
{
    if (replaceWords.size())
    {
        QMapIterator<QString, QMap<QString,QPoint>* > it(replaceWords);
        QMap<QString, QMap<QString,QPoint>*>::iterator i = replaceWords.begin();
        while (i != replaceWords.end())
        {
            if (i.value())
            {
                delete i.value();
            }
            ++i;
        }
    }
}

void paramsettings::on_pushButton_4_clicked()
{
    if (!listPc.count())
        on_pushButton_ok_clicked();

    QString str = ui->lineEdit_2->text();
    QStringList result = listPc.filter(str);
    QString sig = ui->lineEdit->text();
    if (result.count())
    {
        QMap<QString,QPoint>* addStrings = NULL;
        QPoint ranges;
        ranges.setX(ui->lineEdit_3->text().toInt());
        ranges.setY(ui->lineEdit_4->text().toInt());
        if (find_add_str(str))
        {
            addStrings = find_add_str_list(str);
            (*addStrings)[ui->lineEdit_6->text()] =ranges;
        }
        else
        {
            addStrings = new QMap<QString,QPoint>;
            (*addStrings)[ui->lineEdit_6->text()] =ranges;
            replaceWords[str] = addStrings;
        }

        ui->textBrowser->insertPlainText(str);
        ui->textBrowser->insertPlainText(QString(" ->"));
        ui->textBrowser->insertPlainText(ui->lineEdit_6->text());
        ui->textBrowser->insertPlainText(QString(" :"));
        ui->textBrowser->insertPlainText(ui->lineEdit_3->text());
        ui->textBrowser->insertPlainText(QString("~"));
        ui->textBrowser->insertPlainText(ui->lineEdit_4->text());
        ui->textBrowser->insertPlainText(QString("\n"));
    }
}

bool paramsettings::find_add_str(QString &str)
{
    bool bret = false;
    QMapIterator<QString, QMap<QString,QPoint>* > it(replaceWords);
    while (it.hasNext())
    {
        it.next();
        if (it.key().contains(str))
        {
            bret = true;
            break;
        }
    }
    return bret;
}

QMap<QString,QPoint>* paramsettings::find_add_str_list(QString &str)
{
    QMapIterator<QString, QMap<QString,QPoint>* > it(replaceWords);
    while (it.hasNext())
    {
        it.next();
        if (it.key().contains(str))
        {
            return it.value();
        }
    }
    return NULL;
}


























