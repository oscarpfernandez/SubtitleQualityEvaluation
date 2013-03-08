#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QProcess>
#include <QTextStream>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QDesktopServices>
#include "nercommon.h"

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    static QString executeWordDiff(QString &textTrans, QString &textSubs);
    
};

#endif // UTILS_H
