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

QString Utils::readLicenceFile(QString &licenceFile)
{
    QFile file(licenceFile);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    qint32 magic;
    int version;
    int xmlCount;
    QString xmlEncrypted;

    in >> magic;
    in >> version;
    in >> xmlCount;
    in >> xmlEncrypted;

    file.close();

    QString xml;
    if(magic != (qint32)0xAABBCCDD){
        //not our lic file!
        return xml;
    }

    //qDebug() << magic << endl << version << endl << xmlCount << endl << xmlEncrypted;

    SimpleCrypt crypto(Q_UINT64_C(0x0c7ad7b4acb8f723)); //some random number
    xml = crypto.decryptToString(xmlEncrypted);

    return xml;
}

bool Utils::fromXML(QString &xml,
                    QString &user,
                    QString &org,
                    QString &macAddress,
                    QDate &startDate,
                    QDate &finishdate)
{
    QXmlStreamReader xmlReader(xml);

    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        /* Read next element.*/
        xmlReader.readNext();

        if(xmlReader.name() == STR_NER_DOC){
            continue;
        }
        else if(xmlReader.name() == STR_NER_USER){
            user = xmlReader.readElementText();
        }
        else if(xmlReader.name() == STR_NER_ORG){
            org = xmlReader.readElementText();
        }
        else if(xmlReader.name() == STR_NER_MAC){
            macAddress = xmlReader.readElementText();
        }
        else if(xmlReader.name() == STR_NER_START_DATE){
            startDate = QDate::fromString(xmlReader.readElementText(), Qt::ISODate);
        }
        else if(xmlReader.name() == STR_NER_END_DATE){
            finishdate = QDate::fromString(xmlReader.readElementText(), Qt::ISODate);
        }
    }

    if(xmlReader.hasError()){
        return false;
    }

    return true;
}

QList<QString> Utils::getMachinesMACAddresses()
{
    QList<QString> ret;

    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsRunning)){

            foreach (QNetworkAddressEntry entry, interface.addressEntries())

            {
                QString mac = interface.hardwareAddress().toLower().replace("-",":");
                if ( mac != "00:00:00:00:00:00")
                {
                    ret.append(mac);
                }
            }
        }
    }
    return ret;
}

QString Utils::removeBlanksBeforePonctuation(QString &text)
{
    if(!containsPonctuation(text))
    {
        return text;
    }

    QStringList list = text.simplified().split(" ");
    int cardinal = list.count();

    for(int i=0; i<cardinal; i++)
    {
        QString elem = QString(list.at(i));
        if(containsPonctuation(elem) && i>0)
        {
            QString prev = list.at(i-1);
            QString joint = prev.append(elem);
            list.insert(i-1, joint);
            list.removeAt(i);
            list.removeAt(i);
            cardinal--;
        }
    }

    return list.join(" ");

}

bool Utils::containsPonctuation(QString &text)
{
    if(!text.contains("?")
            && !text.contains("!")
            && !text.contains(":")
            && !text.contains(",")
            && !text.contains(";")
            && !text.contains("-")
            && !text.contains(".")
            && !text.contains("¿")
            && !text.contains("¡") )
    {
        return false;
    }

    return true;
}
