#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMapIterator>
#include <QTextCodec>
#include "ccomparestrings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    ,bWork(false)
    ,bhex(false)
    ,nWriteNums(0)
    ,nReadNums(0)
{ 
    ui->setupUi(this);
     port = new QSerialPort;
    portScaner.SetPortBox(ui->comboBox_5);
    portScaner.start();
    workThread.setSerialObj(port);
    QObject::connect(ui->comboBox,
            SIGNAL(currentIndexChanged(int)), this,
            SLOT(save_port_baud()));

    QObject::connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(save_port_byte()));
    QObject::connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)), this,SLOT(save_port_stopbyte()));
    QObject::connect(ui->comboBox_4,SIGNAL(currentIndexChanged(int)), this, SLOT(save_port_parity()));
    QObject::connect(ui->comboBox_5,SIGNAL(currentIndexChanged(int)), this, SLOT(save_port_name()));
    QObject::connect(ui->comboBox_6,SIGNAL(currentIndexChanged(int)),this,SLOT(save_port_flowCtrl()));
    QObject::connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(destroy_threads_on_exit()));
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(read_comport_data()));
    QObject::connect(&autoTimer,SIGNAL(timeout()),this,SLOT(auto_send_timer()));

    portInfo.baud = QSerialPort::Baud9600;
    portInfo.databits = QSerialPort::Data5;
    portInfo.parity = QSerialPort::NoParity;
    portInfo.stopbits = QSerialPort::OneStop;
    portInfo.flowCtrl = QSerialPort::NoFlowControl;

    ui->pushButton_4->setEnabled(false);
    ui->read_num->clear();
    ui->write_num->clear();
    ui->read_num->setText(QString("0"));
    ui->write_num->setText(QString("0"));

}

MainWindow::~MainWindow()
{
    delete port;
    delete ui;
}

void MainWindow::on_FileButton_clicked()
{
    if (port->isOpen())
    {
        ui->textBrowser->setPlainText(QString("sssss"));
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        port->write(ba);
        char szWrite[16] = {0};
        nWriteNums +=ba.count() ;
        sprintf(szWrite, "%d", nWriteNums);
        ui->write_num->setText(szWrite);
    }
    else
    {
        QMessageBox::warning(this, QString("串口异常"),QString("串口没有打开"));
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter dc(this);
    QString imgname(":/images/1.png");
    QImage img;
    if (img.load(imgname))
    {
        QPoint point(0,0);
        dc.drawImage(point, img);
    }
}

QStringList MainWindow::list_port()
{
    QStringList comList;

 #if defined(Q_OS_WIN32)

     HKEY hKey;
     LONG ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM\\"), 0, KEY_READ, &hKey);
     if (ret != ERROR_SUCCESS)
     {
         return comList;//错误：无法打开有关的hKEY
     }

     DWORD dwIndex = 0;
     LONG Status = 0;
     wchar_t ckeyName[512] = {0};
     char ckeyValue[100] = {0};
     DWORD szName = 0;
     DWORD szValue = 0;
     DWORD type = 0;
     QString str1;
     QString str2;

     while (1)
     {
         szName = sizeof(ckeyName);//注意,因为szName每读一次key,数值就变化一次,所以每次必须重新初始化,否则长度若不足,会出现ERROR_MORE_DATA的错误
         szValue = sizeof(ckeyValue);//与szName相同
         Status = RegEnumValue(hKey, dwIndex++, ckeyName, &szName, 0, &type, (BYTE*)ckeyValue, &szValue);

         if (Status == ERROR_SUCCESS)
         {
             //初始化
             str1 = "";
             str2 = "";

             //求出键的名称
             for (DWORD i = 0; i < szName; i++)
             {
                 str1.append(ckeyName[i]);
             }

             //求出键的数值
             for (DWORD i = 0; i < szValue; i++)
             {
                 if (ckeyValue[i] != 0)//必须跳过0,例如"COM1"在ckeyValue数组储存的是"C0O0M010"
                 {
                     str2.append(ckeyValue[i]);
                 }
             }

             //根据键的数值判断是否COM
             if (str2.indexOf("COM") != -1)
             {
                 comList.append(str2);
             }
 //            printf("%s", str2);
         }
         else//ERROR_MORE_DATA(234),ERROR_NO_MORE_ITEMS(259)
         {
             break;
         }

//         printf("\n");
     }

     RegCloseKey(hKey);

 #endif
     return comList;
}



void MainWindow::on_pushButton_clicked()
{
    if (portInfo.portname.isEmpty())
    {
        QMessageBox::warning(this, QString("端口"),QString("请设置端口号"));
        return;
    }

    bWork = !bWork;

    if (bWork)
    {
        setPortParams();
        ui->textBrowser->insertPlainText(QString("端口："));
        ui->textBrowser->insertPlainText(port->portName());

        if (port->open(QSerialPort::ReadWrite))
        {
            workThread.start();
            ui->pushButton->setText(QString("关闭端口"));
            ui->textBrowser->insertPlainText(QString("打开成功\n"));
            ui->comboBox_5->setEnabled(false);
        }
    }
    else
    {
        port->close();
        ui->comboBox_5->setEnabled(true);
        if (!port->isOpen())
        {
            ui->pushButton->setText(QString("打开端口"));
        }
        workThread.stop();
    }
}

void MainWindow::save_port_baud()
{
    int _baud = ui->comboBox->currentText().toInt();
    QSerialPort::BaudRate bd = QSerialPort::Baud4800;
    switch (_baud)
    {
    case 4800:
        bd = QSerialPort::Baud4800;
        break;
    case 9600:
        bd = QSerialPort::Baud9600;
        break;
    case 19200:
        bd = QSerialPort::Baud19200;
        break;
    case 38400:
        bd = QSerialPort::Baud38400;
        break;
    case 57600:
        bd = QSerialPort::Baud57600;
        break;
    case 115200:
        bd = QSerialPort::Baud115200;
        break;
    }
    if (portInfo.baud != bd)
    {
        portInfo.baud = bd;
    }

}

void MainWindow::save_port_byte()
{
    QSerialPort::DataBits databit = QSerialPort::Data5;
    int _databit = ui->comboBox_2->currentText().toInt();
    switch (_databit)
    {
    case 5:
        databit = QSerialPort::Data5;
        break;
    case 6:
        databit = QSerialPort::Data6;
        break;
    case 7:
        databit = QSerialPort::Data7;
        break;
    case 8:
        databit = QSerialPort::Data8;
        break;
    }

    if (portInfo.databits != databit)
        portInfo.databits = databit;
}

void MainWindow::save_port_stopbyte()
{
    QSerialPort::StopBits stopbit = QSerialPort::OneStop;
    int _stopbit = (int)(ui->comboBox_3->currentText().toFloat()*10);
    switch (_stopbit)
    {
    case 10:
        stopbit = QSerialPort::OneStop;
        break;
    case 15:
        stopbit = QSerialPort::OneAndHalfStop;
        break;
    case 20:
        stopbit = QSerialPort::TwoStop;
        break;
    }

    if (portInfo.stopbits != stopbit)
        portInfo.stopbits = stopbit;
}

void MainWindow::save_port_parity()
{
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QString _parity = ui->comboBox_4->currentText();

    if (_parity.compare(QString("none")) == 0)
    {
        parity = QSerialPort::NoParity;
    }
    else if (_parity.compare(QString("old")) == 0)
    {
        parity = QSerialPort::OddParity;
    }
    else if (_parity.compare(QString("even")) == 0)
    {
        parity = QSerialPort::EvenParity;
    }
    else if (_parity.compare(QString("mark")) == 0)
    {
        parity = QSerialPort::MarkParity;
    }
    else if (_parity.compare(QString("space")) == 0)
    {
        parity = QSerialPort::UnknownParity;
    }
    if (portInfo.parity != parity)
        portInfo.parity = parity;
}

void MainWindow::save_port_flowCtrl()
{
    QSerialPort::FlowControl fCtrl = QSerialPort::NoFlowControl;
    QString _fCtrl = ui->comboBox_6->currentText();
    if (_fCtrl.compare(QString("unknown")))
    {
        fCtrl = QSerialPort::NoFlowControl;
    }
    else if (_fCtrl.compare(QString("software")))
    {
        fCtrl = QSerialPort::SoftwareControl;
    }
    else if (_fCtrl.compare(QString("hardware")))
    {
        fCtrl = QSerialPort::HardwareControl;
    }
    if (portInfo.flowCtrl != fCtrl)
        portInfo.flowCtrl = fCtrl;
}

void MainWindow::save_port_name()
{
    QString portname = ui->comboBox_5->currentText();
    if (!portname.isEmpty() && portname.compare(portInfo.portname))
        portInfo.portname = portname;
}

void MainWindow::on_pushButton_2_clicked()
{
   portScaner.start();
}

void MainWindow::setPortParams()
{
    port->setPortName(portInfo.portname);
    port->setBaudRate(portInfo.baud);
    port->setDataBits(portInfo.databits);
    port->setParity(portInfo.parity);
    port->setStopBits(portInfo.stopbits);
}

void MainWindow::destroy_threads_on_exit()
{
    workThread.stop();
}

void MainWindow::read_comport_data()
{
    QByteArray tmp = port->readAll();
    char szRead[16] = {0};
    nReadNums += tmp.count();
    sprintf(szRead, "%d", nReadNums);
    ui->read_num->setText(QString(szRead));

    if (bhex)
    {
        QByteArray thex =  tmp.toHex();
        QString text;
        thex.toUpper();
        text.prepend(thex);

        ui->textBrowser->insertPlainText(text);
        ui->textBrowser->insertPlainText(QString(" "));
    }
    else
        ui->textBrowser->insertPlainText(tmp);

    if (ui->checkBox_3->isChecked() && cmdMap.count())
    {
        QString text(tmp);
        QMapIterator<QString,QString>  i(cmdMap);

        while (i.hasNext())
        {
            i.next();
            if (text.contains(i.key(), Qt::CaseInsensitive))
            {
                QByteArray ba;
                ba.append(i.value());
                ba.append(QChar('\n'));
                port->write(ba);
                break;
            }
        }
    }

    ui->textBrowser->moveCursor(QTextCursor::End);

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (bhex != checked)
        bhex = checked;

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if (checked)
    {
        int timeout = ui->lineEdit->text().toInt();
        if (timeout)
            autoTimer.start(timeout);
    }
    else
    {
        if (autoTimer.isActive())
            autoTimer.stop();
    }
}

void MainWindow::auto_send_timer()
{
    if (port->isOpen())
    {
       on_FileButton_clicked();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    /*
    int r = armAsk.exec();
    if (r)
    {
        cmdMap.clear();
        QStringList pc = armAsk.PcParams();
        QStringList arm = armAsk.ArmParams();

        for (int i = 0; i < pc.count(); i++)
        {
            cmdMap[pc[i]] = i >= arm.count() ? QString(""): arm[i];
        }
    }
    */
    QFileDialog fname;
    fname.setFilter(QDir::Readable);
    fname.setNameFilter(QString("*.xml"));
    if (fname.exec())
    {
        QStringList files = fname.selectedFiles();
        QString file = files[0];


    }
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    ui->pushButton_4->setEnabled(checked);
}

void MainWindow::on_pushButton_5_clicked()
{

    QFileDialog fname;
    fname.setFilter(QDir::Readable);
    fname.setNameFilter(QString("*.xml"));
    if (fname.exec())
    {
        QStringList files = fname.selectedFiles();
        QString file = files[0];
        CCommandXml reader(file);

    }
}
