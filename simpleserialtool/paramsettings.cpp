#include "paramsettings.h"
#include "ui_paramsettings.h"

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
