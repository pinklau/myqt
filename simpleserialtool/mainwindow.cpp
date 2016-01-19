#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FileButton_clicked()
{



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

}

void MainWindow::save_serialort_setting(QString strText, int nType)
{

}