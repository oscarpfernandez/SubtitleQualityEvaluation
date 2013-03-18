#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QDate>
#include <QFile>

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
    
};

#endif // UTILS_H
