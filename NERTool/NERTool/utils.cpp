#include "utils.h"

Utils::Utils(QObject *parent) : QObject(parent)
{
}


QString Utils::executeWordDiff(QString &textTrans, QString &textSubs)
{
    QString program = "dwdiff";

    QTime time = QTime::currentTime();
    QString fileNameSufix;
    fileNameSufix.append(QString::number(time.minute()))
            .append("_").append(QString::number(time.second()))
            .append("_").append(QString::number(time.msec()));

    QString transFileName = QString("trans_").append(fileNameSufix);
    QString subsFileName = QString("subs_").append(fileNameSufix);

    QString path = QDesktopServices::storageLocation(QDesktopServices::TempLocation);

    QString fileTname(path);
    fileTname.append("/").append(transFileName);
    QFile fileTrans(fileTname);
    fileTrans.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&fileTrans);
    out.setCodec("UTF-8");
    out << textTrans;
    out.flush();
    fileTrans.close();

    QString fileSname(path);
    fileSname.append("/").append(subsFileName);
    QFile fileSubs(fileSname);
    fileSubs.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out2(&fileSubs);
    out2.setCodec("UTF-8");
    out2 << textSubs;
    out2.flush();
    fileSubs.close();

    QStringList arguments;
    arguments << transFileName << subsFileName;

    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(path);
    myProcess->start(program, arguments);

    myProcess->waitForFinished();

    QString strError = myProcess->readAllStandardError();
    QString strOut = myProcess->readAllStandardOutput();

    ENGINE_DEBUG << "Diff = " << strOut;

    delete myProcess;

    return strOut;
}
