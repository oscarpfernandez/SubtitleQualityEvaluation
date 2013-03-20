#ifndef LICENCEMANAGER_H
#define LICENCEMANAGER_H

#include <QObject>
#include <QDesktopServices>
#include <QDir>
#include <QHostAddress>
#include <QHostInfo>
#include "utils.h"
#include "NtpClient.h"
#include "NtpReply.h"

const QString STR_LIC_FILE = "ner_licence.lic";
const QString STR_LIC_FOLDER = ".nertool";

enum LIC_ERROR_TYPE {
    LIC_NO_ERROR=0,
    LIC_INVALID_TIME=1,
    LIC_MAC_ADDRESS=2,
    LIC_INVALID_FILE=3,
    LIC_UND_ERROR=4
};

class LicenceManager : public QObject
{
    Q_OBJECT
public:
    explicit LicenceManager(QObject *parent = 0);
    ~LicenceManager();
    void installNewLicence(QString &filePath);
    LIC_ERROR_TYPE checkLicence();

private:
    NtpClient *ntpClient;
    LicenceData licenceData;

private slots:
    void replyReceived(QHostAddress add,
                       quint16 port,
                       NtpReply reply);

    
};

#endif // LICENCEMANAGER_H
