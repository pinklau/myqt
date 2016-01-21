#include "cscanport.h"
#include <qt_windows.h>
#include <QDebug>

CScanPort::CScanPort()
    :portList(0)
{

}

void CScanPort::run()
{
    QStringList ports = list_port();
    if (portList)
    {
        QString activePort = portList->currentText();
        qDebug()<< "current text is " << portList->currentText();
        portList->clear();
        for (int i = 0; i < ports.count();i++)
        {
            portList->addItem(ports.at(i));
        }
        portList->setCurrentText(activePort);
    }

}

void CScanPort::SetPortBox(QComboBox *pPort)
{
    portList = pPort;
}

QStringList CScanPort::list_port()
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

         }
         else//ERROR_MORE_DATA(234),ERROR_NO_MORE_ITEMS(259)
         {
             break;
         }


     }

     RegCloseKey(hKey);

 #endif
     return comList;
}
