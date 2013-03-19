#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QDate>
#include <QFile>
#include <qxmlstream.h>
#include <QTextStream>
#include "common.h"
#include "simplecrypt.h"

const QString STR_NER_DOC = "NER_LIC";
const QString STR_NER_USER = "user";
const QString STR_NER_ORG = "organization";
const QString STR_NER_MAC = "mac";
const QString STR_NER_START_DATE = "start-date";
const QString STR_NER_END_DATE = "end-date";

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    static void generateLicenceFile(QString &licenceFile,
                             QString &user,
                             QString &org,
                             QString &mac,
                             QDate &startDate,
                             QDate &finishDate);
    static QString readLicenceFile(QString &licenceFile);
    static QString getXML(QString &user,
                          QString &org,
                          QString &mac,
                          QDate &startDate,
                          QDate &finishDate);
    static QString fromXML(QString &xml);
    
};

#endif // UTILS_H
