#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QProcess>
#include <QTextStream>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QDesktopServices>
#include <QNetworkInterface>
#include "nercommon.h"
#include <qxmlstream.h>
#include "simplecrypt.h"


const QString STR_NER_DOC  = "NER_LIC";
const QString STR_NER_USER = "user";
const QString STR_NER_ORG  = "organization";
const QString STR_NER_MAC  = "mac";
const QString STR_NER_START_DATE = "start-date";
const QString STR_NER_END_DATE   = "end-date";

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    static QString executeWordDiff(QString &textTrans, QString &textSubs);
    static QString readLicenceFile(QString &licenceFile);
    static bool fromXML(QString &xml,
                        QString &user,
                        QString &org,
                        QString &macAddress,
                        QDate &startDate,
                        QDate &finishdate);
    static QList<QString> getMachinesMACAddresses();
    
};

#endif // UTILS_H
