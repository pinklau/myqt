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
}

paramsettings::~paramsettings()
{
    delete ui;
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
