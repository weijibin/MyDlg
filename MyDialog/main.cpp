#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <windows.h>
#include <Dbghelp.h>
#include <iostream>
#include <vector>
#include <tchar.h>
#include <QDir>


#pragma comment(lib, "Dbghelp.lib")
using namespace std;
#define LOGFILEMAX 10000
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);



    //输出到文件
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    //toLocal8Bit才能保证转换为string 是不是乱码
    //调用标准输出 保证输出到控制台
    std::cout<<message.toLocal8Bit().toStdString()<<std::endl;
    mutex.unlock();
}


//====================================================================
//异常捕获函数
long ApplicationCrashHandler(EXCEPTION_POINTERS *pException){
{
        // 在程序exe的上级目录中创建dmp文件夹
        QDir *dmp = new QDir;
        bool exist = dmp->exists("../dmp/");
        if(exist == false)
            dmp->mkdir("../dmp/");
        }
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
		current_date = "mytestDump";
        QString time =  current_date + ".dmp";
          EXCEPTION_RECORD *record = pException->ExceptionRecord;
          QString errCode(QString::number(record->ExceptionCode, 16));
          QString errAddr(QString::number((uint)record->ExceptionAddress, 16));
          QString errFlag(QString::number(record->ExceptionFlags, 16));
          QString errPara(QString::number(record->NumberParameters, 16));
          qDebug()<<"errCode: "<<errCode;
          qDebug()<<"errAddr: "<<errAddr;
          qDebug()<<"errFlag: "<<errFlag;
          qDebug()<<"errPara: "<<errPara;
          HANDLE hDumpFile = CreateFile((LPCWSTR)QString(time).utf16(),
                   GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
          if(hDumpFile != INVALID_HANDLE_VALUE) {
              MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
              dumpInfo.ExceptionPointers = pException;
              dumpInfo.ThreadId = GetCurrentThreadId();
              dumpInfo.ClientPointers = TRUE;
              MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
              CloseHandle(hDumpFile);
          }
          else{
              qDebug()<<"hDumpFile == null";
          }
          return EXCEPTION_EXECUTE_HANDLER;
}

//====================================================================

int main(int argc, char *argv[])
{

    //注冊异常捕获函数
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);


    QApplication a(argc, argv);

    //=========================================
    //注册MessageHandler
//    qInstallMessageHandler(outputMessage);

    //打印日志到文件中
    qDebug("This is a debug message");
    qWarning("This is a warning message");
    qCritical("This is a critical message");
    //qFatal("This is a fatal message");
    //=========================================



    Widget w;
    w.show();

    return a.exec();
}
