#include "utils.h"

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}


void Utils::generateLicenceFile(QString &licenceFile,
                                QString &user,
                                QString &org,
                                QString &mac,
                                QDate &startDate,
                                QDate &finishDate)
{

    QFile file(licenceFile);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Write a header with a "magic number" and a version
    out << (quint32)0xAABBCCDD;
    out << (qint32)23;

    out.setVersion(QDataStream::Qt_4_8);

    QString xml = Utils::getXML(user, org, mac, startDate, finishDate);

    SimpleCrypt crypto(Q_UINT64_C(0x0c7ad7b4acb8f723)); //some random number
    QString xmlEncrypted = crypto.encryptToString(xml);
    //qDebug() << xml << endl << xmlEncrypted;

    // Write the data
    out << xmlEncrypted.count();
    out << xmlEncrypted;


    file.close();
}


QString Utils::readLicenceFile(QString &licenceFile)
{
    QFile file(licenceFile);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    int magic;
    int version;
    int xmlCount;
    QString xmlEncrypted;

    in >> magic;
    in >> version;
    in >> xmlCount;
    in >> xmlEncrypted;

    file.close();

    //qDebug() << magic << endl << version << endl << xmlCount << endl << xmlEncrypted;

    SimpleCrypt crypto(Q_UINT64_C(0x0c7ad7b4acb8f723)); //some random number
    QString xml = crypto.decryptToString(xmlEncrypted);

    return xml;


}

QString Utils::getXML(QString &user,
                      QString &org,
                      QString &mac,
                      QDate &startDate,
                      QDate &finishDate)
{
    QString x;

    QXmlStreamWriter xmlWriter(&x);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement(STR_NER_DOC);

    xmlWriter.writeStartElement(STR_NER_USER);
    xmlWriter.writeCharacters(user);
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement(STR_NER_ORG);
    xmlWriter.writeCharacters(org);
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement(STR_NER_MAC);
    xmlWriter.writeCharacters(mac);
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement(STR_NER_START_DATE);
    xmlWriter.writeCharacters(startDate.toString());
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement(STR_NER_END_DATE);
    xmlWriter.writeCharacters(finishDate.toString());
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    return x;
}

QString Utils::fromXML(QString &xml)
{
    QXmlStreamReader xmlReader(xml);

    QString user, org, mac, startDate, endDate;

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
            mac = xmlReader.readElementText();
        }
        else if(xmlReader.name() == STR_NER_START_DATE){
            startDate = xmlReader.readElementText();
        }
        else if(xmlReader.name() == STR_NER_END_DATE){
            endDate = xmlReader.readElementText();
        }
    }

    QString ret;
    ret.append("* Username \t---\t").append(user).append("\n")
            .append("* Organization \t---\t").append(org).append("\n")
            .append("* MAC Address \t---\t").append(mac).append("\n")
            .append("* Start Date \t---\t").append(startDate).append("\n")
            .append("* Finish Date \t---\t").append(endDate);

    return ret;
}
































